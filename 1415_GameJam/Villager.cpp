
#include "flib.h"
#include "flib_vec2.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Villager.h"



namespace
{
	const char * const SPRITE_NAME = "Villager.tga";

	const TGfxVec2 VILLAGER_SIZE = TGfxVec2(32.0f, 64.0f);
	const float VILLAGER_WALK_SPEED = 32.0f;				// Pixels per seconds
}


TGfxTexture * TVillager::s_pTexture = nullptr;

TVillager::TVillager() :
TDynamic()
{

}

TVillager::TVillager(const TGfxVec2 & tPos) :
TDynamic(tPos, VILLAGER_SIZE, VILLAGER_WALK_SPEED)
{
	m_pSprite = GfxSpriteCreate(s_pTexture);
	GfxSpriteSetPosition(m_pSprite, tPos.x - (m_tSize.x / 2.0f), tPos.y - m_tSize.y);
}

TVillager::~TVillager()
{

}


void TVillager::S_Initialize()
{
	s_pTexture = GfxTextureLoad(SPRITE_NAME);
}
