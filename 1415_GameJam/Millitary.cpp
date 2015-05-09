
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Background.h"
#include "Parallax.h"
#include "Map.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Anim.h"
#include "Bird.h"
#include "Villager.h"
#include "Profession.h"
#include "Millitary.h"



using namespace Generics;

namespace
{
	const char * const IDLE_TILESET_NAME = "Millitary\\Millitary_Idle.tga";
	const char * const WALK_TILESET_NAME = "Millitary\\Millitary_Walk.tga";
	const char * const ACTION_TILESET_NAME = "Millitary\\Millitary_Action.tga";

	const int TIME_BETWEEN_SHOTS = 3 * (SECONDS / 2);
	const int ATTACK_ANIMATION_DURATION = int((SECONDS / 7.0f) * 8.0f);


	const float SIGHT_RADIUS = 400.0f;
}


TGfxTexture * TMillitary::s_pIdleTileSet = nullptr;
TGfxTexture * TMillitary::s_pWalkTileSet = nullptr;
TGfxTexture * TMillitary::s_pActionTileSet = nullptr;

TMillitary::TMillitary() :
TProfession(),
m_iLastAttackTime(0)
{
	m_pIdle = new TAnim(s_pIdleTileSet, 1, 32, 64);
	m_pWalk = new TAnim(s_pWalkTileSet, 7, 32, 64);
	m_pAction = new TAnim(s_pActionTileSet, 7, 32, 64);
}

TMillitary::TMillitary(TVillager * pLinkedVillager) :
TProfession(pLinkedVillager),
m_iLastAttackTime(0)
{
	m_pIdle = new TAnim(s_pIdleTileSet, 1, 32, 64);
	m_pWalk = new TAnim(s_pWalkTileSet, 7, 32, 64);
	m_pAction = new TAnim(s_pActionTileSet, 7, 32, 64);
}

TMillitary::~TMillitary()
{

}


void TMillitary::S_Initialize()
{
	s_pIdleTileSet = GfxTextureLoad(IDLE_TILESET_NAME);
	s_pWalkTileSet = GfxTextureLoad(WALK_TILESET_NAME);
	s_pActionTileSet = GfxTextureLoad(ACTION_TILESET_NAME);
}


void TMillitary::ProfessionUpdate()
{
	TBird ** pBirds = TMap::S_GetBirds();

	TBird * pClosestBird = nullptr;

	for (int i = 0; i < TMap::S_GetBirdsCount(); i++)
	{
		if (pBirds[i] != nullptr &&
			(pBirds[i]->GetPos() - m_pLinkedVillager->m_tPos).SquaredLength() <= (SIGHT_RADIUS * SIGHT_RADIUS))
		{
			if (pClosestBird == nullptr ||
				(pBirds[i]->GetPos() - m_pLinkedVillager->m_tPos).SquaredLength() < (pClosestBird->GetPos() - m_pLinkedVillager->m_tPos).SquaredLength())
			{
				pClosestBird = pBirds[i];
			}
		}
	}

	if (pClosestBird != nullptr && GfxTimeGetMilliseconds() - m_iLastAttackTime >= TIME_BETWEEN_SHOTS)
	{
		pClosestBird->TakeHit();

		m_iLastAttackTime = GfxTimeGetMilliseconds();

		m_pLinkedVillager->m_eAction = EAction_Action;
		m_pLinkedVillager->m_tVelocity.x = 0.0f;
	}

	else
	{
		m_pLinkedVillager->RandomMove();
	}


	if (m_pLinkedVillager->m_eAction == EAction_Walking)
	{
		m_pLinkedVillager->m_pSprite = m_pWalk->Play(m_pLinkedVillager->m_eDirection);
	}

	else if (m_pLinkedVillager->m_eAction == EAction_Action)
	{
		m_pLinkedVillager->m_pSprite = m_pAction->Play(m_pLinkedVillager->m_eDirection);

		if (GfxTimeGetMilliseconds() - m_iLastAttackTime >= ATTACK_ANIMATION_DURATION)
		{
			m_pLinkedVillager->m_eAction = EAction_Idle;
		}
	}

	else
	{
		m_pLinkedVillager->m_pSprite = m_pIdle->Play(m_pLinkedVillager->m_eDirection);
	}
}
