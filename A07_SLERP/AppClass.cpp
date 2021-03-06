#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("SLERP - Luke Zett"); // Window Name

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	m_pCameraMngr->SetPositionTargetAndView(vector3(12.12f, 28.52f, 11.34f), ZERO_V3, REAXISY);

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);

	m_m4Sun = glm::scale(IDENTITY_M4, 5.936f, 5.936f, 5.936f);
	m_m4Earth = glm::scale(IDENTITY_M4, 0.524f, 0.524f, 0.524f);
	m_m4Moon = glm::scale(IDENTITY_M4, 0.524f * 0.27f, 0.524f * 0.27f, 0.524f * 0.27f);

	//Loading the models
	m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Sun");
	m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", "Earth");
	m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", "Moon");

	//Setting the days duration
	m_fDay = 1.0f;
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;

	//Earth Orbit
	double fEarthHalfOrbTime = 182.5f * m_fDay; //Earths orbit around the sun lasts 365 days / half the time for 2 stops
	float fEarthHalfRevTime = 0.5f * m_fDay; // Move for Half a day
	float fMoonHalfOrbTime = 14.0f * m_fDay; //Moon's orbit is 28 earth days, so half the time for half a route

	//EARTH STUFF
	glm::quat firstEarthOrbitQuat = glm::quat(vector3(0, 11.0f, 0));
	glm::quat secondEarthOrbitQuat = glm::quat(vector3(0, -11.0f, 0));
	float fPercentage = static_cast<float>(fRunTime / fEarthHalfOrbTime);
	glm::quat earthOrbitQuat = glm::mix(firstEarthOrbitQuat, secondEarthOrbitQuat, fPercentage);

	glm::quat firstEarthRotQuat = glm::quat(vector3(-1.5f, 0, 0));
	glm::quat secondEarthRotQuat = glm::quat(vector3(1.5f, 0, 0));
	fPercentage = static_cast<float>(fRunTime) / fEarthHalfRevTime;
	glm::quat earthRotQuat = glm::mix(firstEarthRotQuat, secondEarthRotQuat, fPercentage);

	matrix4 distanceEarth = glm::translate(11.0f, 0.0f, 0.0f);

	m_m4Earth = glm::mat4_cast(earthOrbitQuat) * glm::mat4_cast(earthRotQuat) * distanceEarth;

	//MOON STUFF
	matrix4 EarthPos = IDENTITY_M4;
	EarthPos[3] = m_m4Earth[3];

	//I tried rotating around the earth using this, but could only get the moon to rotate in place
	glm::quat firstMoonOrbitQuat = glm::quat(vector3(0, 0, 2.0f));
	glm::quat secondMoonOrbitQuat = glm::quat(vector3(0, 0, -2.0f));
	fPercentage = static_cast<float>(fRunTime / fMoonHalfOrbTime);
	glm::quat moonOrbitQuat = glm::mix(firstMoonOrbitQuat, secondMoonOrbitQuat, fPercentage);

	matrix4 distanceMoon = glm::translate(2.0f, 0.0f, 0.0f);

	m_m4Moon = EarthPos * distanceMoon * glm::mat4_cast(moonOrbitQuat);

	m_m4Moon = glm::scale(m_m4Moon, 0.524f * 0.27f, 0.524f * 0.27f, 0.524f * 0.27f);
	//m_m4Moon = glm::rotate(m_m4Moon, fPercentage, vector3(0.0f, 0.0f, 1.0f));

	//Setting the matrices
	m_pMeshMngr->SetModelMatrix(m_m4Sun, "Sun");
	m_pMeshMngr->SetModelMatrix(m_m4Earth, "Earth");
	m_pMeshMngr->SetModelMatrix(m_m4Moon, "Moon");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	int nEarthOrbits = static_cast<float>(fRunTime) / (fEarthHalfOrbTime * 2);
	int nEarthRevolutions = static_cast<float>(fRunTime) / (fEarthHalfRevTime * 2);
	int nMoonOrbits = static_cast<float>(fRunTime) / (fMoonHalfOrbTime * 2);;

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	
	m_pMeshMngr->Print("Time:");
	m_pMeshMngr->PrintLine(std::to_string(fRunTime));

	m_pMeshMngr->Print("Day:");
	m_pMeshMngr->PrintLine(std::to_string(m_fDay));

	m_pMeshMngr->Print("E_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthOrbits));

	m_pMeshMngr->Print("E_Revolutions:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthRevolutions));

	m_pMeshMngr->Print("M_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nMoonOrbits));

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default:
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}