
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Floor.h"



using namespace Generics;

namespace
{
	const float GRAVITY = 0.6f;
	const float MAX_FALL_SPEED = 30.0f;
}


TDynamic::TDynamic() :
TEntity(),
m_eDirection(),
m_fSpeed(0.0f),
m_tVelocity(0.0f, 0.0f),
m_iLastMove(0)
{
	
}

TDynamic::TDynamic(const TGfxVec2 & tPos, const TGfxVec2 & tSize, const float fSpeed) :
TEntity(tPos, tSize),
m_eDirection(),
m_fSpeed(fSpeed),
m_tVelocity(0.0f, 0.0f),
m_iLastMove(0)
{
	m_eDirection = GfxMathGetRandomInteger(0, 1) == 1 ? EDirection_Right : EDirection_Left;
}

TDynamic::~TDynamic()
{

}


void TDynamic::Update()
{
	SpecificUpdate();
	Move();
}

void TDynamic::Move()
{
	// Move on Y
	if (m_tPos.y < TFloor::S_GetPosition().y
		|| (m_tPos.x < TFloor::S_GetPosition().x - TFloor::S_GetLeftSize()
		|| m_tPos.x > TFloor::S_GetPosition().x + TFloor::S_GetRightSize()))
	{
		if (m_tVelocity.y < MAX_FALL_SPEED)
		{
			m_tVelocity.y += GRAVITY;

			if (m_tVelocity.y > MAX_FALL_SPEED)
			{
				m_tVelocity.y = MAX_FALL_SPEED;
			}
		}
	}

	m_tPos += m_tVelocity;

	if (m_tPos.x < TFloor::S_GetPosition().x + TFloor::S_GetRightSize()
		&& m_tPos.x > TFloor::S_GetPosition().x - TFloor::S_GetLeftSize()
		&& m_tPos.y > TFloor::S_GetPosition().y)
	{
		m_tPos.y = TFloor::S_GetPosition().y;
		m_tVelocity.y = 0.0f;
	}
}

void TDynamic::SetFallVelocity(const float fVelocity)
{
	m_tVelocity.y = fVelocity;
}
