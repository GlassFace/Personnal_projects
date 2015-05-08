
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Map.h"
#include "Entity.h"
#include "Building.h"
#include "House.h"
#include "Map.h"



using namespace Generics;

namespace
{

	const char * const SPRITE_NAME = "House.tga";

	const TGfxVec2 HOUSE_SIZE = TGfxVec2(112.0f, 112.0f);

	const int VILLAGERS_SPAWN_RATE = 30 * SECONDS;
	const float VILLAGERS_SIZE_Y = 32.0f;
}


TGfxTexture * THouse::s_pTexture = nullptr;

THouse::THouse() :
TBuilding(),
m_iLastSpawnTime(0)
{
	m_eBuildingType = EBuildingType_House;
}

THouse::THouse(const TGfxVec2 & tPos) :
TBuilding(tPos, HOUSE_SIZE),
m_iLastSpawnTime(0)
{
	m_eBuildingType = EBuildingType_House;

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
		TMap::S_CreateVillager(m_tPos - TGfxVec2(0.0f, VILLAGERS_SIZE_Y / 2.0f));
		m_iLastSpawnTime = GfxTimeGetMilliseconds();
	}
}

float THouse::S_GetSizeX()
{
	return HOUSE_SIZE.x;
}
