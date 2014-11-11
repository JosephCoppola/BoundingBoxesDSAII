#include "ApplicationClass.h"
#include <locale>
#include <codecvt>
#include <string>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

ApplicationClass* ApplicationClass::m_pInstance = nullptr;
ApplicationClass* ApplicationClass::GetInstance( HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new ApplicationClass( );
		m_pInstance->Init(hInstance, lpCmdLine, nCmdShow);
	}
	return m_pInstance;
}

ApplicationClass::ApplicationClass()
{
	m_pSystem = nullptr;
	m_pWindow = nullptr;
	m_pGLSystem = nullptr;
	m_pModelManager = nullptr;
	m_pLightMngr = nullptr;
}
ApplicationClass::ApplicationClass(ApplicationClass const& other){}
ApplicationClass& ApplicationClass::operator=(ApplicationClass const& other){	return *this; }
ApplicationClass::~ApplicationClass()
{
	Release();
	ReleaseInstance();
};

void ApplicationClass::ReleaseInstance()
{
	if(m_pBSMngr != nullptr)
	{
		m_pBSMngr->ReleaseInstance();
	}
	if( m_pLightMngr != nullptr)
	{
		m_pLightMngr->ReleaseInstance();
	}
	if(	m_pModelManager != nullptr)
	{
		m_pModelManager->ReleaseInstance();
	}
	if(	m_pGLSystem != nullptr)
	{
		m_pGLSystem->ReleaseInstance();
	}
	if( m_pWindow != nullptr)
	{
		delete m_pWindow;
		m_pWindow = nullptr;
	}
	if(	m_pSystem != nullptr)
	{
		m_pSystem->ReleaseInstance();
	}
}

void ApplicationClass::Init( HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// Is this running out of Visual Studio?
	if(IsDebuggerPresent())
	{
		printf("Shaders: ");
		system("cmd.exe /C xcopy \"../Solution/Shaders\" \"Shaders\" /y /q");
		m_pWindow->CreateConsoleWindow();
	}

	m_pSystem = SystemClass::GetInstance();
	m_pLightMngr = LightManagerClass::GetInstance();
	pMatMngr = MaterialManagerClass::GetInstance();

	m_bForceNewConfig = false;
	InitAppSystem();

	ReadConfig();

	m_pWindow = new WindowClass( hInstance, nCmdShow, WndProc);
	m_pWindow->SetFullscreen(m_pSystem->IsWindowFullscreen());
	m_pWindow->SetBorderless(m_pSystem->IsWindowBorderless());

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wide = converter.from_bytes( m_pSystem->WindowName);

	m_pWindow->CreateMEWindow(wide.c_str(), m_pSystem->WindowWidth, m_pSystem->WindowHeight);
	
	m_pGLSystem = GLSystemClass::GetInstance();
	//Check if OPENGL Context is enabled
	if(m_pSystem->m_RenderingContext == OPENGL2X || m_pSystem->m_RenderingContext == OPENGL3X)
	{
		//Is old OpenGL enforced?
		if(m_pSystem->m_RenderingContext == OPENGL2X)
			m_pGLSystem->ForceOldOpenGL();
		
		//Create context
		m_pGLSystem->InitGLDevice(m_pWindow->GetHandler());

		//Verify what is the OpenGL rendering context and save it to system (3.x might fail, in which case 2.X)
		if(m_pGLSystem->IsNewOpenGLRunning())
			m_pSystem->m_RenderingContext = OPENGL3X;
		else
			m_pSystem->m_RenderingContext = OPENGL2X;

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}

	m_pCamera0 = CameraClass::GetInstance();
	m_pModelManager = ModelManagerClass::GetInstance();
	InitAppInternalVariables();
	InitAppVariables();

	printf("\n");
}

void ApplicationClass::ReadConfig(void)
{
	if(m_bForceNewConfig == true)
	{
		WriteConfig();
		return;
	}

	//If we are forcing the changes
	String sRoot = m_pSystem->m_pFolder->GetFolderRoot();
	String App = m_pSystem->ApplicationName;
	App = sRoot + App + ".cfg";

	FileReaderClass reader;
	if(reader.ReadFile(App.c_str()) == MEErrors::ERROR_FILE_MISSING)
	{
		WriteConfig();
		return;
	}
	reader.Rewind();
	while(reader.ReadNextLine() == RUNNING)
	{
		String sWord = reader.GetFirstWord();

		int nLenght  = reader.m_sLine.length();
		char* zsTemp = new char[nLenght];
		
		if(sWord == "Fullscreen:")
		{
			int nValue;
			sscanf_s(reader.m_sLine.c_str(), "Fullscreen: %d", &nValue);
			if(nValue == 0)
				m_pSystem->SetWindowFullscreen(false);
			else
				m_pSystem->SetWindowFullscreen(true);
		}
		else if(sWord == "Borderless:")
		{
			int nValue;
			sscanf_s(reader.m_sLine.c_str(), "Borderless: %d", &nValue);
			if(nValue == 0)
				m_pSystem->SetWindowBorderless(false);
			else
				m_pSystem->SetWindowBorderless(true);
		}
		else if(sWord == "Context:")
		{
			sscanf_s(reader.m_sLine.c_str(), "Context: %s", zsTemp, nLenght);
			String sTemp = zsTemp;
			if(sTemp == "OPENGL2X")
				m_pSystem->m_RenderingContext = OPENGL2X;
			else if(sTemp == "OPENGL3X")
				m_pSystem->m_RenderingContext = OPENGL3X;
			else if(sTemp == "DIRECTX")
				m_pSystem->m_RenderingContext = DIRECTX;
		}
		else if(sWord == "Resolution:")
		{
			int nValue1;
			int nValue2;
			sscanf_s(reader.m_sLine.c_str(), "Resolution: [ %d x %d ]", &nValue1,  &nValue2);
			m_pSystem->WindowWidth = nValue1;
			m_pSystem->WindowHeight = nValue2;
		}
		else if(sWord == "Ambient:")
		{
			float fValueX;
			float fValueY;
			float fValueZ;
			sscanf_s(reader.m_sLine.c_str(), "Ambient: [%f,%f,%f]", &fValueX, &fValueY, &fValueZ);
			m_pLightMngr->SetColor(vector3(fValueX, fValueY, fValueZ), 0);
		}
		else if(sWord == "AmbientPower:")
		{
			float fValue;
			sscanf_s(reader.m_sLine.c_str(), "AmbientPower: %f", &fValue);
			m_pLightMngr->SetIntensity(fValue, 0);
		}
		else if(sWord == "Data:")
		{
			sscanf_s(reader.m_sLine.c_str(), "Data: %s", zsTemp, nLenght);
			m_pSystem->m_pFolder->SetFolderData( zsTemp );
		}
		else if(sWord == "3DS:")
		{
			sscanf_s(reader.m_sLine.c_str(), "3DS: %s", zsTemp, nLenght);
			m_pSystem->m_pFolder->SetFolderM3DS( zsTemp );
		}
		else if(sWord == "BTO:")
		{
			sscanf_s(reader.m_sLine.c_str(), "BTO: %s", zsTemp, nLenght);
			m_pSystem->m_pFolder->SetFolderMBTO( zsTemp );
		}
		else if(sWord == "FBX:")
		{
			sscanf_s(reader.m_sLine.c_str(), "FBX: %s", zsTemp, nLenght);
			m_pSystem->m_pFolder->SetFolderMFBX( zsTemp );
		}
		else if(sWord == "OBJ:")
		{
			sscanf_s(reader.m_sLine.c_str(), "OBJ: %s", zsTemp, nLenght);
			m_pSystem->m_pFolder->SetFolderMOBJ( zsTemp );
		}
		else if(sWord == "POM:")
		{
			sscanf_s(reader.m_sLine.c_str(), "POM: %s", zsTemp, nLenght);
			m_pSystem->m_pFolder->SetFolderMPOM( zsTemp );
		}
		else if(sWord == "Level:")
		{
			sscanf_s(reader.m_sLine.c_str(), "Level: %s", zsTemp, nLenght);
			m_pSystem->m_pFolder->SetFolderLVL( zsTemp );
		}
		else if(sWord == "Textures:")
		{
			sscanf_s(reader.m_sLine.c_str(), "Textures: %s", zsTemp, nLenght);
			m_pSystem->m_pFolder->SetFolderTextures( zsTemp );
		}

		delete[] zsTemp;
		zsTemp = nullptr;
	}
	reader.CloseFile();
	
}

void ApplicationClass::WriteConfig(void)
{
	String sRoot = m_pSystem->m_pFolder->GetFolderRoot();
	String App = m_pSystem->ApplicationName;
	App = sRoot + App + ".cfg";

	FILE *pFile; 
	fopen_s(&pFile, App.c_str(),"w");
	if(!pFile)	//If we couldn't create the file we exit without changes.
		return;

	rewind(pFile);
	fprintf(pFile,"# Configuration file for the program: %s", m_pSystem->GetAppName().c_str());
	
	fprintf(pFile,"\n\nFullscreen: ");
	if(m_pSystem->IsWindowFullscreen())
		fprintf(pFile,"1");
	else
		fprintf(pFile,"0");

	fprintf(pFile,"\nBorderless: ");
	if(m_pSystem->IsWindowBorderless())
		fprintf(pFile,"1");
	else
		fprintf(pFile,"0");

	fprintf(pFile,"\nContext: OPENGL3X"); //Only openGL3X context is supported ATM

	//if(m_pSystem->m_RenderingContext == OPENGL2X)
	//	fprintf(pFile,"OPENGL2X");
	//else if(m_pSystem->m_RenderingContext == OPENGL3X)
	//	fprintf(pFile,"OPENGL3X");
	//else if(m_pSystem->m_RenderingContext == DIRECTX)
	//	fprintf(pFile,"DIRECTX");


	fprintf(pFile,"\n\n# Resolution: [ 640 x 480 ]");
	fprintf(pFile,"\n# Resolution: [ 1280 x 720 ]");
	fprintf(pFile,"\n# Resolution: [ 1680 x 1050 ]");
	fprintf(pFile,"\n# Resolution: [ 1920 x 1080 ]");
	fprintf(pFile,"\n# Resolution: [ 2650 x 1440 ]");
	fprintf(pFile,"\nResolution: [ %d x %d ]", m_pSystem->WindowWidth, m_pSystem->WindowHeight);

	fprintf(pFile,"\n\nAmbient: [%.2f,%.2f,%.2f]",
		m_pLightMngr->GetColor(0).r, m_pLightMngr->GetColor(0).g, m_pLightMngr->GetColor(0).b);
	fprintf(pFile,"\nAmbientPower: %.2f", m_pLightMngr->GetIntensity(0));

	fprintf(pFile,"\n\n# Folders:");
	
	fprintf(pFile,"\nData:		%s", m_pSystem->m_pFolder->GetFolderData().c_str());
	fprintf(pFile,"\n3DS:		%s", m_pSystem->m_pFolder->GetFolderM3DS().c_str());
	fprintf(pFile,"\nBTO:		%s", m_pSystem->m_pFolder->GetFolderMBTO().c_str());
	fprintf(pFile,"\nFBX:		%s", m_pSystem->m_pFolder->GetFolderMFBX().c_str());
	fprintf(pFile,"\nOBJ:		%s", m_pSystem->m_pFolder->GetFolderMOBJ().c_str());
	fprintf(pFile,"\nLevel:		%s", m_pSystem->m_pFolder->GetFolderLVL().c_str());
	fprintf(pFile,"\nTextures:	%s", m_pSystem->m_pFolder->GetFolderTextures().c_str());

	fclose(pFile);
}

void ApplicationClass::Reshape(int a_nWidth, int a_nHeight)
{
}

void ApplicationClass::Run (void)
{
	MSG msg = {0};
	while( WM_QUIT != msg.message )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			ProcessKeyboard();
			ProcessMouse();
			ProcessJoystick();
			Update();
			switch (m_pSystem->m_RenderingContext)
			{
			case DIRECTX:
				DisplayDX();
				break;
			case OPENGL2X:
				Display2X();
				break;
			case OPENGL3X:
				Display3X();
				break;
			}
		}
		Idle();
	}
}

void ApplicationClass::DisplayDX (void) //for DirectX Applications
{
}

void ApplicationClass::Display2X (void) //for OpenGL 2.X Applications
{
	m_pGLSystem->DrawOldGLScene();
}
//--------
void ApplicationClass::InitAppSystem(void)
{
	//m_bForceNewConfig = true;

	m_pSystem->WindowWidth = 1280;
	m_pSystem->WindowHeight = 720;
	m_pSystem->WindowName = "Box Collisions";
	m_pSystem->m_RenderingContext = OPENGL3X;
	m_pSystem->WindowFullscreen = false;
	m_pSystem->WindowBorderless = false;
}
void ApplicationClass::InitAppVariables()
{

	m_bArcBall = false;

	CreateAxisFrame();

	m_pBSMngr = BoundingSphereManager::GetInstance();
	m_pBBMngr = BoundingBoxManager::GetInstance();

	m_pModelManager->LoadModel("MC_Steve.obj", "Steve", glm::translate(matrix4(1.0f), vector3(0.0f,0.0f,0.0f)));
	m_pModelManager->LoadModel("MC_Cow.obj", "Cow", glm::translate(matrix4(1.0f), vector3(-4.0f,0.0f,0.0f)));
	m_pModelManager->LoadModel("MC_Pig.obj", "Pig", glm::translate(matrix4(1.0f), vector3(-2.0f,0.0f,0.0f)));
	m_pModelManager->LoadModel("MC_Creeper.obj", "Creeper", glm::translate(matrix4(1.0f), vector3(2.0f,0.0f,0.0f)));
	m_pModelManager->LoadModel("MC_Zombie.obj", "Zombie", glm::translate(matrix4(1.0f), vector3(4.0f,0.0f,0.0f)));
}
void ApplicationClass::InitAppInternalVariables()
{
	if(m_pSystem->m_RenderingContext != OPENGL3X)
		exit(0);

	m_bFPC = false;

	m_pCamera0->SetPosition(vector3( 0.0f, 2.0f, 7.0f ));
	
	m_pLightMngr->SetPosition( glm::vec3( 0, 0, 10) );
	m_pLightMngr->SetColor( glm::vec3( 1, 1, 1) );
	m_pLightMngr->SetIntensity ( 5.0f ); //Rotating Light
	m_pLightMngr->SetIntensity ( 0.75f, 0 ); //Ambient light (Ambient Light is always the first light, or light[0])

	m_sSelectedObject = "None";
}

void ApplicationClass::CreateAxisFrame(void)
{
	LineManagerClass* pLineMngr = LineManagerClass::GetInstance();
	pLineMngr->AddLine(vector3(-100.0f,   0.0f,   0.0f), vector3( 100.0f,   0.0f,   0.0f), MERED);
	pLineMngr->AddLine(vector3(   0.0f,-100.0f,   0.0f), vector3(   0.0f, 100.0f,   0.0f), MEGREEN);
	pLineMngr->AddLine(vector3(   0.0f,   0.0f,-100.0f), vector3(   0.0f,   0.0f, 100.0f), MEBLUE);
}

void ApplicationClass::Release()
{
	m_pLightMngr->ReleaseInstance();
	
	LineManagerClass* pLineMngr = LineManagerClass::GetInstance();
	pLineMngr->ReleaseInstance();

	BoxManagerClass* pBoxMngr = BoxManagerClass::GetInstance();
	pBoxMngr->ReleaseInstance();
}

void ApplicationClass::Idle (void)
{
	m_bFPC = true;
}
