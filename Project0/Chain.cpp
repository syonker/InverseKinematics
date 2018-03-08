#include "Chain.h"



Chain::Chain(unsigned int numLinks, Point* goal)
{
	Link* newLink = new Link(0);
	Links.push_back(newLink);
	Root = newLink;

	for (int i = 1; i < numLinks; i++) {
		Link* newLink = new Link(i);
		Links.push_back(newLink);
		Links[i - 1]->AddChild(newLink);
	}

	Links[numLinks - 1]->lastLink = true;

	Goal = goal;
	Goal->Position = {(numLinks*2)-2 , 0.0f, 0.0f};
	Goal->model->ambient = {0,1,0};

	tolerance = 0.001f;
	IKon = false;
}


Chain::~Chain()
{
}

void Chain::ToggleIK() {
	if (IKon) {
		IKon = false;
	}
	else {
		IKon = true;
	}
}

void Chain::IK(glm::mat4 parentW) {

	if (IKon) {

		glm::vec3 diff = Goal->Position - EndEffector;

		if (glm::length(diff) > tolerance) {

			Root->IK(parentW, EndEffector, Goal->Position);

		}

	}

}

void Chain::Update(glm::mat4 parentW) {

	Root->Update(parentW, &EndEffector);

}


void Chain::Draw(const glm::mat4 &viewProjMtx, uint shader) {

	Root->Draw(viewProjMtx, shader);

}

void Chain::TestDOFChange(unsigned int link, unsigned int dof, float value) {

	Links[link]->arrayDOF[dof]->SetValue(value);

}