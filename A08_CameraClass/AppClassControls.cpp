#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	//Flag for the modifier
	bool bModifier = false;
	float fSpeed = 0.01f;

	//ON PRESS/RELEASE
#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		//m_pCameraMngr->MoveForward(fSpeed);
		m_pCamera->MoveForward(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		//m_pCameraMngr->MoveForward(-fSpeed);
		m_pCamera->MoveForward(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		//m_pCameraMngr->MoveSideways(-fSpeed);
		m_pCamera->MoveSideways(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		//m_pCameraMngr->MoveSideways(fSpeed);
		m_pCamera->MoveSideways(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		//m_pCameraMngr->MoveVertical(-fSpeed);
		m_pCamera->MoveVertical(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		//m_pCameraMngr->MoveVertical(fSpeed);
		m_pCamera->MoveVertical(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		//m_pCameraMngr->MoveVertical(fSpeed);
		m_pCamera->SetPosition(vector3(0.0f,0.0f,0.0f));

	//Exit the program
#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL))
#pragma endregion
}

void AppClass::ProcessMouse(void)
{
	float fSpeed = 0.01f;
	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

								//Initialize the position of the pointer to the middle of the screen
	CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
	CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;

	//Calculate the position of the mouse and store it
	POINT pt;
	GetCursorPos(&pt);
	MouseX = pt.x;
	MouseY = pt.y;

	//Calculate the difference in view with the angle
	float fAngleX = 0.0f;
	float fAngleY = 0.0f;
	float fDeltaMouse = 0.0f;
	if (MouseX < CenterX)
	{
		fDeltaMouse = static_cast<float>(CenterX - MouseX);
		fAngleY += fDeltaMouse * fSpeed;
	}
	else if (MouseX > CenterX)
	{
		fDeltaMouse = static_cast<float>(MouseX - CenterX);
		fAngleY -= fDeltaMouse * fSpeed;
	}

	if (MouseY < CenterY)
	{
		fDeltaMouse = static_cast<float>(CenterY - MouseY);
		fAngleX -= fDeltaMouse * fSpeed;
	}
	else if (MouseY > CenterY)
	{
		fDeltaMouse = static_cast<float>(MouseY - CenterY);
		fAngleX += fDeltaMouse * fSpeed;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		//Change the Yaw and the Pitch of the camera
		//m_pCameraMngr->ChangeYaw(fAngleY * 3.0f);
		//m_pCameraMngr->ChangePitch(-fAngleX * 3.0f);
		m_pCamera->ChangeYaw(fAngleY * 3.0f);
		m_pCamera->ChangePitch(-fAngleX * 3.0f);
		SetCursorPos(CenterX, CenterY);//Position the mouse in the center
	}
}