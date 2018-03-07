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
	

	Goal = goal;
	Goal->Position = {(numLinks*2)+1 , 0.0f, 0.0f};
	Goal->model->ambient = {0,1,0};
	
}


Chain::~Chain()
{
}

void Chain::Update(glm::mat4 parentW) {

	Root->Update(parentW);

}


void Chain::Draw(const glm::mat4 &viewProjMtx, uint shader) {

	Root->Draw(viewProjMtx, shader);

}

void Chain::TestDOFChange(unsigned int link, unsigned int dof, float value) {

	Links[link]->arrayDOF[dof]->SetValue(value);

}