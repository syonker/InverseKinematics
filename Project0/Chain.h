#pragma once

#include "Core.h"
#include "Link.h"
#include "Point.h"
#include <iostream>

class Chain
{
public:
	Chain(unsigned int numLinks, Point* goal);
	~Chain();

	void Update(glm::mat4 parentW);
	void Draw(const glm::mat4 &viewProjMtx, uint shader);
	void TestDOFChange(unsigned int link, unsigned int dof, float value);
	void IK(glm::mat4 parentW);
	void ToggleIK();

	std::vector<Link*> Links;
	Link* Root;
	Point* Goal;
	float tolerance;

	glm::vec3 EndEffector;

	bool IKon;
};

