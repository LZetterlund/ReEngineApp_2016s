#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("E10_Projections"); // Window Name
}

//CAMERA METHODS
matrix4 AppClass::GetView()
{
	//m_m4View = m_m4View * glm::(m_v3PitchYawRoll);
	return m_m4View;
}

matrix4 AppClass::GetProjection(bool bOrthographic)
{
	if(bOrthographic)
	m_m4Projection = glm::ortho(-10.80f, 10.80f, -7.68f, 7.68f, 0.01f, 1000.0f);

	else m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	
	return m_m4Projection;
}

void AppClass::SetPosition(vector3 v3Position)
{
	m_v3Position = v3Position;

	m_m4View = glm::translate(IDENTITY_M4,v3Position);
	m_v3Forward = vector3(0.0f, 0.0f, -1.0f);
	m_v3Upward = vector3(0.0f, 1.0f, 0.0f);
	m_v3Rightward = vector3(1.0f, 0.0f, 0.0f);
}

void AppClass::SetTarget(vector3 v3Target)
{
	m_v3Target = v3Target;
	m_m4View = glm::lookAt(v3Target, vector3(0.0f,0.0f,0.0f), m_v3Upward);
}

void AppClass::SetUp(vector3 v3Up)
{
	m_v3Upward = v3Up;
}

void AppClass::MoveForward(float a_fDistance)
{
	m_m4View = m_m4View * glm::translate(m_v3Forward * a_fDistance);
}

void AppClass::MoveSideways(float a_fDistance)
{
	m_m4View = m_m4View * glm::translate(m_v3Rightward * a_fDistance);
}

void AppClass::MoveVertical(float a_fDistance)
{
	m_m4View = m_m4View * glm::translate(m_v3Upward * a_fDistance);
}

void AppClass::ChangePitch(float a_fDistance)
{
	m_v3PitchYawRoll = m_v3PitchYawRoll * quaternion(vector3(glm::radians(a_fDistance), 0.0f, 0.0f));
	m_v3Forward = m_v3Forward * quaternion(vector3(glm::radians(a_fDistance), 0.0f, 0.0f));
	m_v3Rightward = m_v3Rightward * quaternion(vector3(glm::radians(a_fDistance), 0.0f, 0.0f));
	//m_v3Upward = m_v3Upward * quaternion(vector3(glm::radians(a_fDistance), 0.0f, 0.0f));

	m_m4View = m_m4View * glm::toMat4(quaternion(vector3(glm::radians(a_fDistance), 0.0f, 0.0f)));
}

void AppClass::ChangeRoll(float a_fDistance)
{
	m_v3PitchYawRoll = m_v3PitchYawRoll * quaternion(vector3(0.0f, 0.0f, glm::radians(a_fDistance)));
	m_v3Forward = m_v3Forward * quaternion(vector3(0.0f, 0.0f, glm::radians(a_fDistance)));
	m_v3Rightward = m_v3Rightward * quaternion(vector3(0.0f, 0.0f, glm::radians(a_fDistance)));
	//m_v3Upward = m_v3Upward * quaternion(vector3(0.0f, 0.0f, glm::radians(a_fDistance)));
	m_m4View = m_m4View * glm::toMat4(quaternion(vector3(0.0f, 0.0f, glm::radians(a_fDistance))));
}

void AppClass::ChangeYaw(float a_fDistance)
{
	m_v3PitchYawRoll = m_v3PitchYawRoll * quaternion(vector3(0.0f, glm::radians(a_fDistance), 0.0f));
	m_v3Forward = m_v3Forward * quaternion(vector3(0.0f, glm::radians(a_fDistance), 0.0f));
	m_v3Rightward = m_v3Rightward * quaternion(vector3(0.0f, glm::radians(a_fDistance), 0.0f));
	//m_v3Upward = m_v3Upward * quaternion(vector3(0.0f, glm::radians(a_fDistance), 0.0f));
	m_m4View = m_m4View * glm::toMat4(quaternion(vector3(0.0f, glm::radians(a_fDistance), 0.0f)));
}

void AppClass::InitVariables(void)
{
	//Generate the Cone
	m_pCone = new PrimitiveClass();
	m_pCone->GenerateCone(1.0f, 1.0f, 10, RERED);

	//Generate the Cylinder
	m_pCylinder = new PrimitiveClass();
	m_pCylinder->GenerateCylinder(1.0f, 1.0f, 10, REGREEN);

	//Calculate the first projections
	//m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	//m_m4Projection = glm::ortho(-10.80f, 10.80f, -7.68f, 7.68f, 0.01f, 1000.0f);
	//m_m4View = glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	
	//Render the grid
	m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY);

	//Render the cone
	m_pCone->Render(GetProjection(false), GetView(), IDENTITY_M4);

	//Render the cylinder
	m_pCylinder->Render(GetProjection(false), GetView(), glm::translate(IDENTITY_M4, REAXISZ * -3.0f));

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	//Release the memory of the member fields
	SafeDelete(m_pCone);
	SafeDelete(m_pCylinder);

	//Release the memory of the inherited fields
	super::Release(); 
}