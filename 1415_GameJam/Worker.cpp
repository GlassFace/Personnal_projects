
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Entity.h"
#include "House.h"
#include "Building.h"
#include "Dynamic.h"
#include "Anim.h"
#include "Villager.h"
#include "Profession.h"
#include "Worker.h"
#include "Floor.h"
#include "Map.h"



using namespace Generics;

namespace
{
	const char * const IDLE_TILESET_NAME = "Worker\\Worker_Idle.tga";
	const char * const WALK_TILESET_NAME = "Worker\\Worker_Walk.tga";
	const char * const ACTION_TILESET_NAME = "Worker\\Worker_Action.tga";

	const int TIME_BETWEEN_CONSTRUCTIONS = 10 * SECONDS;
	const int CONSTRUCTION_TIME = 6 * SECONDS;
}


TGfxTexture * TWorker::s_pIdleTileSet = nullptr;
TGfxTexture * TWorker::s_pWalkTileSet = nullptr;
TGfxTexture * TWorker::s_pActionTileSet = nullptr;

TWorker::TWorker() :
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

TWorker::TWorker(EBuildingType eBuildingToConstruct) :
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
	if (m_eAction != EAction_Action && m_tDestinationToConstruct == TGfxVec2(0.0f, 0.0f))
	{
		if (GfxTimeGetMilliseconds() - (m_iStartConstructionTime + CONSTRUCTION_TIME) >= TIME_BETWEEN_CONSTRUCTIONS)
		{
			do
			{
				const TGfxVec2 tRandomPos = TGfxVec2(GfxMathGetRandomFloat(TFloor::GetPosition().x - TFloor::GetLeftSize(), TFloor::GetPosition().x + TFloor::GetRightSize()), TFloor::GetPosition().y);

				if (TMap::S_EnoughRoomToConstruct(tRandomPos, GetBuildingSize()))
				{
					m_tDestinationToConstruct = tRandomPos;
				}

			} while (m_tDestinationToConstruct == TGfxVec2(0.0f, 0.0f));

			m_eDirection = (m_tDestinationToConstruct - m_tPos).x >= 0.0f ? EDirection_Right : EDirection_Left;
		}
		
		else
		{
			RandomMove();
		}
	}

	else if (m_eAction == EAction_Walking && m_tPos != m_tDestinationToConstruct)
	{
		if ((m_tDestinationToConstruct - m_tPos).x <= ((m_fSpeed / GfxTimeFrameGetCurrentFPS())))
		{
			m_tPos = m_tDestinationToConstruct;

			m_eAction = EAction_Action;
			m_iStartConstructionTime = GfxTimeGetMilliseconds();
		}
	}

	else if (m_eAction == EAction_Action)
	{
		if (GfxTimeGetMilliseconds() - m_iStartConstructionTime >= CONSTRUCTION_TIME)
		{
			TMap::S_CreateBuilding(m_eConstructionToDo, m_tDestinationToConstruct);

			m_eAction = EAction_Idle;
		}
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

		break;

	case EBuildingType_Tower:

		break;
	}

	return fSize;
}
