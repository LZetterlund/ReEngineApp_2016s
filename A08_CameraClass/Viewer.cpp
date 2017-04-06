#include "Viewer.h"
Viewer::Viewer() { }
Viewer::Viewer(const Viewer& other) { }
Viewer& Viewer::operator=(const Viewer& other) { return *this; }
Viewer::~Viewer(void)
{ 
	//add things to delete
}

//CAMERA METHODS
matrix4 Viewer::GetView(void)
{
	//m_m4View = m_m4View * glm::(m_v3PitchYawRoll);
	return m_m4View;
}

matrix4 Viewer::GetProjection(bool bOrthographic)
{
	if (bOrthographic)
		m_m4Projection = glm::ortho(-10.80f, 10.80f, -7.68f, 7.68f, 0.01f, 1000.0f);

	else m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);

	return m_m4Projection;
}

void Viewer::SetPosition(vector3 v3Position)
{
	m_v3Position = v3Position;

	m_m4View = glm::translate(IDENTITY_M4, v3Position);
	m_v3Forward = vector3(0.0f, 0.0f, -1.0f);
	m_v3Upward = vector3(0.0f, 1.0f, 0.0f);
	m_v3Rightward = vector3(1.0f, 0.0f, 0.0f);
}

void Viewer::SetTarget(vector3 v3Target)
{
	m_v3Target = v3Target;
	m_m4View = glm::lookAt(v3Target, vector3(0.0f, 0.0f, 0.0f), m_v3Upward);
}

void Viewer::SetUp(vector3 v3Up)
{
	m_v3Upward = v3Up;
}

void Viewer::MoveForward(float a_fDistance)
{
	m_m4View = m_m4View * glm::translate(m_v3Forward * a_fDistance);
}

void Viewer::MoveSideways(float a_fDistance)
{
	m_m4View = m_m4View * glm::translate(m_v3Rightward * a_fDistance);
}

void Viewer::MoveVertical(float a_fDistance)
{
	m_m4View = m_m4View * glm::translate(m_v3Upward * a_fDistance);
}

void Viewer::ChangePitch(float a_fDistance)
{
	m_v3PitchYawRoll = m_v3PitchYawRoll * quaternion(vector3(glm::radians(a_fDistance), 0.0f, 0.0f));
	m_v3Forward = m_v3Forward * quaternion(vector3(glm::radians(a_fDistance), 0.0f, 0.0f));
	m_v3Rightward = m_v3Rightward * quaternion(vector3(glm::radians(a_fDistance), 0.0f, 0.0f));
	//m_v3Upward = m_v3Upward * quaternion(vector3(glm::radians(a_fDistance), 0.0f, 0.0f));

	m_m4View = m_m4View * glm::toMat4(quaternion(vector3(glm::radians(a_fDistance), 0.0f, 0.0f)));
}

void Viewer::ChangeRoll(float a_fDistance)
{
	m_v3PitchYawRoll = m_v3PitchYawRoll * quaternion(vector3(0.0f, 0.0f, glm::radians(a_fDistance)));
	m_v3Forward = m_v3Forward * quaternion(vector3(0.0f, 0.0f, glm::radians(a_fDistance)));
	m_v3Rightward = m_v3Rightward * quaternion(vector3(0.0f, 0.0f, glm::radians(a_fDistance)));
	//m_v3Upward = m_v3Upward * quaternion(vector3(0.0f, 0.0f, glm::radians(a_fDistance)));
	m_m4View = m_m4View * glm::toMat4(quaternion(vector3(0.0f, 0.0f, glm::radians(a_fDistance))));
}

void Viewer::ChangeYaw(float a_fDistance)
{
	m_v3PitchYawRoll = m_v3PitchYawRoll * quaternion(vector3(0.0f, glm::radians(a_fDistance), 0.0f));
	m_v3Forward = m_v3Forward * quaternion(vector3(0.0f, glm::radians(a_fDistance), 0.0f));
	m_v3Rightward = m_v3Rightward * quaternion(vector3(0.0f, glm::radians(a_fDistance), 0.0f));
	//m_v3Upward = m_v3Upward * quaternion(vector3(0.0f, glm::radians(a_fDistance), 0.0f));
	m_m4View = m_m4View * glm::toMat4(quaternion(vector3(0.0f, glm::radians(a_fDistance), 0.0f)));
}