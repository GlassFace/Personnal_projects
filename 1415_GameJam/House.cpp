
#include "flib.h"
#include "flib_vec2.h"
#include "Entity.h"
#include "Building.h"
#include "House.h"



namespace
{
	const char * const SPRITE_NAME = "House.tga";

	const TGfxVec2 HOUSE_SIZE = TGfxVec2(96.0f, 96.0f);
}


TGfxTexture * THouse::s_pTexture = nullptr;

THouse::THouse() :
TBuilding()
{

}

THouse::THouse(const TGfxVec2 & tPos) :
TBuilding(tPos, HOUSE_SIZE)
{
	m_pSprite = GfxSpriteCreate(s_pTexture);
	GfxSpriteSetPosition(m_pSprite, tPos.x - (m_tSize.x / 2.0f), tPos.y - m_tSize.y);
}

THouse::~THouse()
{

}


void THouse::S_Initialize()
{
	s_pTexture = GfxTextureLoad(SPRITE_NAME);
}
