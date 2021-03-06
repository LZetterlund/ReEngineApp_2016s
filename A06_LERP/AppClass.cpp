#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here
	//Use the clock... "Luke"
	static DWORD startTimeSystem = GetTickCount();
	DWORD timeApplication = GetTickCount() - startTimeSystem;
	float timer = timeApplication / 1000.0f;
	m_pMeshMngr->PrintLine("Time is: " + std::to_string(timer));
	timer += 0.1f;

	//could be done more effeciently, but this works fine
	int numOfPositions = 11;
	std::vector<vector3> positions;
	positions.push_back(vector3(-4.0f, -2.0f, 5.0f));
	positions.push_back(vector3(1.0f, -2.0f, 5.0f));
	positions.push_back(vector3(-3.0f, -1.0f, 3.0f));
	positions.push_back(vector3(2.0f, -1.0f, 3.0f));
	positions.push_back(vector3(-2.0f, 0.0f, 0.0f));
	positions.push_back(vector3(3.0f, 0.0f, 0.0f));
	positions.push_back(vector3(-1.0f, 1.0f, -3.0f));
	positions.push_back(vector3(4.0f, 1.0f, -3.0f));
	positions.push_back(vector3(0.0f, 2.0f, -5.0f));
	positions.push_back(vector3(5.0f, 2.0f, -5.0f));
	positions.push_back(vector3(1.0f, 3.0f, -5.0f));

	//temperoarilt using 11 just because
	for (int i = 0; i < numOfPositions; i++) {
		matrix4 positionMatrix = glm::translate(positions[i]) * glm::scale(vector3(0.1f));
		m_pMeshMngr->AddSphereToRenderList(positionMatrix, RERED, WIRE | SOLID);
	}
	//3 seconds from point to point modulus the number of points gives the index of the next point to be used
	int currentPos = static_cast<int>(std::floor(timer)) / 3 % numOfPositions;
	//this number is used to be mapped as the max value against the timer in the MapValue function
	float currentMaxTimer = (static_cast<float>(currentPos)+1) * 3;

	//fmod 33.0f because if it takes 3 seconds to get from point to point, once we reach the eleventh point that number should act like 0 again
	float timerMapped = MapValue(std::fmodf(timer, 33.0f), currentMaxTimer-3, currentMaxTimer, 0.0f, 1.0f);
	matrix4 m4WallEye;
	vector3 v3lerp;
	//v3lerp = positions[currentPos];
	if (currentPos == 0) {
		v3lerp = glm::lerp(positions[numOfPositions - 1], positions[0], timerMapped);
	}
	else {
		v3lerp = glm::lerp(positions[currentPos-1], positions[currentPos], timerMapped);
	}
	m4WallEye = glm::translate(v3lerp);
	m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");

#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}