
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
#include "Priest.h"
#include "Building.h"
#include "Enclosure.h"




using namespace Generics;

namespace
{
	const char * const IDLE_TILESET_NAME = "Priest\\Priest_Idle.tga";
	const char * const WALK_TILESET_NAME = "Priest\\Priest_Walk.tga";
	const char * const ACTION_TILESET_NAME = "Priest\\Priest_Action.tga";

	const int TIME_BETWEEN_SHOTS = 3 * (SECONDS / 2);
	const int ATTACK_ANIMATION_DURATION = int((SECONDS / 7.0f) * 8.0f);


	const float SIGHT_RADIUS = 400.0f;
}


TGfxTexture * TPriest::s_pIdleTileSet = nullptr;
TGfxTexture * TPriest::s_pWalkTileSet = nullptr;
TGfxTexture * TPriest::s_pActionTileSet = nullptr;

TPriest::TPriest() :
TProfession()
{
	m_pIdle = new TAnim(s_pIdleTileSet, 1, 32, 64);
	m_pWalk = new TAnim(s_pWalkTileSet, 7, 32, 64);
	m_pRun = new TAnim(s_pWalkTileSet, 15, 32, 64);
}

TPriest::TPriest(TVillager * pLinkedVillager) :
TProfession(pLinkedVillager)
{
	m_pIdle = new TAnim(s_pIdleTileSet, 1, 32, 64);
	m_pWalk = new TAnim(s_pWalkTileSet, 7, 32, 64);
	m_pRun = new TAnim(s_pWalkTileSet, 15, 32, 64);
}

TPriest::~TPriest()
{

}


void TPriest::S_Initialize()
{
	s_pIdleTileSet = GfxTextureLoad(IDLE_TILESET_NAME);
	s_pWalkTileSet = GfxTextureLoad(WALK_TILESET_NAME);
}


void TPriest::ProfessionUpdate()
{
	if (m_pEnclosureTarget == nullptr)
	{
		TBuilding ** pBuildings = TMap::S_GetBuildings();

		TEnclosure * pNearestEnclosure = nullptr;

		for (int i = 0; i < TMap::S_GetBuildingsCount(); i++)
		{
			if (pBuildings[i]->GetBuildingType() == EBuildingType_Enclosure &&
				pNearestEnclosure != nullptr &&
				(pBuildings[i]->GetPos().x - m_pLinkedVillager->m_tPos.x) < (pNearestEnclosure->GetPos().x - m_pLinkedVillager->m_tPos.x)
				||
				pBuildings[i]->GetBuildingType() == EBuildingType_Enclosure)
			{
				pNearestEnclosure = static_cast<TEnclosure*>(pBuildings[i]);
			}
		}

		m_pEnclosureTarget = pNearestEnclosure;

		if (m_pEnclosureTarget != nullptr)
		{
			TVillager ** pVillagers = TMap::S_GetVillagers();

			TVillager * pNearestVillager = nullptr;

			for (int i = 0; i < TMap::S_GetVillagerCount(); i++)
			{
				if (pVillagers[i] != m_pLinkedVillager &&
					pVillagers[i]->m_pAssignedBuilding == nullptr &&
					pVillagers[i]->m_eAction != EAction_Grab &&
					pNearestVillager != nullptr &&
					(pVillagers[i]->m_tPos.x - m_pLinkedVillager->m_tPos.x) < (pNearestVillager->m_tPos.x - m_pLinkedVillager->m_tPos.x)
					||
					pVillagers[i] != m_pLinkedVillager &&
					pVillagers[i]->m_pAssignedBuilding == nullptr &&
					pVillagers[i]->m_eAction != EAction_Grab)
				{
					pNearestVillager = pVillagers[i];
				}
			}

			m_pRescuedVillager = pNearestVillager;

			if (m_pRescuedVillager != nullptr)
			{
				m_pLinkedVillager->m_eAction = EAction_Running;
			}
		}
	}

	else
	{
		switch (m_pLinkedVillager->m_eAction)
		{
		case EAction_Running:
		{
				if (m_pRescuedVillager->m_tPos.x - m_pLinkedVillager->m_tPos.x >= -0.1f &&
					m_pRescuedVillager->m_tPos.x - m_pLinkedVillager->m_tPos.x <= 0.1f)
				{
					m_pLinkedVillager->m_eAction = EAction_Action;
					m_pRescuedVillager->m_eAction = EAction_Grab;
					m_pRescuedVillager->SetPosition(m_pLinkedVillager->m_tPos - TGfxVec2(0.0f, m_pLinkedVillager->m_tSize.y));
				}

				else
				{
					const float fDirectionSign = m_pRescuedVillager->m_tPos.x >= m_pLinkedVillager->m_tPos.x ? 1.0f : -1.0f;

					m_pLinkedVillager->m_tVelocity.x = ((m_pLinkedVillager->m_fSpeed * 2.0f) / GfxTimeFrameGetCurrentFPS()) * fDirectionSign;
					m_pLinkedVillager->m_eDirection = fDirectionSign == 1.0f ? EDirection_Right : EDirection_Left;
				}

				break;
		}
		case EAction_Action:
		{
			if (m_pEnclosureTarget->GetPos().x - m_pLinkedVillager->m_tPos.x >= -0.1f &&
				m_pEnclosureTarget->GetPos().x - m_pLinkedVillager->m_tPos.x <= 0.1f)
			{
				m_pRescuedVillager->m_eAction = EAction_Idle;
				m_pEnclosureTarget->AssignVillager(m_pRescuedVillager);
				m_pEnclosureTarget = nullptr;
				m_pRescuedVillager = nullptr;

				m_pLinkedVillager->m_eAction = EAction_Idle;
			}

			else
			{
				const float fDirectionSign = m_pEnclosureTarget->GetPos().x >= m_pLinkedVillager->m_tPos.x ? 1.0f : -1.0f;

				m_pLinkedVillager->m_tVelocity.x = (m_pLinkedVillager->m_fSpeed / GfxTimeFrameGetCurrentFPS()) * fDirectionSign;
				m_pLinkedVillager->m_eDirection = fDirectionSign == 1.0f ? EDirection_Right : EDirection_Left;
			}

			break;
		}

		/*case EAction_Walking:
		case EAction_Idle:



			break;*/
		}




		/*if (m_pLinkedVillager->m_eAction == EAction_Action)
		{
			if ((m_pRescuedVillager->m_tPos.x - m_pLinkedVillager->m_tPos.x) > (m_pLinkedVillager->m_tSize.x / 2.0f))
			{
				const float fDirectionSign = m_pRescuedVillager->m_tPos.x >= m_pLinkedVillager->m_tPos.x ? 1.0f : -1.0f;
				m_pLinkedVillager->m_eDirection = fDirectionSign == 1.0f ? EDirection_Right : EDirection_Left;

				m_pLinkedVillager->m_tVelocity.x = ((m_pLinkedVillager->m_fSpeed * 2.0f) / GfxTimeFrameGetCurrentFPS()) * fDirectionSign;
			}

			else
			{
				m_pLinkedVillager->m_eAction = EAction_Walking;
			}
		}

		else if (m_pLinkedVillager->m_eAction == EAction_Walking)
		{
			if ((m_pEnclosureTarget->GetPos().x - m_pLinkedVillager->m_tPos.x) > (m_pLinkedVillager->m_tSize.x / 2.0f))
			{
				const float fDirectionSign = m_pEnclosureTarget->GetPos().x >= m_pLinkedVillager->m_tPos.x ? 1.0f : -1.0f;
				m_pLinkedVillager->m_eDirection = fDirectionSign == 1.0f ? EDirection_Right : EDirection_Left;

				m_pLinkedVillager->m_tVelocity.x = (m_pLinkedVillager->m_fSpeed / GfxTimeFrameGetCurrentFPS()) * fDirectionSign;
			}
		}*/
	}


	/*if (m_pLinkedVillager->m_eAction == EAction_Walking &&
		m_pRescuedVillager != nullptr)
	{
		m_pRescuedVillager->m_tVelocity.x = m_pLinkedVillager->m_tVelocity.x;
		m_pRescuedVillager->m_eDirection = m_pLinkedVillager->m_eDirection;
		m_pRescuedVillager->m_eAction = EAction_Walking;
	}*/


	if (m_pEnclosureTarget == nullptr)
	{
		m_pRescuedVillager = nullptr;
		m_pLinkedVillager->RandomMove();
	}


	if (m_pLinkedVillager->m_eAction == EAction_Idle)
	{
		m_pLinkedVillager->m_pSprite = m_pIdle->Play(m_pLinkedVillager->m_eDirection);
	}

	else if (m_pLinkedVillager->m_eAction == EAction_Walking)
	{
		m_pLinkedVillager->m_pSprite = m_pWalk->Play(m_pLinkedVillager->m_eDirection);
	}

	else if (m_pLinkedVillager->m_eAction == EAction_Running)
	{
		m_pLinkedVillager->m_pSprite = m_pRun->Play(m_pLinkedVillager->m_eDirection);
	}

	else
	{
		m_pLinkedVillager->m_pSprite = m_pAction->Play(m_pLinkedVillager->m_eDirection);
	}
}
