/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/09
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
//#include <chrono>

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class AppClass : public ReEngAppClass
{
	PrimitiveClass* m_pCone = nullptr;
	PrimitiveClass* m_pCylinder = nullptr;

	//CAMERA STUFF
	vector3 m_v3Position = vector3(0.0f, 0.0f, 5.0f);
	vector3 m_v3Target = vector3(0.0f, 0.0f, 0.0f);
	vector3 m_v3Top = vector3(0.0f, 1.0f, 0.0f);

	vector3 m_v3Forward = vector3(0.0f, 0.0f, -1.0f);
	vector3 m_v3Upward = vector3(0.0f, 1.0f, 0.0f);
	vector3 m_v3Rightward = vector3(1.0f, 0.0f, 0.0f);

	vector3 m_v3PitchYawRoll = vector3(0.0f);

	matrix4 m_m4Projection = matrix4(1.0f);
	matrix4 m_m4View = matrix4(1.0f);
	//end camera stuff
public:
	typedef ReEngAppClass super;

	/* Constructor */
	AppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow) : super(hInstance, lpCmdLine, nCmdShow) {}

	/*
	InitWindow
	Initialize ReEng variables necessary to create the window
	*/
	virtual void InitWindow(String a_sWindowName);

	/*
	InitVariables
	Initializes user specific variables, this is executed right after InitApplicationVariables,
	the purpose of this member function is to initialize member variables specific for this lesson
	*/
	virtual void InitVariables(void);

	/*
	Update
	Updates the scene
	*/
	virtual void Update(void);

	/*
	Display
	Displays the scene
	*/
	virtual void Display(void);

	/*
	ProcessKeyboard
	Manage the response of key presses
	*/
	virtual void ProcessKeyboard(void);


	/*
	USAGE: Manage the response of mouse position and clicks
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessMouse(void);

	/*
	Release
	Releases the application
	IF INHERITED AND OVERRIDEN MAKE SURE TO RELEASE BASE POINTERS (OR CALL BASED CLASS RELEASE)
	*/
	virtual void Release(void);

	/*
	USAGE: Reads the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ReadConfig(void) final {}

	/*
	USAGE: Writes the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void WriteConfig(void) final {}


	/*
	USAGE: Gets the View matrix from the camera
	ARGUMENTS: ---
	OUTPUT:
	*/
	matrix4 GetView(void);
	/*
	USAGE: Gets the Projection matrix from the camera
	ARGUMENTS: Either a Perspective or an Orthographic projection depending on the bool argument
	OUTPUT:
	*/
	matrix4 GetProjection(bool bOrtographic);

	/*
	USAGE:  Sets the position of the camera
	ARGUMENTS: ---
	OUTPUT:
	*/
	void SetPosition(vector3 a_v3Position);
	/*
	USAGE: Sets the target of the camera to the specified position
	ARGUMENTS:
	- vector3 a_vTarget -> point to look at
	OUTPUT:
	*/
	void SetTarget(vector3 a_v3Target);

	/*
	USAGE:  Sets the Upward vector of the camera
	ARGUMENTS: input
	OUTPUT: ---
	*/
	void SetUp(vector3 a_v3Input);

	/*
	USAGE: Translates the camera forward or backward
	ARGUMENTS:
	OUTPUT: ---
	*/
	void MoveForward(float a_fDistance);
	/*
	USAGE: Translates the camera Upward or downward
	ARGUMENTS:
	OUTPUT: ---
	*/
	void MoveVertical(float a_fDistance);
	/*
	USAGE: Translates the camera right or left
	ARGUMENTS:
	OUTPUT: ---
	*/
	void MoveSideways(float a_fDistance);
	/*
	USAGE: Rotates the camera Pitch
	ARGUMENTS:
	OUTPUT: ---
	*/
	void ChangePitch(float a_fDegree);
	/*
	USAGE: Rotates the camera Yaw
	ARGUMENTS:
	OUTPUT: ---
	*/
	void ChangeYaw(float a_fDegree);
	/*
	USAGE: Rotates the camera Roll
	ARGUMENTS:
	OUTPUT: ---
	*/
	void ChangeRoll(float a_fDegree);
};

#endif //__APPLICATION_H_
