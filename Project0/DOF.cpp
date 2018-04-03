
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

void DOF::SetMinMax(float minValue, float maxValue) {

	min = minValue;
	max = maxValue;

}

float DOF::Add(float addVal) {

	value += addVal;

	return value;

}

