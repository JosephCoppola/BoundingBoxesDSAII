#include "ApplicationClass.h"
void ApplicationClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.1f;
	int nMesh = m_pModelManager->IdentifyInstance(m_sSelectedObject);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		exit(0);

	//Modifiers
#pragma region Modifiers

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		fSpeed += 1.0f;
		bModifier = true;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		fSpeed += 1.0f;
		bModifier = true;
	}
	
#pragma endregion
	//Light
#pragma region Light
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	{
		float fIntensity = m_pLightMngr->GetLight(0).Intensity;
		fIntensity -= 0.01f;
		if(fIntensity < 0)
			fIntensity = 0;
		m_pLightMngr->SetIntensity ( fIntensity, 0 );
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	{
		float fIntensity = m_pLightMngr->GetLight(0).Intensity;
		fIntensity += 0.01f;
		m_pLightMngr->SetIntensity ( fIntensity, 0 );
	}
#pragma endregion
	//Shaders
#pragma region Shaders
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		m_pModelManager->SetShaderProgram(m_sSelectedObject, "Shaders\\MEShader.vs","Shaders\\MEShaderInv.fs", "Inverse"); 
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		m_pModelManager->SetShaderProgram(m_sSelectedObject, "MEShader"); 
	}
#pragma endregion
	//Model Positioning
#pragma region Model Positioning
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//matrix4 matrix = glm::translate( m_pModelManager->GetModelMatrix(m_sSelectedObject), vector3(-0.1f,0.0f,0.0f));
		matrix4 matrix = glm::translate( matrix4(1.0f), vector3(-0.1f,0.0f,0.0f)) * m_pModelManager->GetModelMatrix(m_sSelectedObject);
		m_pModelManager->SetModelMatrix(matrix, m_sSelectedObject);
		m_pBSMngr->SetModelMatrix(matrix, m_sSelectedObject);
		//m_pBBMngr->SetModelMatrix(matrix, m_sSelectedObject);
		
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		matrix4 matrix = glm::translate( matrix4(1.0f), vector3(0.1f,0.0f,0.0f)) * m_pModelManager->GetModelMatrix(m_sSelectedObject);
		m_pModelManager->SetModelMatrix(matrix, m_sSelectedObject);
		m_pBSMngr->SetModelMatrix(matrix, m_sSelectedObject);
		//m_pBBMngr->SetModelMatrix(matrix, m_sSelectedObject);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		matrix4 matrix;
		if(bModifier)
			matrix = glm::translate( matrix4(1.0f), vector3(0.0f,0.1f,0.0f)) * m_pModelManager->GetModelMatrix(m_sSelectedObject);
		else
			matrix = glm::translate( matrix4(1.0f), vector3(0.0f,0.0f,-0.1f)) * m_pModelManager->GetModelMatrix(m_sSelectedObject);
		
		m_pModelManager->SetModelMatrix(matrix, m_sSelectedObject);
		m_pBSMngr->SetModelMatrix(matrix, m_sSelectedObject);
		//m_pBBMngr->SetModelMatrix(matrix, m_sSelectedObject);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		matrix4 matrix;
		if(bModifier)
			matrix = glm::translate( matrix4(1.0f), vector3(0.0f,-0.1f,0.0f)) * m_pModelManager->GetModelMatrix(m_sSelectedObject);
		else
			matrix = glm::translate( matrix4(1.0f), vector3(0.0f,0.0f,0.1f)) * m_pModelManager->GetModelMatrix(m_sSelectedObject);
		
		m_pModelManager->SetModelMatrix(matrix, m_sSelectedObject);
		m_pBSMngr->SetModelMatrix(matrix, m_sSelectedObject);
		//m_pBBMngr->SetModelMatrix(matrix, m_sSelectedObject);
	}
#pragma endregion
	//Model Loading
#pragma region Model Loading
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
	{
		FileReaderClass pFile;
		String sFileName = pFile.RetriveFileNameFromExplorer(L"OBJ Files (*.obj)\0*.obj\0WRL Files (*.wrl)\0*.wrl\0", L"obj");
		if(sFileName != "")
		{
			m_pModelManager->DeleteInstance();
			sFileName = pFile.GetFileNameAndExtension(sFileName);
			m_pModelManager->LoadModel(sFileName, sFileName);
		}
		m_sSelectedObject = sFileName;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
	{
		m_pModelManager->DeleteInstance(m_sSelectedObject);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
	{
		m_pModelManager->DeleteInstance();//Nuke em all
	}
#pragma endregion
	//Debug
#pragma region Debug
	static bool bWasF5Pressed = false; //Was pressed keeps its value for the rest of the program even if it leaves the scope
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5))//Check the current state to see if its pressed right now
	{
		bWasF5Pressed = true;//if it is flag it
	}
	else if(bWasF5Pressed == true)//if its not currently pressed but it was pressed last...
	{
		m_pBSMngr->RemoveSphere("ALL");//remove all spheres (if there are none currently nothing bad is going to happen)
		for(int nInstance = 0; nInstance < m_pModelManager->GetNumberOfInstances(); nInstance++)//for all instances...
		{
			String sInstance = m_pModelManager->GetInstanceName(nInstance);//Create spheres
			m_pBSMngr->AddSphere(sInstance);
		}
		m_pBSMngr->SetVisible(true, "ALL");//Make those spheres visible
		bWasF5Pressed = false;//reset the flag
	}
	
	static bool bWasF6Pressed = false; //Was pressed keeps its value for the rest of the program even if it leaves the scope
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F6))//Check the current state to see if its pressed right now
	{
		bWasF6Pressed = true;//if it is flag it
	}
	else if(bWasF6Pressed == true)//if its not currently pressed but it was pressed last...
	{
		//m_pBBMngr->RemoveBox("ALL");//remove all spheres (if there are none currently nothing bad is going to happen)
		//for(int nInstance = 0; nInstance < m_pModelManager->GetNumberOfInstances(); nInstance++)//for all instances...
		//{
		//	String sInstance = m_pModelManager->GetInstanceName(nInstance);//Create spheres
		//	m_pBBMngr->AddBox(sInstance);
		//}
		//m_pBBMngr->SetVisible(true, "ALL");//Make those spheres visible
		bWasF6Pressed = false;//reset the flag
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F7))
	{
		m_pBSMngr->RemoveSphere("ALL");
		//m_pBBMngr->RemoveBox("ALL");
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F8))
	{
		m_pModelManager->SetCoordinateSystemVisible(true, "ALL");
		m_pModelManager->SetBoundingSphereColor(MEMAGENTA, "ALL");
		m_pModelManager->SetBoundingSphereVisible(true, "ALL");

		/*m_pModelManager->SetBoundingSphereColor(MEGREEN, m_sSelectedObject);
		m_pModelManager->SetBoundingSphereVisible(true, m_sSelectedObject);*/
		
		/*BSClass* oBS = m_pModelManager->GetBoundingSphere(m_sSelectedObject);
		if(oBS != nullptr)
		{
			oBS->SetColor(MEBLUE);
			oBS->SetVisible(true);
		}*/
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F9))
	{
		if(bModifier)
		{
			m_pModelManager->SetDebugMode(false);
		}
		else
			m_pModelManager->SetDebugMode(true);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F10))
	{
		if(bModifier)
			m_pModelManager->SetShowAABB(false);
		else
			m_pModelManager->SetShowAABB(true);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
	{
		if(bModifier)
			m_pModelManager->SetShowOBB(false);
		else
			m_pModelManager->SetShowOBB(true);
	}
#pragma endregion
	//Camera
#pragma region Camera
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pCamera0->MoveForward(fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pCamera0->MoveForward(-fSpeed);
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pCamera0->MoveSideways(-fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pCamera0->MoveSideways(fSpeed);
	m_pCamera0->CalculateView();
#pragma endregion
}
void ApplicationClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;

	static bool bLeft_Released = false;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		bLeft_Released = true;
	}
	else
	{
		if(bLeft_Released == true)
		{
			m_pModelManager->SetDebug(false, "ALL");
			String sName = m_pModelManager->ShootRay(
														sf::Mouse::getPosition().x,
														sf::Mouse::getPosition().y,
														m_pCamera0,
														false
													);
			if(sName != "NULL")
			{
				m_sSelectedObject = sName;
				printf("\nObject: %s\n", sName.c_str());
			}
		}
		bLeft_Released = false;
	}
}
void ApplicationClass::ProcessJoystick(void)
{
	sf::Joystick::update();

	int nPad = 0;
	if(sf::Joystick::isConnected(nPad))
	{
		if(sf::Joystick::isButtonPressed(nPad, 4) && sf::Joystick::isButtonPressed(nPad, 5))
			exit(0);

		static float fAngleX = 0.0f;
		static float fAngleY = 0.0f;

		if(sf::Joystick::isButtonPressed(nPad, 8) && sf::Joystick::isButtonPressed(nPad, 9))	
		{
			fAngleX = 0.0f;
			fAngleY = 0.0f;
			m_pCamera0->SetPosition(glm::vec3( 0.0f, 0.0f, 10.0f));
		}

		float fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::Y);
		if(fDelta > 20 || fDelta < -20)
		{
			fDelta /= 1000.0f;
			m_pCamera0->MoveForward(-fDelta);
		}
		
		fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::X);
		if(fDelta > 20 || fDelta < -20)
		{
			fDelta /= 1000.0f;
			m_pCamera0->MoveSideways(fDelta);
		}

		fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::Z);
		if(fDelta > 20 || fDelta < -20)
		{
			fDelta /= 1000.0f;
			m_pCamera0->MoveVertical(fDelta);
		}

		fDelta = -sf::Joystick::getAxisPosition(nPad, sf::Joystick::R);
		if(fDelta > 25 || fDelta < -25)
		{
			fAngleX -= fDelta/10000.0f;
		}
		
		fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::U);
		if(fDelta > 25 || fDelta < -25)
		{
			fAngleY -= fDelta/10000.0f;
		}

		m_pCamera0->Rotate(fAngleX, fAngleY);
		m_pCamera0->CalculateView();
		
	}
}
void ApplicationClass::ArcBall(float a_fSensitivity)
{
	static matrix4 arcball = matrix4(1.0);
	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

	CenterX = m_pSystem->WindowX + m_pSystem->WindowWidth / 2;
	CenterY = m_pSystem->WindowY + m_pSystem->WindowHeight / 2;
	
	float DeltaMouse;
	POINT pt;

	GetCursorPos(&pt);
	
	MouseX = pt.x;
	MouseY = pt.y;

	SetCursorPos(CenterX, CenterY);

	static float fVerticalAngle = 0.0f;
	static float fHorizontalAngle = 0.0f;

	float fSpeed = 0.001f;

	if(MouseX < CenterX)
	{
		DeltaMouse = static_cast<float>(CenterX - MouseX);
		arcball = glm::rotate(arcball, a_fSensitivity * DeltaMouse, vector3(0.0f, 1.0f, 0.0f));
	}
	else if(MouseX > CenterX)
	{
		DeltaMouse = static_cast<float>(MouseX - CenterX);
		arcball = glm::rotate(arcball, -a_fSensitivity * DeltaMouse, vector3(0.0f, 1.0f, 0.0f));
	}

	if(MouseY < CenterY)
	{
		DeltaMouse = static_cast<float>(CenterY - MouseY);
		arcball = glm::rotate(arcball, a_fSensitivity * DeltaMouse, vector3(1.0f, 0.0f, 0.0f));
	}
	else if(MouseY > CenterY)
	{
		DeltaMouse = static_cast<float>(MouseY - CenterY);
		arcball = glm::rotate(arcball, -a_fSensitivity * DeltaMouse, vector3(1.0f, 0.0f, 0.0f));
	}

	//m_pCamera0->Rotate(fVerticalAngle, fHorizontalAngle);
	m_pModelManager->SetModelMatrix(arcball, m_sSelectedObject);
	m_pBSMngr->SetModelMatrix(arcball, m_sSelectedObject);
	//m_pBBMngr->SetModelMatrix(arcball, m_sSelectedObject);
	//m_pPrimitive->SetModelMatrix(arcball);
}
void ApplicationClass::CameraRotation(float a_fSpeed)
{
	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

	CenterX = m_pSystem->WindowX + m_pSystem->WindowWidth / 2;
	CenterY = m_pSystem->WindowY + m_pSystem->WindowHeight / 2;
	
	float DeltaMouse;
	POINT pt;

	GetCursorPos(&pt);
	
	MouseX = pt.x;
	MouseY = pt.y;

	SetCursorPos(CenterX, CenterY);

	static float fAngleX = 0.0f;
	static float fAngleY = 0.0f;

	if(MouseX < CenterX)
	{
		DeltaMouse = static_cast<float>(CenterX - MouseX);
		fAngleY += DeltaMouse * a_fSpeed;
	}
	else if(MouseX > CenterX)
	{
		DeltaMouse = static_cast<float>(MouseX - CenterX);
		fAngleY -= DeltaMouse * a_fSpeed;
	}

	if(MouseY < CenterY)
	{
		DeltaMouse = static_cast<float>(CenterY - MouseY);
		fAngleX -= DeltaMouse * a_fSpeed;
	}
	else if(MouseY > CenterY)
	{
		DeltaMouse = static_cast<float>(MouseY - CenterY);
		fAngleX += DeltaMouse * a_fSpeed;
	}
	m_pCamera0->Rotate(fAngleX, fAngleY);
}