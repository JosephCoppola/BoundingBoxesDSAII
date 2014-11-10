#include "ApplicationClass.h"
void ApplicationClass::Update (void)
{
	m_pSystem->UpdateTime(); //Update the system
	printf("FPS: %d \r", m_pSystem->FPS);//print the Frames per Second

	//Check if the objects models have been read
	static bool bObjectSelected = false;
	if(!bObjectSelected)
	{
		if(m_pModelManager->GetNumberOfInstances() > 0)
		{
			m_sSelectedObject = m_pModelManager->m_vInstance[0]->GetName();
			bObjectSelected = true;
		}
	}

	//Arcball rotation
	if(m_bArcBall == true)
		ArcBall();

	//First person camera movement
	if(m_bFPC == true)
		CameraRotation();

	m_pBSMngr->Update();
	m_pBBMngr->Update();
}

void ApplicationClass::Display3X (void) //for OpenGL 3.X Applications
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear the window

	m_pModelManager->RenderInstance();

	m_pBSMngr->Render();
	m_pBBMngr->Render();

	m_pGLSystem->GLSwapBuffers();
}