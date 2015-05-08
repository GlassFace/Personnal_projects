
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Anim.h"
#include "Villager.h"
#include "Profession.h"
#include "HUD.h"
#include "Floor.h"
#include <string.h>



using namespace Generics;

namespace
{
	const char * const NAMES_FILE = "Names.txt";

	const char * const IDLE_TILESET_NAME = "Villager_Idle.tga";
	const char * const WALK_TILESET_NAME = "Villager_Walk.tga";

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

	const float GRAVITY = 0.2f;
	const float MAX_FALL_SPEED = 20.0f;
}


TGfxTexture * TVillager::s_pIdleTileSet = nullptr;
TGfxTexture * TVillager::s_pWalkTileSet = nullptr;
TGfxFile * TVillager::s_pNamesFile = nullptr;

TVillager::TVillager() :
TDynamic(),
m_eState(EState_Alive),
m_pName(nullptr),
m_iAge(0),
m_eAction(EAction_Idle),
m_pProfession(nullptr),
m_iStartMoveTime(0),
m_iMoveDuration(0),
m_iIdleDuration(0),
m_pIdle(nullptr),
m_pWalk(nullptr)
{

}

TVillager::TVillager(const TGfxVec2 & tPos) :
TDynamic(tPos, VILLAGER_SIZE, VILLAGER_WALK_SPEED),
m_eState(EState_Alive),
m_pName(nullptr),
m_iAge(0),
m_eAction(EAction_Idle),
m_pProfession(nullptr),
m_iStartMoveTime(0),
m_iMoveDuration(0),
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
		if (pCursor[i] == '\r')
		{
			iNamesCount++;
		}
	}

	const int iRandomNameLine = GfxMathGetRandomInteger(0, iNamesCount);

	i = 0;

	for (int iLine = 0; iLine != iRandomNameLine; i++)
	{
		if (pCursor[i] == '\r')
		{
			iLine++;
		}
	}

	if (pCursor[i] == '\n')
	{
		i++;
	}

	char pName[NAME_MAX_SIZE] = { 0 };

	for (int iLetter = 0/*, i = i*/; pCursor[i] != '\r' && pCursor[i] != '\n' && pCursor[i] != '\0'; iLetter++, i++)
	{
		pName[iLetter] = pCursor[i];
	}

	m_pName = new char[NAME_MAX_SIZE]{ 0 };
	strcpy(m_pName, pName);
}


void TVillager::SpecificUpdate()
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
}

void TVillager::RandomMove()
{
	// Move on Y
	if (m_tPos.y < TFloor::GetPosition().y
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
	}
	else
	{
		if (m_eAction == EAction_Walking && GfxTimeGetMilliseconds() - m_iStartMoveTime >= m_iMoveDuration)
		{
			m_eAction = EAction_Idle;
			m_tVelocity.x = 0.0f;

			m_iIdleDuration = GfxMathGetRandomInteger(IDLE_DURATION_MIN, IDLE_DURATION_MAX);
		}

		else if (m_eAction == EAction_Idle && GfxTimeGetMilliseconds() - (m_iStartMoveTime + m_iMoveDuration) >= m_iIdleDuration)
		{
			m_eAction = EAction_Walking;
			m_tVelocity.x = (m_fSpeed / (GfxTimeFrameGetCurrentFPS() != 0.0f ? GfxTimeFrameGetCurrentFPS() : 60.0f)) * (m_eDirection == EDirection_Right ? 1.0f : -1.0f);

			m_iMoveDuration = GfxMathGetRandomInteger(MOVE_DURATION_MIN, MOVE_DURATION_MAX);
			m_iStartMoveTime = GfxTimeGetMilliseconds();
		}

		if (GfxTimeGetMilliseconds() % SECONDS >= 950 &&
			GfxTimeGetMilliseconds() % SECONDS <= 1050 &&
			GfxMathGetRandomFloat(0.0f, 100.0f) <= DIRECTION_CHANGE_CHANCES)
		{
			m_eDirection = EDirection(!m_eDirection);
			m_tVelocity.x *= -1.0f;
		}
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

void TVillager::SetProfession(TProfession * pProfession)
{
	m_pProfession = pProfession;
}

void TVillager::Render() const
{
	if (m_pSprite != nullptr)
	{
		GfxSpriteRender(m_pSprite);
	}
}
