#include "Link.h"



Link::Link(unsigned int index)
{

	position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 minOffset = { 0.0f,0.5f,0.5f };
	glm::vec3 maxOffset = { 2.0f,0.5f,0.5f };
	boxmin = position - minOffset;
	boxmax = position + maxOffset;
	model = new Model();
	model->MakeBox(boxmin, boxmax);
	model->ambient = ((float)(index+1) / 5.0f) * model->ambient;

	if (index == 0) {
		offset = { 0.0f,0.0f,0.0f };
	}
	else {
		offset = { 2.0f,0.0f,0.0f };
	}
	pose = { 0.0f,0.0f,0.0f };
	L = glm::mat4(1.0f);
	W = glm::mat4(1.0f);


	DOF* xDOF = new DOF();
	DOF* yDOF = new DOF();
	DOF* zDOF = new DOF();
	arrayDOF.push_back(xDOF);
	arrayDOF.push_back(yDOF);
	arrayDOF.push_back(zDOF);

	//max radians than it can rotate in one update
	threshold = 0.001f;
	lastLink = false;

}


Link::~Link()
{
}

void Link::AddChild(Link* newChild) {

	children.push_back(newChild);

}

void Link::Update(glm::mat4 parentW, glm::vec3* endEffector) {

	float x = arrayDOF[0]->GetValue();
	float y = arrayDOF[1]->GetValue();
	float z = arrayDOF[2]->GetValue();

	glm::mat4 rotX = glm::mat4(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, cos(x), sin(x), 0.0f),
		glm::vec4(0.0f, -sin(x), cos(x), 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	glm::mat4 rotY = glm::mat4(glm::vec4(cos(y), 0.0f, -sin(y), 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(sin(y), 0.0f, cos(y), 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	glm::mat4 rotZ = glm::mat4(glm::vec4(cos(z), sin(z), 0.0f, 0.0f),
		glm::vec4(-sin(z), cos(z), 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	glm::mat4 translate = glm::mat4(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(offset, 1.0f));

	L = translate * rotZ * rotY * rotX;

	W = parentW * L;

	if (lastLink) {
		glm::vec4 pos = { position, 1.0f };
		pos = W * pos;
		glm::vec3 pivotPos = { pos.x, pos.y, pos.z };
		*endEffector = pivotPos;
	}

	for (unsigned int i = 0; i < children.size(); i++) {

		children[i]->Update(W, endEffector);

	}

}


void Link::Draw(const glm::mat4 &viewProjMtx, uint shader) {

	if (!lastLink) {

		model->Draw(W, viewProjMtx, shader);

		for (unsigned int i = 0; i < children.size(); i++) {

			children[i]->Draw(viewProjMtx, shader);

		}
	}
}

void Link::IK(glm::mat4 parentW, glm::vec3 endEffector, glm::vec3 goal) {

	float x = arrayDOF[0]->GetValue();
	float y = arrayDOF[1]->GetValue();
	float z = arrayDOF[2]->GetValue();

	glm::mat4 rotX = glm::mat4(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, cos(x), sin(x), 0.0f),
		glm::vec4(0.0f, -sin(x), cos(x), 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	glm::mat4 rotY = glm::mat4(glm::vec4(cos(y), 0.0f, -sin(y), 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(sin(y), 0.0f, cos(y), 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	glm::mat4 rotZ = glm::mat4(glm::vec4(cos(z), sin(z), 0.0f, 0.0f),
		glm::vec4(-sin(z), cos(z), 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	glm::mat4 translate = glm::mat4(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(offset, 1.0f));

	L = translate * rotZ * rotY * rotX;
	W = parentW * L;



	//gets the each unit length rotation axis in world space
	glm::vec4 axis;
	axis = { 1,0,0,0 };
	glm::vec4 worldAxisX4 = parentW * rotZ * rotY * axis;
	axis = { 0,1,0,0 };
	glm::vec4 worldAxisY4 = parentW * rotZ * axis;
	axis = { 0,0,1,0 };
	glm::vec4 worldAxisZ4 = parentW * axis;
	glm::vec3 worldAxisX = { worldAxisX4.x, worldAxisX4.y, worldAxisX4.z };
	glm::vec3 worldAxisY = { worldAxisY4.x, worldAxisY4.y, worldAxisY4.z };
	glm::vec3 worldAxisZ = { worldAxisZ4.x, worldAxisZ4.y, worldAxisZ4.z };

	
	//gets the position of joint pivot in world space
	glm::vec4 pos = { position, 1.0f };
	pos = W * pos;
	glm::vec3 pivotPos = { pos.x, pos.y, pos.z };

	glm::vec3 Jx = glm::cross(worldAxisX, (endEffector - pivotPos));
	glm::vec3 Jy = glm::cross(worldAxisY, (endEffector - pivotPos));
	glm::vec3 Jz = glm::cross(worldAxisZ, (endEffector - pivotPos));

	/*
	glm::mat3 J = { Jx,Jy,Jz };
	J = glm::transpose(J);
	Jx = J[0];
	Jy = J[1];
	Jz = J[2];
	*/

	//calculate step size
	glm::vec3 deltaE = goal - endEffector;

	float deltaX = glm::dot(Jx, deltaE);
	float beta = threshold / (glm::max(threshold, glm::abs(deltaX)));
	arrayDOF[0]->SetValue((arrayDOF[0]->GetValue() + (beta * deltaX)));

	float deltaY = glm::dot(Jy, deltaE);
	beta = threshold / (glm::max(threshold, glm::abs(deltaY)));
	arrayDOF[1]->SetValue((arrayDOF[1]->GetValue() + (beta * deltaY)));

	float deltaZ = glm::dot(Jz, deltaE);
	beta = threshold / (glm::max(threshold, glm::abs(deltaZ)));
	arrayDOF[2]->SetValue((arrayDOF[2]->GetValue() + (beta * deltaZ)));




	for (unsigned int i = 0; i < children.size(); i++) {

		children[i]->IK(W, endEffector, goal);

	}

}
