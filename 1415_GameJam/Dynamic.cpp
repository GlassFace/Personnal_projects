
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Floor.h"



using namespace Generics;

namespace
{
	const float GRAVITY = 0.2f;
	const float MAX_FALL_SPEED = 20.0f;
}


TDynamic::TDynamic() :
TEntity(),
m_eDirection(EDirection_Right),
m_fSpeed(0.0f),
m_tVelocity(0.0f, 0.0f),
m_iNextMoveChoice(0),
m_iLastMoveChoice(0),
m_iLastMove(0)
{
	
}

TDynamic::TDynamic(const TGfxVec2 & tPos, const TGfxVec2 & tSize, const float fSpeed) :
TEntity(tPos, tSize),
m_eDirection(EDirection_Right),
m_fSpeed(fSpeed),
m_tVelocity(0.0f, 0.0f),
m_iNextMoveChoice(0),
m_iLastMoveChoice(0),
m_iLastMove(0)
{

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

	if (m_tPos.y + 10.f < TFloor::GetPosition().y
		|| (m_tPos.x < TFloor::GetPosition().x - TFloor::GetLeftSize()
		|| m_tPos.x > TFloor::GetPosition().x + TFloor::GetRightSize()))
	{
		if (m_tVelocity.y < MAX_FALL_SPEED)
		{
			m_tVelocity.y += GRAVITY;

			if (m_tVelocity.y > MAX_FALL_SPEED)
			{
				m_tVelocity.y = MAX_FALL_SPEED;
			}
		}
		
		m_tPos.y += m_tVelocity.y;

		if (m_tPos.y > 1080.0f)
		{
			Die();
		}

		GfxSpriteSetPosition(m_pSprite, m_tPos.x, m_tPos.y);
		m_iLastMove = GfxTimeGetMilliseconds();
	}

	else
	{
		m_tVelocity.y = 0.0f;
		m_tPos.y = TFloor::GetPosition().y;

		float fTimePassed = float((GfxTimeGetMilliseconds() - m_iLastMove)) / float(SECONDS);

		m_tPos.x += m_tVelocity.x * fTimePassed;
		GfxSpriteSetPosition(m_pSprite, m_tPos.x, m_tPos.y);
		m_iLastMove = GfxTimeGetMilliseconds();
	}

}

void TDynamic::SetFallVelocity(const float fVelocity)
{
	m_tVelocity.y = fVelocity;
}
