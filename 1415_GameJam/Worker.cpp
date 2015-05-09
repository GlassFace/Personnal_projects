
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Background.h"
#include "Parallax.h"
#include "Map.h"
#include "Entity.h"
#include "Building.h"
#include "House.h"
#include "Workshop.h"
#include "Enclosure.h"
#include "Dynamic.h"
#include "Anim.h"
#include "Villager.h"
#include "Profession.h"
#include "Worker.h"
#include "Floor.h"



using namespace Generics;

namespace
{
	const char * const IDLE_TILESET_NAME = "Worker\\Worker_Idle.tga";
	const char * const WALK_TILESET_NAME = "Worker\\Worker_Walk.tga";
	const char * const ACTION_TILESET_NAME = "Worker\\Worker_Action.tga";

	const int TIME_BETWEEN_CONSTRUCTIONS = 10 * SECONDS;
	const int CONSTRUCTION_TIME = 6 * SECONDS;

	const float EXTENSIONS_CONSTRUCTION_SECURITY_DISTANCE = 20.0f;
}


TGfxTexture * TWorker::s_pIdleTileSet = nullptr;
TGfxTexture * TWorker::s_pWalkTileSet = nullptr;
TGfxTexture * TWorker::s_pActionTileSet = nullptr;

TWorker::TWorker() :
TProfession(),
m_pIdle(nullptr),
m_pWalk(nullptr),
m_pAction(nullptr),
m_tDestinationToConstruct(0.0f, 0.0f),
m_iStartConstructionTime(0),
m_eConstructionToDo()
{
	m_pIdle = new TAnim(s_pIdleTileSet, 1, 32, 64);
	m_pWalk = new TAnim(s_pWalkTileSet, 7, 32, 64);
	m_pAction = new TAnim(s_pActionTileSet, 7, 32, 64);
}

TWorker::TWorker(EBuildingType eBuildingToConstruct, TVillager * pLinkedVillager) :
TProfession(pLinkedVillager),
m_pIdle(nullptr),
m_pWalk(nullptr),
m_pAction(nullptr),
m_tDestinationToConstruct(0.0f, 0.0f),
m_iStartConstructionTime(0),
m_eConstructionToDo(eBuildingToConstruct)
{
	m_pIdle = new TAnim(s_pIdleTileSet, 1, 32, 64);
	m_pWalk = new TAnim(s_pWalkTileSet, 7, 32, 64);
	m_pAction = new TAnim(s_pActionTileSet, 7, 32, 64);
}

TWorker::~TWorker()
{

}


void TWorker::S_Initialize()
{
	s_pIdleTileSet = GfxTextureLoad(IDLE_TILESET_NAME);
	s_pWalkTileSet = GfxTextureLoad(WALK_TILESET_NAME);
	s_pActionTileSet = GfxTextureLoad(ACTION_TILESET_NAME);
}


void TWorker::ProfessionUpdate()
{
	if (m_pLinkedVillager->m_eAction != EAction_Action && m_tDestinationToConstruct == TGfxVec2(0.0f, 0.0f))
	{
		if (GfxTimeGetMilliseconds() - (m_iStartConstructionTime + CONSTRUCTION_TIME) >= TIME_BETWEEN_CONSTRUCTIONS)			// Find a spot to build after waiting
		{
			if (m_eConstructionToDo != EBuildingType_Barricade)
			{
				int iAttempts = 0;

				do
				{
					const TGfxVec2 tRandomPos = TGfxVec2(GfxMathGetRandomFloat(TFloor::S_GetPosition().x - TFloor::S_GetLeftSize(), TFloor::S_GetPosition().x + TFloor::S_GetRightSize()), TFloor::S_GetPosition().y);

					if (TMap::S_EnoughRoomToConstruct(tRandomPos, GetBuildingSize()))
					{
						m_tDestinationToConstruct = tRandomPos;
					}

					iAttempts++;

				} while (m_tDestinationToConstruct == TGfxVec2(0.0f, 0.0f) && iAttempts < 100);
			}
			
			else
			{
				const EDirection eSide = GfxMathGetRandomInteger(0, 1) == 1 ? EDirection_Right : EDirection_Left;

				switch (eSide)
				{
				case EDirection_Right:

					m_tDestinationToConstruct = TFloor::S_GetPosition() + TGfxVec2(TFloor::S_GetRightSize() - EXTENSIONS_CONSTRUCTION_SECURITY_DISTANCE, 0.0f);

					break;

				case EDirection_Left:

					m_tDestinationToConstruct = TFloor::S_GetPosition() - TGfxVec2(TFloor::S_GetLeftSize() - EXTENSIONS_CONSTRUCTION_SECURITY_DISTANCE, 0.0f);

					break;
				}
			}


			if (m_tDestinationToConstruct != TGfxVec2(0.0f, 0.0f))
			{
				m_pLinkedVillager->m_eAction = EAction_Walking;
				m_pLinkedVillager->m_eDirection = (m_tDestinationToConstruct - m_pLinkedVillager->m_tPos).x >= 0.0f ? EDirection_Right : EDirection_Left;
			}
		}

		
		else																															// Wait
		{
			m_pLinkedVillager->RandomMove();
		}
	}

	else if (m_pLinkedVillager->m_eAction == EAction_Walking && m_pLinkedVillager->m_tPos != m_tDestinationToConstruct)					// Go to spot
	{
		if (m_eConstructionToDo != EBuildingType_Barricade &&
			!TMap::S_EnoughRoomToConstruct(m_tDestinationToConstruct, GetBuildingSize()))
		{
			m_pLinkedVillager->m_eAction = EAction_Idle;
			m_tDestinationToConstruct = TGfxVec2(0.0f, 0.0f);
		}

		else if ((m_tDestinationToConstruct - m_pLinkedVillager->m_tPos).x <= (m_pLinkedVillager->m_fSpeed / GfxTimeFrameGetCurrentFPS()) &&
				 (m_tDestinationToConstruct - m_pLinkedVillager->m_tPos).x >= -(m_pLinkedVillager->m_fSpeed / GfxTimeFrameGetCurrentFPS()))
		{
			m_pLinkedVillager->m_tPos = m_tDestinationToConstruct;

			m_pLinkedVillager->m_eAction = EAction_Action;
			m_pLinkedVillager->m_tVelocity.x = 0.0f;

			m_iStartConstructionTime = GfxTimeGetMilliseconds();
		}
	}

	else if (m_pLinkedVillager->m_eAction == EAction_Action)																			// Build
	{
		if (m_eConstructionToDo != EBuildingType_Barricade &&
			!TMap::S_EnoughRoomToConstruct(m_tDestinationToConstruct, GetBuildingSize()))
		{
			m_pLinkedVillager->m_eAction = EAction_Idle;
			m_tDestinationToConstruct = TGfxVec2(0.0f, 0.0f);
		}

		if (GfxTimeGetMilliseconds() - m_iStartConstructionTime >= CONSTRUCTION_TIME)
		{
			TMap::S_CreateBuilding(m_eConstructionToDo, m_tDestinationToConstruct);

			m_tDestinationToConstruct = TGfxVec2(0.0f, 0.0f);
			m_pLinkedVillager->m_eAction = EAction_Idle;
		}
	}


	if (m_pLinkedVillager->m_eAction == EAction_Walking)
	{
		m_pLinkedVillager->m_pSprite = m_pWalk->Play(m_pLinkedVillager->m_eDirection);
	}

	else if (m_pLinkedVillager->m_eAction == EAction_Action)
	{
		m_pLinkedVillager->m_pSprite = m_pAction->Play(m_pLinkedVillager->m_eDirection);
	}

	else
	{
		m_pLinkedVillager->m_pSprite = m_pIdle->Play(m_pLinkedVillager->m_eDirection);
	}
}

void TWorker::SetBuildingsToCreate(EBuildingType eBuildingToConstruct)
{
	m_eConstructionToDo = eBuildingToConstruct;

	GfxDbgPrintf("%s\n", m_eConstructionToDo == EBuildingType_Barricade ? "Barricade" : m_eConstructionToDo == EBuildingType_House ? "House" : "Workshop");

	if (m_tDestinationToConstruct != TGfxVec2(0.0f, 0.0f))
	{
		GfxDbgPrintf("Yo\n");

		m_iStartConstructionTime = GfxTimeGetMilliseconds();

		m_pLinkedVillager->m_eAction = EAction_Idle;
		m_tDestinationToConstruct = TGfxVec2(0.0f, 0.0f);
	}
}

float TWorker::GetBuildingSize()
{
	float fSize = 0.0f;

	switch (m_eConstructionToDo)
	{
	case EBuildingType_House:

		fSize = THouse::S_GetSizeX();

		break;

	case EBuildingType_Workshop:

		fSize = TWorkshop::S_GetSizeX();

		break;

	case EBuildingType_Barricade:

		fSize = 0.0f;

		break;

	case EBuildingType_Enclosure:

		fSize = TEnclosure::S_GetSizeX();

		break;
	}

	return fSize;
}
