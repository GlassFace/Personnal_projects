#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Map.h"
#include <math.h>
#include "Entity.h"
#include "Dynamic.h"
#include "Villager.h"
#include "HUD.h"
#include "Building.h"
#include "House.h"
#include "Map.h"


namespace
{
	const float SUICIDE_GAUGE_SIZE_X_MAX = 300.f;
	const float SUICIDE_GAUGE_SIZE_Y = 20.f;
	const float SUICIDE_GAUGE_POS_X = 1520.f;
	const float SUICIDE_GAUGE_POS_Y = 100.f;
	const float SUICIDE_GAUGE_SPEED = 3.f;
	const float SUICIDE_MALUS = 10.f;

	const float VILLAGER_COUNTER_POS_X = 100.f;
	const float VILLAGER_COUNTER_POS_Y = 100.f;
	const float SUICID_CAP = 300.f;
}

TGfxSprite * THUD::m_pVillagerCounter = nullptr;
TSuicideInfo THUD::m_tSuicideInfo;

THUD::THUD()
{
}

THUD::~THUD()
{

}

void THUD::S_Initialize()
{
	m_pVillagerCounter = GfxTextSpriteCreate();
	GfxSpriteSetFilteringEnabled(m_pVillagerCounter, false);
	GfxTextSpritePrintf(m_pVillagerCounter, "%d villagers alive", TMap::S_GetVillagerCount()); // Get Nbr Villager Alive

	// Initialize suicid gauge sprite
	TGfxImage * pImage = GfxImageCreate(1, 1);
	GfxImageGetData(pImage)[0] = EGfxColor_White;

	TGfxTexture * pTexture = GfxTextureCreate(pImage);
	m_tSuicideInfo.m_pSuicideGauge = GfxSpriteCreate(pTexture);
	GfxSpriteSetScale(m_tSuicideInfo.m_pSuicideGauge, 0, SUICIDE_GAUGE_SIZE_Y);
	GfxSpriteSetColor(m_tSuicideInfo.m_pSuicideGauge, EGfxColor_Red);
	GfxSpriteSetPosition(m_tSuicideInfo.m_pSuicideGauge, SUICIDE_GAUGE_POS_X, SUICIDE_GAUGE_POS_Y);
	GfxSpriteSetFilteringEnabled(m_tSuicideInfo.m_pSuicideGauge, false);

	GfxImageDestroy(pImage);

	m_tSuicideInfo.m_iLastFrameLost = GfxTimeGetMilliseconds();
}

void THUD::S_Update()
{
	S_UpdateVillagerCounter();
	S_UpdateVillagerSuicideGauge();
}

void THUD::S_UpdateVillagerCounter()
{
	GfxTextSpritePrintf(m_pVillagerCounter, "%d villagers alive", TMap::S_GetVillagerCount());	// Get alive villagers count
}

void THUD::S_UpdateVillagerSuicideGauge()
{
	int iSinceLastFrame = GfxTimeGetMilliseconds() - m_tSuicideInfo.m_iLastFrameLost;
	float fLess = (iSinceLastFrame / 1000.f)* SUICIDE_GAUGE_SPEED;
	m_tSuicideInfo.m_fSuicideMalus -= fLess;

	if (m_tSuicideInfo.m_fSuicideMalus < 0.f)
	{
		m_tSuicideInfo.m_fSuicideMalus = 0.f;
	}

	GfxSpriteSetScale(m_tSuicideInfo.m_pSuicideGauge, (floorf(m_tSuicideInfo.m_fSuicideMalus)), SUICIDE_GAUGE_SIZE_Y);

	m_tSuicideInfo.m_iLastFrameLost = GfxTimeGetMilliseconds();
}

void THUD::S_OneMoreSuicide()
{
	m_tSuicideInfo.m_iTotalSuicide++;
	m_tSuicideInfo.m_fSuicideMalus += SUICIDE_MALUS;

	if (m_tSuicideInfo.m_fSuicideMalus > SUICID_CAP)
	{
		m_tSuicideInfo.m_fSuicideMalus = SUICID_CAP;
	}
	GfxSpriteSetScale(m_tSuicideInfo.m_pSuicideGauge, (floorf(m_tSuicideInfo.m_fSuicideMalus)), SUICIDE_GAUGE_SIZE_Y);
}

void THUD::S_Render()
{
	GfxTextSpriteRender(m_pVillagerCounter, VILLAGER_COUNTER_POS_X, VILLAGER_COUNTER_POS_Y, EGfxColor_White, 2.f, false, false);
	GfxSpriteRender(m_tSuicideInfo.m_pSuicideGauge);
}

