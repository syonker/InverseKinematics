#include "Point.h"



Point::Point(float x, float y, float z)
{
	Position = {x,y,z};
	model = new Model();
	offset = { 0.5f,0.5f,0.5f };
	model->MakeBox(Position - offset, Position + offset);
}


Point::~Point()
{
}

void Point::Update() {

	model->MakeBox(Position - offset, Position + offset);

}

void Point::Draw(const glm::mat4 &viewProjMtx, uint shader) {

	model->Draw(glm::mat4(1.0f), viewProjMtx, shader);

}