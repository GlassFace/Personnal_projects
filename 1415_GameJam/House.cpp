
#include "flib.h"
#include "flib_vec2.h"
#include "House.h"
#include "Entity.h"
#include "Building.h"
#include "Map.h"



namespace
{
	const char * const SPRITE_NAME = "House.tga";

	const TGfxVec2 HOUSE_SIZE = TGfxVec2(96.0f, 96.0f);

	const int VILLAGERS_SPAWN_RATE = 60 * 1000;		// Milliseconds
}


TGfxTexture * THouse::s_pTexture = nullptr;

THouse::THouse() :
TBuilding(),
m_iLastSpawnTime(0)
{

}

THouse::THouse(const TGfxVec2 & tPos) :
TBuilding(tPos, HOUSE_SIZE),
m_iLastSpawnTime(0)
{
	m_pSprite = GfxSpriteCreate(s_pTexture);
	GfxSpriteSetPivot(m_pSprite, (m_tSize.x / 2.0f), m_tSize.y);
	GfxSpriteSetPosition(m_pSprite, m_tPos.x, m_tPos.y);
}

THouse::~THouse()
{

}


void THouse::S_Initialize()
{
	s_pTexture = GfxTextureLoad(SPRITE_NAME);
}


void THouse::SpecificUpdate()
{
	if (GfxTimeGetMilliseconds() - m_iLastSpawnTime >= VILLAGERS_SPAWN_RATE)
	{
		TMap::S_CreateVillager(m_tPos);
		m_iLastSpawnTime = GfxTimeGetMilliseconds();
	}
}
