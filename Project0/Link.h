#pragma once

#include "Core.h"
#include "DOF.h"
#include "Model.h"
#include <iostream>

class Link
{
public:
	Link(unsigned int index);
	~Link();

	void AddChild(Link* newChild);
	void Update(glm::mat4 parentW);
	void Draw(const glm::mat4 &viewProjMtx, uint shader);

	std::vector<Link*> children;
	std::vector<DOF*> arrayDOF;
	glm::vec3 position;
	glm::vec3 offset;
	glm::vec3 boxmin;
	glm::vec3 boxmax;
	glm::vec3 pose;
	glm::mat4 L;
	glm::mat4 W;
	Model* model;

};

