#pragma once

#include"Core.h"
#include "Model.h"

class Point
{
public:
	Point(float x, float y, float z);
	~Point();

	void Update();
	void Draw(const glm::mat4 &viewProjMtx, uint shader);

	glm::vec3 Position;
	glm::vec3 offset;
	Model* model;

};

