
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "House.h"
#include "Entity.h"
#include "Building.h"
#include "Map.h"



using namespace Generics;

namespace
{
	const char * const SPRITE_NAME = "House.tga";

	const TGfxVec2 HOUSE_SIZE = TGfxVec2(96.0f, 96.0f);

	const int VILLAGERS_SPAWN_RATE = 1 * SECONDS;
	const float VILLAGERS_SIZE_Y = 32.0f;
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
		TMap::S_CreateVillager(m_tPos - TGfxVec2(0.0f, VILLAGERS_SIZE_Y));
		m_iLastSpawnTime = GfxTimeGetMilliseconds();
	}
}
