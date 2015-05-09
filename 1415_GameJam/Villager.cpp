
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Entity.h"
#include "Background.h"
#include "Parallax.h"
#include "Map.h"
#include "Dynamic.h"
#include "Anim.h"
#include "Background.h"
#include "Villager.h"
#include "Profession.h"
#include "Worker.h"
#include "Building.h"
#include "HUD.h"
#include "Floor.h"
#include <string.h>



using namespace Generics;

namespace
{
	const char * const NAMES_FILE = "Villager\\Names.txt";

	const char * const IDLE_TILESET_NAME = "Villager\\Villager_Idle.tga";
	const char * const WALK_TILESET_NAME = "Villager\\Villager_Walk.tga";

	const int NAME_MAX_SIZE = 250;

	const TGfxVec2 VILLAGER_SIZE = TGfxVec2(32.0f, 64.0f);

	const float VILLAGER_WALK_SPEED = 64.0f;				// Pixels per seconds
	const int IDLE_DURATION_MIN = 1 * SECONDS;
	const int IDLE_DURATION_MAX = 5 * SECONDS;
	const int MOVE_DURATION_MIN = 2 * SECONDS;
	const int MOVE_DURATION_MAX = 6 * SECONDS;
	const float DIRECTION_CHANGE_CHANCES = 5.0f;			// Percentage

	const int CHANGE_DIRECTION_TIME_MIN = 2 * SECONDS;
	const int CHANGE_DIRECTION_TIME_MAX = 10 * SECONDS;

	const float AIR_DRAG = 0.8f;
}


TGfxTexture * TVillager::s_pIdleTileSet = nullptr;
TGfxTexture * TVillager::s_pWalkTileSet = nullptr;
TGfxFile * TVillager::s_pNamesFile = nullptr;

TVillager::TVillager() :
TDynamic(),
m_eState(EState_Alive),
m_tLocalName(0, 0),
m_pName(nullptr),
m_iAge(0),
m_eAction(EAction_Idle),
m_pProfession(nullptr),
m_pAssignedBuilding(nullptr),
m_iStartMoveTime(0),
m_iMoveDuration(0),
m_iIdleDuration(0),
m_pSpriteName(GfxTextSpriteCreate()),
m_pIdle(nullptr),
m_pWalk(nullptr)
{

}

TVillager::TVillager(const TGfxVec2 & tPos) :
TDynamic(tPos, VILLAGER_SIZE, VILLAGER_WALK_SPEED),
m_eState(EState_Alive),
m_tLocalName(0, 0),
m_pName(nullptr),
m_iAge(60),
m_eAction(EAction_Idle),
m_pProfession(nullptr),
m_pAssignedBuilding(nullptr),
m_iStartMoveTime(0),
m_iMoveDuration(0),
m_pSpriteName(GfxTextSpriteCreate()),
m_iIdleDuration(0),
m_pIdle(nullptr),
m_pWalk(nullptr)
{
	m_pIdle = new TAnim(s_pIdleTileSet, 1, 32, 64);
	m_pWalk = new TAnim(s_pWalkTileSet, 7, 32, 64);

	GetRandomName();
}

TVillager::~TVillager()
{
	if (m_pAssignedBuilding != nullptr)
	{
		m_pAssignedBuilding->UnassignVillager(this);
	}

	if (m_pName != nullptr)
	{
		delete[] m_pName;
		m_pName = nullptr;
	}
}


void TVillager::S_Initialize()
{
	s_pNamesFile = GfxFileOpenRead(NAMES_FILE);

	s_pIdleTileSet = GfxTextureLoad(IDLE_TILESET_NAME);
	s_pWalkTileSet = GfxTextureLoad(WALK_TILESET_NAME);
}

void TVillager::GetRandomName()
{
	char * pCursor = static_cast<char *>(GfxMemAlloc(GfxFileSize(s_pNamesFile) + 1));
	GfxFileRead(s_pNamesFile, pCursor, GfxFileSize(s_pNamesFile));
	GfxFileSeek(s_pNamesFile, 0);

	int iNamesCount = 0;
	int i = 0;

	for (i = 0; pCursor != nullptr && pCursor[i] != '\0'; i++)
	{
		if (pCursor[i] == '\n')
		{
			iNamesCount++;
		}
	}

	const int iRandomNameLine = GfxMathGetRandomInteger(0, iNamesCount);

	i = 0;

	for (int iLine = 0; iLine != iRandomNameLine; i++)
	{
		if (pCursor[i] == '\n')
		{
			iLine++;
		}
	}

	if (pCursor[i] == '\n')
	{
		i++;
	}

	char pName[NAME_MAX_SIZE] = { 0 };

	int iNameSize = 0;

	for (int iLetter = 0; pCursor[i] != '\r' && pCursor[i] != '\n' && i < GfxFileSize(s_pNamesFile); iLetter++, i++)
	{
		pName[iLetter] = pCursor[i];
		iNameSize++;
	}

	m_pName = new char[NAME_MAX_SIZE]{ 0 };
	strcpy(m_pName, pName);
	m_pName[iNameSize] = '\0';
}


void TVillager::SpecificUpdate()
{
	if (m_eAction != EAction_Grab && m_eAction != EAction_Falling)
	{
		if (m_pProfession == nullptr)
		{
			RandomMove();

			if (m_eAction == EAction_Walking)
			{
				m_pSprite = m_pWalk->Play(m_eDirection);
			}

			else
			{
				m_pSprite = m_pIdle->Play(m_eDirection);
			}
		}
		
		else
		{
			m_pProfession->ProfessionUpdate();
		}


		if (m_eAction == EAction_Walking)
		{
			m_tVelocity.x = (m_fSpeed / (GfxTimeFrameGetCurrentFPS() != 0.0f ? GfxTimeFrameGetCurrentFPS() : 60.0f)) * (m_eDirection == EDirection_Right ? 1.0f : -1.0f);
		}

		else if (m_eAction == EAction_Idle || m_eAction == EAction_Action)
		{
			m_tVelocity.x = 0.0f;
		}


		if (m_tPos.y > GfxGetDisplaySizeY())
		{
			Die();
		}

		else if (m_tPos.y < TFloor::GetPosition().y)
		{
			m_eAction = EAction_Falling;
		}
	}

	else if (m_eAction == EAction_Falling)
	{
		if (m_tPos.y >= TFloor::GetPosition().y)
		{
			m_eAction = EAction_Idle;
		}

		m_tVelocity.x -= AIR_DRAG / (GfxTimeFrameGetCurrentFPS() != 0.0f ? GfxTimeFrameGetCurrentFPS() : 60.0f);
	}
}

void TVillager::RandomMove()
{
	if (m_eAction == EAction_Walking && GfxTimeGetMilliseconds() - m_iStartMoveTime >= m_iMoveDuration)							// Stop walking
	{
		m_eAction = EAction_Idle;

		m_iIdleDuration = GfxMathGetRandomInteger(IDLE_DURATION_MIN, IDLE_DURATION_MAX);
	}

	else if (m_eAction == EAction_Idle && GfxTimeGetMilliseconds() - (m_iStartMoveTime + m_iMoveDuration) >= m_iIdleDuration)	// Start walking
	{
		m_eAction = EAction_Walking;

		m_iMoveDuration = GfxMathGetRandomInteger(MOVE_DURATION_MIN, MOVE_DURATION_MAX);
		m_iStartMoveTime = GfxTimeGetMilliseconds();
	}


	if (m_pProfession == nullptr && m_pAssignedBuilding != nullptr &&																						// Enclosure collision
		m_eAction == EAction_Walking)
	{
		const float fFenceLeftBorder = m_pAssignedBuilding->GetPos().x - (m_pAssignedBuilding->GetSize().x / 2.0f);
		const float fFenceRightBorder = m_pAssignedBuilding->GetPos().x + (m_pAssignedBuilding->GetSize().x / 2.0f);

		if (m_eDirection == EDirection_Left && m_tPos.x - (m_tSize.x / 2.0f) <= fFenceLeftBorder ||
			m_eDirection == EDirection_Right && m_tPos.x + (m_tSize.x / 2.0f) >= fFenceRightBorder)
		{
			m_eDirection = EDirection(!m_eDirection);
			m_tVelocity.x *= -1.0f;
		}
	}


	if (GfxTimeGetMilliseconds() % SECONDS >= 950 &&																			// Change direction
		GfxTimeGetMilliseconds() % SECONDS <= 1050 &&
		GfxMathGetRandomFloat(0.0f, 100.0f) <= DIRECTION_CHANGE_CHANCES)
	{
		m_eDirection = EDirection(!m_eDirection);
		m_tVelocity.x *= -1.0f;
	}
}

void TVillager::Die()
{
	m_eState = EState_Dead;

	THUD::S_OneMoreSuicide();
}

bool TVillager::IsAlive() const
{
	return m_eState == EState_Alive;
}

bool TVillager::IsOldEnough(const int iAgeNeeded) const
{
	return m_iAge >= iAgeNeeded;
}

bool TVillager::IsMouseOver(const TGfxVec2 & tMousePos) const
{
	const bool bMouseOnX = tMousePos.x >= m_tPos.x - (m_tSize.x / 2.0f) && tMousePos.x < m_tPos.x + (m_tSize.x / 2.0f);
	const bool bMouseOnY = tMousePos.y >= m_tPos.y - m_tSize.y && tMousePos.y <= m_tPos.y;

	if (bMouseOnX && bMouseOnY)
	{
		return true;
	}

	return false;
}

void TVillager::SetAction(EAction eAction)
{
	m_eAction = eAction;
}

void TVillager::AddForce(const TGfxVec2 & tForce)
{
	m_tVelocity += tForce;
}

void TVillager::SetProfession(TProfession * pProfession, TBuilding * pBuilding)
{
	if (m_pProfession != nullptr)
	{
		m_pAssignedBuilding->UnassignVillager(this);
	}

	m_pProfession = pProfession;
	m_pAssignedBuilding = pBuilding;
}

void TVillager::Unassign()
{
	delete m_pProfession;
	m_pProfession = nullptr;
	
	m_pAssignedBuilding = nullptr;
}

void TVillager::Render() const
{
	if (m_pSprite != nullptr)
	{
		GfxSpriteRender(m_pSprite);
	}
}
