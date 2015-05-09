
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Meteorite.h"
#include "Floor.h"
#include "Anim.h"



using namespace Generics;

namespace
{
	const char * const TILESET_NAME = "Meteorite\\Meteorite.tga";
	const char * const WARNING_TILESET_NAME = "Meteorite\\Warning.tga";

	const TGfxVec2 METEORITE_SIZE = TGfxVec2(150.0f, 150.0f);
	const TGfxVec2 WARNING_SIZE = TGfxVec2();

	const float METEORITE_SPEED = 300.0f;

	const int WARNING_DURATION = 5 * SECONDS;
}


TGfxTexture * TMeteorite::s_pMeteoriteTileset = nullptr;
TGfxTexture * TMeteorite::s_pWarningTileSet = nullptr;

TMeteorite::TMeteorite() :
TDynamic(),
m_tDestination(0.0f, 0.0f),
m_iStartWarningTime(0),
m_pFall(nullptr),
m_pWarning(nullptr),
m_pWarningSprite(nullptr)
{

}

TMeteorite::TMeteorite(const TGfxVec2 & tPos) :
TDynamic(tPos, METEORITE_SIZE, METEORITE_SPEED),
m_tDestination(0.0f, 0.0f),
m_iStartWarningTime(0),
m_pFall(nullptr),
m_pWarning(nullptr),
m_pWarningSprite(nullptr)
{
	m_tDestination = TGfxVec2(tPos.x, TFloor::S_GetPosition().y);
	m_iStartWarningTime = GfxTimeGetMilliseconds();

	m_pFall = new TAnim(s_pMeteoriteTileset, 15, METEORITE_SIZE.x, METEORITE_SIZE.y);
	m_pWarning = new TAnim(s_pWarningTileSet, 7, WARNING_SIZE.x, WARNING_SIZE.y);
}

TMeteorite::~TMeteorite()
{

}


void TMeteorite::S_Initialize()
{
	s_pMeteoriteTileset = GfxTextureLoad(TILESET_NAME);
}

void TMeteorite::SpecificUpdate()
{
	if (GfxTimeGetMilliseconds() - m_iStartWarningTime >= WARNING_DURATION)
	{
		m_tVelocity.y = m_fSpeed / GfxTimeFrameGetCurrentFPS();

		m_pSprite = m_pFall->Play(EDirection_Right);
	}

	else
	{
		m_pWarningSprite = m_pWarning->Play(EDirection_Right);
		GfxSpriteSetPosition(m_pWarningSprite, m_tPos.x - (WARNING_SIZE.x / 2.0f), m_tPos.y);
	}
}
