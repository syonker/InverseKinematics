
#include "DOF.h"


DOF::DOF()
{
	//set default value
	value = 0.0f;
}

DOF::~DOF()
{
}

void DOF::SetValue(float newValue) {

	value = newValue;

}

float DOF::GetValue() {

	return value;

}


float DOF::Add(float addVal) {

	value += addVal;

	return value;

}

