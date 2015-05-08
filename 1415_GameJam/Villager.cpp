
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Anim.h"
#include "Villager.h"
#include "HUD.h"
#include "Floor.h"
#include <string.h>



using namespace Generics;

namespace
{
	const char * const NAMES_FILE = "Names.txt";

	const int NAME_MAX_SIZE = 250;

	const TGfxVec2 VILLAGER_SIZE = TGfxVec2(32.0f, 64.0f);
	const float VILLAGER_WALK_SPEED = 64.0f;					// Pixels per seconds

	const int CHANGE_DIRECTION_TIME_MIN = 2 * SECONDS;
	const int CHANGE_DIRECTION_TIME_MAX = 10 * SECONDS;
}


TGfxTexture * TVillager::s_pTexture = nullptr;
TGfxFile * TVillager::s_pNamesFile = nullptr;

TVillager::TVillager() :
TDynamic(),
m_eState(EState_Alive),
m_pName(nullptr),
m_pWalk(nullptr)
{

}

TVillager::TVillager(const TGfxVec2 & tPos) :
TDynamic(tPos, VILLAGER_SIZE, VILLAGER_WALK_SPEED),
m_eState(EState_Alive),
m_pName(nullptr),
m_pWalk(nullptr)
{
	m_pWalk = new TAnim("Villager_Walk.tga", 7, 32, 64);

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
	RandomMove();

	m_pSprite = m_pWalk->Play(m_eDirection);
}

void TVillager::RandomMove()
{
	int iTimePassed = GfxTimeGetMilliseconds() - m_iLastMoveChoice;
	if (iTimePassed >= m_iNextMoveChoice)
	{
		m_iLastMoveChoice = GfxTimeGetMilliseconds();
		m_iNextMoveChoice = GfxMathGetRandomInteger(CHANGE_DIRECTION_TIME_MIN, CHANGE_DIRECTION_TIME_MAX);
		int iSide = GfxMathGetRandomInteger(0, 1);
		if (iSide == 0)
		{
			m_tVelocity.x = m_fSpeed;
			m_eDirection = EDirection_Right;
		}
		else
		{
			m_tVelocity.x = -m_fSpeed;
			m_eDirection = EDirection_Left;
		}
	}
}

void TVillager::Die()
{
	m_eState = EState_Dead;

	THUD::S_OneMoreSuicide(this);
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

void TVillager::Render() const
{
	if (m_pSprite != nullptr)
	{
		GfxSpriteRender(m_pSprite);
	}
}
