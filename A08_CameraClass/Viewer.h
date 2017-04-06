#ifndef __VIEWER_H_
#define __VIEWER_H_

#include "RE\ReEngAppClass.h"

class Viewer
{
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
	/*
	MyPrimitive
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	Viewer();
	/* Copy Constructor */
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Viewer(const Viewer& other);
	/* Copy Assignment Operator */
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	virtual Viewer& operator=(const Viewer& other);

	/* Destructor */
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Viewer(void);

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
#endif //__VIEWER_H_
