#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma endregion
#pragma region FEEL FREE TO USE THIS CLOCK
	//Calculate delta and total times
	static double dTotalTime = 0.0; //Total time of the simulation
	double dDeltaTime = m_pSystem->LapClock(); //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences 
#pragma endregion
#pragma region YOUR CODE GOES HERE
	m_m4Steve = glm::mat4(1.0f); // same as m_m4Steve = IDENTITY_M4; setting the identity to steve

	float value5 = fmodf(static_cast<float>(dTotalTime), 5.0f);

	float value10 = fmodf(static_cast<float>(dTotalTime), 10.0f);

	if (value10 > 5) {
		value10 = 5 - value5;
	}

	float mappedValue = MapValue(value5, 0.0f, 5.0f, 90.0f, 450.0f);

	//float transValue = MapValue(value5, 0.0f, 10.0f, 0.0f, 5.0f);

	matrix4 steveOrbit = glm::rotate(IDENTITY_M4, mappedValue, vector3(0, 0, 1.0f));

	matrix4 rotateZ = glm::rotate(IDENTITY_M4, -90.0f, vector3(0.0f, 0.0f, 1.0f));

	matrix4 steveDistance = glm::translate(vector3(value10, 0, 0));

	m_m4Steve = steveOrbit * steveDistance * rotateZ;
#pragma endregion
#pragma region DOES NOT NEED CHANGES
	//Set the model matrix
	m_pMeshMngr->SetModelMatrix(m_m4Steve, "Steve");
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("Seconds:");
	m_pMeshMngr->PrintLine(std::to_string(dTotalTime), RERED);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}
