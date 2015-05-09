
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Meteorite.h"
#include "Floor.h"
#include "Anim.h"
#include "Camera.h"



using namespace Generics;

namespace
{
	const char * const TILESET_NAME = "Meteorite\\Meteorite.tga";
	const char * const WARNING_TILESET_NAME = "Meteorite\\Warning.tga";

	const TGfxVec2 METEORITE_SIZE = TGfxVec2(150.0f, 150.0f);
	const TGfxVec2 WARNING_SIZE = TGfxVec2(128.0f, 128.0f);

	const float METEORITE_SPEED = 2000.0f;

	const int WARNING_DURATION = 5 * SECONDS;
}


TGfxTexture * TMeteorite::s_pMeteoriteTileset = nullptr;
TGfxTexture * TMeteorite::s_pWarningTileSet = nullptr;

TMeteorite::TMeteorite() :
m_pFall(nullptr),
m_pMeteoriteSprite(nullptr),
m_pWarning(nullptr),
m_pDirtSpraySprite(nullptr),
m_bWarning(true),
m_tDestination(0.0f, 0.0f),
m_iStartWarningTime(0),
m_tPos(0.0f, -800.0f),
m_tSize(METEORITE_SIZE),
m_tVelocity(0.0f, 0.0f),
m_fSpeed(METEORITE_SPEED)
{

}

TMeteorite::TMeteorite(const TGfxVec2 & tPos) :
m_pFall(nullptr),
m_pMeteoriteSprite(nullptr),
m_pWarning(nullptr),
m_pDirtSpraySprite(nullptr),
m_bWarning(true),
m_tDestination(0.0f, 0.0f),
m_iStartWarningTime(0),
m_tPos(tPos),
m_tSize(METEORITE_SIZE),
m_tVelocity(0.0f, 0.0f),
m_fSpeed(METEORITE_SPEED)
{
	m_tDestination = TGfxVec2(tPos.x, TFloor::S_GetPosition().y);
	m_iStartWarningTime = GfxTimeGetMilliseconds();

	m_pFall = new TAnim(s_pMeteoriteTileset, 15, int(METEORITE_SIZE.x), int(METEORITE_SIZE.y));
	m_pWarning = new TAnim(s_pWarningTileSet, 7, int(WARNING_SIZE.x), int(WARNING_SIZE.y));
}

TMeteorite::~TMeteorite()
{

}


void TMeteorite::S_Initialize()
{
	s_pMeteoriteTileset = GfxTextureLoad(TILESET_NAME);
	s_pWarningTileSet = GfxTextureLoad(WARNING_TILESET_NAME);
}

void TMeteorite::Update()
{
	if (GfxTimeGetMilliseconds() - m_iStartWarningTime >= WARNING_DURATION)
	{
		m_tVelocity.y = m_fSpeed / GfxTimeFrameGetCurrentFPS();
		m_tPos += m_tVelocity;

		m_pMeteoriteSprite = m_pFall->Play(EDirection_Right);

		const TGfxVec2 tMeteoritePosWorld = TGfxVec2(m_tPos.x - (WARNING_SIZE.x / 2.0f), m_tPos.y) - TCamera::S_GetWorldPosition();
		GfxSpriteSetPosition(m_pMeteoriteSprite, tMeteoritePosWorld.x, tMeteoritePosWorld.y);

		m_bWarning = false;

		if (m_tPos.y >= TFloor::S_GetPosition().y)
		{
			// Destruction
		}
	}

	else
	{
		m_pMeteoriteSprite = m_pWarning->Play(EDirection_Right);

		const TGfxVec2 tWarningPosWorld = TGfxVec2(m_tPos.x - (WARNING_SIZE.x / 2.0f), m_tPos.y + m_tSize.y) - TCamera::S_GetWorldPosition();
		GfxSpriteSetPosition(m_pMeteoriteSprite, tWarningPosWorld.x, tWarningPosWorld.y);

		m_bWarning = true;
	}
}

void TMeteorite::Die()
{

}


void TMeteorite::Render() const
{
	if (m_pMeteoriteSprite != nullptr)
	{
		GfxSpriteRender(m_pMeteoriteSprite);
	}
}
