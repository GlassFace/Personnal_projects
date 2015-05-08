
#include "flib.h"
#include "flib_vec2.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Villager.h"
#include "HUD.h"
#include <string.h>



namespace
{
	const char * const SPRITE_NAME = "Villager.tga";
	const char * const NAMES_FILE = "Names.txt";

	const int NAME_MAX_SIZE = 250;

	const TGfxVec2 VILLAGER_SIZE = TGfxVec2(32.0f, 64.0f);
	const float VILLAGER_WALK_SPEED = 32.0f;				// Pixels per seconds
}


TGfxTexture * TVillager::s_pTexture = nullptr;
TGfxFile * TVillager::s_pNamesFile = nullptr;

TVillager::TVillager() :
TDynamic(),
m_eState(EState_Alive),
m_pName(nullptr)
{

}

TVillager::TVillager(const TGfxVec2 & tPos) :
TDynamic(tPos, VILLAGER_SIZE, VILLAGER_WALK_SPEED),
m_eState(EState_Alive),
m_pName(nullptr)
{
	m_pSprite = GfxSpriteCreate(s_pTexture);
	GfxSpriteSetPosition(m_pSprite, tPos.x - (m_tSize.x / 2.0f), tPos.y - m_tSize.y);

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
	s_pTexture = GfxTextureLoad(SPRITE_NAME);

	s_pNamesFile = GfxFileOpenRead(NAMES_FILE);
}

void TVillager::GetRandomName()
{
	char * pCursor = static_cast<char *>(GfxMemAlloc(GfxFileSize(s_pNamesFile) + 1));
	GfxFileRead(s_pNamesFile, pCursor, GfxFileSize(s_pNamesFile));

	int iNamesCount = 0;
	int i = 0;

	for (i = 0; pCursor != nullptr && pCursor[i] != '\0'; i++)
	{
		if (pCursor[0] == '\r')
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

	char pName[NAME_MAX_SIZE] = { 0 };

	for (int iLetter = 0/*, i = i*/; pCursor[i] != '\r' && pCursor[i] != '\n'; iLetter++, i++)
	{
		pName[iLetter] = pCursor[i];
	}

	m_pName = new char[NAME_MAX_SIZE]{ 0 };
	strcpy(m_pName, pName);
}


void TVillager::SpecificUpdate()
{

}

void TVillager::Die()
{
	m_eState = EState_Dead;

	THUD::S_OneMoreSuicide();
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
