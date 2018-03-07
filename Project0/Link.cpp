#include "Link.h"



Link::Link(unsigned int index)
{

	position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 size = { 1.0f,0.5f,0.5f };
	boxmin = position - size;
	boxmax = position + size;
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

}


Link::~Link()
{
}

void Link::AddChild(Link* newChild) {

	children.push_back(newChild);

}

void Link::Update(glm::mat4 parentW) {

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

	for (unsigned int i = 0; i < children.size(); i++) {

		children[i]->Update(W);

	}

}


void Link::Draw(const glm::mat4 &viewProjMtx, uint shader) {

	model->Draw(W, viewProjMtx, shader);

	for (unsigned int i = 0; i < children.size(); i++) {

		children[i]->Draw(viewProjMtx, shader);

	}

}
