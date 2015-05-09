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
#include <stdio.h>

namespace
{
	const char * const MOUSE_TEXTURE_NAME = "Mouse.tga";

	const char * const ALIVE_VILLAGER = "HUD\\VillagerHead.tga";
	const char * const DEAD_VILLAGER = "HUD\\Skull.tga";
	const char * const NUMBER = "HUD\\FigureSet.tga";
	const char * const HUD_COLOR = "HUD\\HUDJauge.tga";
	const char * const JAUGE_COLOR = "HUD\\JaugeColor.tga";

	const float SUICIDE_GAUGE_SIZE_X_MAX = 300.f;
	const float SUICIDE_GAUGE_SIZE_Y = 20.f;
	const float SUICIDE_GAUGE_POS_X = 1520.f;
	const float SUICIDE_GAUGE_POS_Y = 100.f;
	const float SUICIDE_GAUGE_SPEED = 3.f;
	const float SUICIDE_MALUS = 10.f;
	const float SUICIDE_MALUS_MAX = 300.f;

	const float VILLAGER_COUNTER_POS_X = 100.f;
	const float VILLAGER_COUNTER_POS_Y = 100.f;
	const float SUICID_CAP = 300.f;

	const float PARALLAX_SCROLL_SPEED = 0.5f;
}

TGfxSprite * THUD::s_pVillagerCounter = nullptr;
TSuicideInfo THUD::s_tSuicideInfo;

TGfxTexture * THUD::s_pMouseTexture = nullptr;
TGfxSprite * THUD::s_pMouseSprite = nullptr;

TGfxTexture * THUD::s_pDigitText = nullptr;

TGfxTexture * THUD::s_pVillagerAliveTexture = nullptr;
TGfxSprite * THUD::s_pVillagerAlive = nullptr;
TGfxSprite ** THUD::s_pVillagerAliveText = nullptr;

TGfxTexture * THUD::s_pVillagerDeadTexture = nullptr;
TGfxSprite * THUD::s_pVillagerDead = nullptr;
TGfxSprite ** THUD::s_pVillagerDeadText = nullptr;


TGfxTexture * THUD::s_pSuicidometreTex = nullptr;
TGfxTexture * THUD::s_pSuicidometreDecoTex = nullptr;

TGfxSprite * THUD::s_pSuicidometre = nullptr;
TGfxSprite * THUD::s_pSuicidometreDeco = nullptr;

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

	// Initialize villager alive counter;


	// ALIVE SPRITE
	s_pVillagerAliveTexture = GfxTextureLoad(ALIVE_VILLAGER);
	s_pVillagerAlive = GfxSpriteCreate(s_pVillagerAliveTexture);
	GfxSpriteSetPivot(s_pVillagerAlive, 32.f, 32.f);
	GfxSpriteSetPosition(s_pVillagerAlive, 100.f, 100.f);
	
	s_pDigitText = GfxTextureLoad(NUMBER);

	s_pVillagerAliveText = new TGfxSprite *[NBR_SPRITE]{ 0 };
	for (int i = 0; i < NBR_SPRITE; i++)
	{
		s_pVillagerAliveText[i] = GfxSpriteCreate(s_pDigitText);
		GfxSpriteSetPivot(s_pVillagerAliveText[i], 15, 30);
		GfxSpriteSetPosition(s_pVillagerAliveText[i], 164.f + i * 30, 100.f);
	}


	// DEAD SPRITE
	s_pVillagerDeadTexture = GfxTextureLoad(DEAD_VILLAGER);
	s_pVillagerDead = GfxSpriteCreate(s_pVillagerDeadTexture);
	GfxSpriteSetPivot(s_pVillagerDead, 32.f, 32.f);
	GfxSpriteSetPosition(s_pVillagerDead, 100.f, 164.f);
	s_pVillagerDeadText = new TGfxSprite *[NBR_SPRITE]{ 0 };
	for (int i = 0; i < NBR_SPRITE; i++)
	{
		s_pVillagerDeadText[i] = GfxSpriteCreate(s_pDigitText);
		GfxSpriteSetPivot(s_pVillagerDeadText[i], 15, 30);
		GfxSpriteSetPosition(s_pVillagerDeadText[i], 164.f + i * 30, 164.f);
	}



	// SUICIDOMETRE
	s_pSuicidometreTex = GfxTextureLoad(JAUGE_COLOR);
	s_pSuicidometreDecoTex = GfxTextureLoad(HUD_COLOR);
	s_pSuicidometre = GfxSpriteCreate(s_pSuicidometreTex);
	s_pSuicidometreDeco = GfxSpriteCreate(s_pSuicidometreDecoTex);

	GfxSpriteSetPosition(s_pSuicidometre, 1320.f, 50.f);
	GfxSpriteSetPosition(s_pSuicidometreDeco, 1320.f, 50.f);
	///

	s_pVillagerCounter = GfxTextSpriteCreate();
	GfxSpriteSetFilteringEnabled(s_pVillagerCounter, false);

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

void THUD::Initialize()
{
	for (int i = 0; i < NBR_SPRITE; i++)
	{
		GfxSpriteSetPosition(s_pVillagerAliveText[i], 164.f, 100.f + i * 30);
	}
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

	S_UpdateVillagerSuicideGauge();
	S_DisplayName();

	// update score;
	S_SetTextSprite(s_pVillagerAliveText, TMap::S_GetVillagerCount());
	S_SetTextSprite(s_pVillagerDeadText, s_tSuicideInfo.m_iTotalSuicide);

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

	GfxSpriteSetScale(s_pSuicidometre, (s_tSuicideInfo.m_fSuicideMalus / SUICIDE_MALUS_MAX), 1);

	GfxDbgPrintf("%f \n", s_tSuicideInfo.m_fSuicideMalus / SUICIDE_MALUS_MAX);
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

int THUD::GetNumber(int iNbrVillager, int iColumn)
{
	int iNumber = iNbrVillager;
	for (int i = 0; i < iColumn; i++)
	{
		iNumber = iNumber / 10;
	}

	int iDigit = iNumber % 10;

	return iDigit;

}


void THUD::S_SetTextSprite(TGfxSprite ** pSprite, int iNumber)
{
	GfxSpriteSetCutout(pSprite[0], (30 * GetNumber(iNumber, 2)), 0, 30, 60);
	GfxSpriteSetCutout(pSprite[1], (30 * GetNumber(iNumber, 1)), 0, 30, 60);
	GfxSpriteSetCutout(pSprite[2], (30 * GetNumber(iNumber, 0)), 0, 30, 60);
}


void THUD::S_Render()
{

	for (int i = 0; i < NBR_SPRITE; i++)
	{
		GfxSpriteRender(s_pVillagerAliveText[i]);
		GfxSpriteRender(s_pVillagerDeadText[i]);
	}

	GfxSpriteRender(s_pSuicidometreDeco);
	GfxSpriteRender(s_pSuicidometre);

	for (int i = 0; i < TMap::S_GetVillagerCount(); i++)
	{
		TVillager * pVillager = TMap::S_GetVillagers()[i];
		GfxTextSpriteRender(pVillager->GetNameSprite(), pVillager->GetNameLocal().x, pVillager->GetNameLocal().y - pVillager->GetSize().y + 10.0f, EGfxColor_Black, 1.0f, true, true);
	}

	GfxSpriteRender(s_pVillagerAlive);
	GfxSpriteRender(s_pVillagerDead);

	GfxSpriteRender(s_pMouseSprite);
}

