////////////////////////////////////////
// Tester.h
////////////////////////////////////////

#pragma once

#include "Shader.h"
#include "Camera.h"
#include "DOF.h"
#include "Point.h"
#include "Chain.h"
#include "Link.h"

////////////////////////////////////////////////////////////////////////////////

// The 'Tester' is a simple top level application class. It creates and manages a
// window with the GLUT extension to OpenGL and it maintains a simple 3D scene
// including a camera and some other components.

class Tester {
public:
	Tester(const char *windowTitle,int argc,char **argv);
	~Tester();

	void Update();
	void Reset();
	void Draw();

	void Quit();

	// Event handlers
	void Resize(int x,int y);
	void Keyboard(int key,int x,int y);
	void MouseButton(int btn,int state,int x,int y);
	void MouseMotion(int x,int y);

private:
	// Window management
	int WindowHandle;
	int WinX,WinY;

	// Input
	bool LeftDown,MiddleDown,RightDown;
	int MouseX,MouseY;

	// Components
	ShaderProgram *Program;
	Camera *Cam;

	Point* Goal;
	Chain* MainChain;

	bool moveCam;
	

};

////////////////////////////////////////////////////////////////////////////////
