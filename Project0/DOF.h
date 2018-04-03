
#pragma once

#include "Core.h"

class DOF
{
public:
	DOF();
	~DOF();
	void SetValue(float newValue);
	float GetValue();
	float Add(float addVal);

	float value;

private:

};
