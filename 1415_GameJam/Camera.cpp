#include "flib.h"
#include "flib_vec2.h"
#include "Camera.h"
#include "Floor.h"

TGfxVec2 TCamera::m_tWorldPosition;

TCamera::TCamera()
{

}

TCamera::~TCamera()
{

}


void TCamera::S_Initialize()
{
	m_tWorldPosition = TGfxVec2(GfxGetDisplaySizeX() / 2.f, GfxGetDisplaySizeY() / 2.f);
}

void TCamera::S_Update()
{

}

void TCamera::S_Render()
{

}

void TCamera::S_Scroll(float fXVelocity)
{
	m_tWorldPosition.x += fXVelocity;
	
	if (m_tWorldPosition.x < (TFloor::GetPosition().x - TFloor::GetLeftSize()))
	{
		m_tWorldPosition.x = TFloor::GetPosition().x - TFloor::GetLeftSize();
	}
	if (m_tWorldPosition.x >(TFloor::GetPosition().x + TFloor::GetRightSize()))
	{
		m_tWorldPosition.x = TFloor::GetPosition().x + TFloor::GetRightSize();
	}
}