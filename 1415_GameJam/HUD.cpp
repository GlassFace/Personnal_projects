#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Background.h"
#include "Parallax.h"
#include "Map.h"
#include <math.h>
#include "Entity.h"
#include "Dynamic.h"
#include "Villager.h"
#include "HUD.h"
#include "Building.h"
#include "House.h"


namespace
{
	const char * const MOUSE_TEXTURE_NAME = "Mouse.tga";

	const float SUICIDE_GAUGE_SIZE_X_MAX = 300.f;
	const float SUICIDE_GAUGE_SIZE_Y = 20.f;
	const float SUICIDE_GAUGE_POS_X = 1520.f;
	const float SUICIDE_GAUGE_POS_Y = 100.f;
	const float SUICIDE_GAUGE_SPEED = 3.f;
	const float SUICIDE_MALUS = 10.f;

	const float VILLAGER_COUNTER_POS_X = 100.f;
	const float VILLAGER_COUNTER_POS_Y = 100.f;
	const float SUICID_CAP = 300.f;

	const float PARALLAX_SCROLL_SPEED = 0.5f;
}

TGfxSprite * THUD::s_pVillagerCounter = nullptr;
TSuicideInfo THUD::s_tSuicideInfo;

TGfxTexture * THUD::s_pMouseTexture = nullptr;
TGfxSprite * THUD::s_pMouseSprite = nullptr;

THUD::THUD()
{
}

THUD::~THUD()
{

}

void THUD::S_Initialize()
{
	GfxSetMouseVisible(false);

	s_pMouseTexture = GfxTextureLoad(MOUSE_TEXTURE_NAME);
	s_pMouseSprite = GfxSpriteCreate(s_pMouseTexture);
	GfxSpriteSetCutout(s_pMouseSprite, 0, 0, 32, 32);
	GfxSpriteSetPivot(s_pMouseSprite, 10.0f, 10.0f);
	GfxSpriteSetPosition(s_pMouseSprite, float(GfxGetCurrentMouseX()), float(GfxGetCurrentMouseY()));


	s_pVillagerCounter = GfxTextSpriteCreate();
	GfxSpriteSetFilteringEnabled(s_pVillagerCounter, false);
	GfxTextSpritePrintf(s_pVillagerCounter, "%d villagers alive", TMap::S_GetVillagerCount()); // Get Nbr Villager Alive

	// Initialize suicid gauge sprite
	TGfxImage * pImage = GfxImageCreate(1, 1);
	GfxImageGetData(pImage)[0] = EGfxColor_White;

	TGfxTexture * pTexture = GfxTextureCreate(pImage);
	s_tSuicideInfo.m_pSuicideGauge = GfxSpriteCreate(pTexture);
	GfxSpriteSetScale(s_tSuicideInfo.m_pSuicideGauge, 0, SUICIDE_GAUGE_SIZE_Y);
	GfxSpriteSetColor(s_tSuicideInfo.m_pSuicideGauge, EGfxColor_Red);
	GfxSpriteSetPosition(s_tSuicideInfo.m_pSuicideGauge, SUICIDE_GAUGE_POS_X, SUICIDE_GAUGE_POS_Y);
	GfxSpriteSetFilteringEnabled(s_tSuicideInfo.m_pSuicideGauge, false);

	GfxImageDestroy(pImage);

	s_tSuicideInfo.m_iLastFrameLost = GfxTimeGetMilliseconds();
}

void THUD::S_Update()
{
	GfxSpriteSetPosition(s_pMouseSprite, float(GfxGetCurrentMouseX()), float(GfxGetCurrentMouseY()));

	if (GfxInputIsPressed(EGfxInputID_MouseLeft))
	{
		GfxSpriteSetCutout(s_pMouseSprite, 32, 0, 32, 32);
	}

	else
	{
		GfxSpriteSetCutout(s_pMouseSprite, 0, 0, 32, 32);
	}

	S_UpdateVillagerCounter();
	S_UpdateVillagerSuicideGauge();
	S_DisplayName();

}

void THUD::S_UpdateVillagerCounter()
{
	GfxTextSpritePrintf(s_pVillagerCounter, "%d villagers alive", TMap::S_GetVillagerCount());	// Get alive villagers count
}

void THUD::S_UpdateVillagerSuicideGauge()
{
	int iSinceLastFrame = GfxTimeGetMilliseconds() - s_tSuicideInfo.m_iLastFrameLost;
	float fLess = (iSinceLastFrame / 1000.f)* SUICIDE_GAUGE_SPEED;
	s_tSuicideInfo.m_fSuicideMalus -= fLess;

	if (s_tSuicideInfo.m_fSuicideMalus < 0.f)
	{
		s_tSuicideInfo.m_fSuicideMalus = 0.f;
	}

	GfxSpriteSetScale(s_tSuicideInfo.m_pSuicideGauge, (floorf(s_tSuicideInfo.m_fSuicideMalus)), SUICIDE_GAUGE_SIZE_Y);

	s_tSuicideInfo.m_iLastFrameLost = GfxTimeGetMilliseconds();
}

void THUD::S_OneMoreSuicide()
{
	s_tSuicideInfo.m_iTotalSuicide++;
	s_tSuicideInfo.m_fSuicideMalus += SUICIDE_MALUS;

	if (s_tSuicideInfo.m_fSuicideMalus > SUICID_CAP)
	{
		s_tSuicideInfo.m_fSuicideMalus = SUICID_CAP;
	}
	GfxSpriteSetScale(s_tSuicideInfo.m_pSuicideGauge, (floorf(s_tSuicideInfo.m_fSuicideMalus)), SUICIDE_GAUGE_SIZE_Y);
}


void THUD::S_DisplayName()
{
	for (int i = 0; i < TMap::S_GetVillagerCount(); i++)
	{
		TVillager * pVillager = TMap::S_GetVillagers()[i];
		GfxTextSpritePrintf(pVillager->GetNameSprite(), "%s", pVillager->GetName());
	}
}
void THUD::S_Render()
{
	GfxSpriteRender(s_pMouseSprite);

	GfxTextSpriteRender(s_pVillagerCounter, VILLAGER_COUNTER_POS_X, VILLAGER_COUNTER_POS_Y, EGfxColor_White, 2.0f, false, false);
	GfxSpriteRender(s_tSuicideInfo.m_pSuicideGauge);

	for (int i = 0; i < TMap::S_GetVillagerCount(); i++)
	{
		TVillager * pVillager = TMap::S_GetVillagers()[i];
		GfxTextSpriteRender(pVillager->GetNameSprite(), pVillager->GetNameLocal().x, pVillager->GetNameLocal().y - pVillager->GetSize().y + 10.0f, EGfxColor_Black, 1.0f, true, true);
	}
}

