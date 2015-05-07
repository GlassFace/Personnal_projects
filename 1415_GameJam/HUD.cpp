#include "flib.h"
#include "HUD.h"

THUD::THUD()
: m_pVillagerCounter(GfxTextSpriteCreate())
{
}

THUD::~THUD()
{

}

void THUD::Initialize()
{
	GfxSpriteSetFilteringEnabled(m_pVillagerCounter, false);
	GfxTextSpritePrintf(m_pVillagerCounter, "%d villagers alive", 0); // Get Nbr Villager Alive

	// Initialize suicid gauge sprite
	TGfxImage * pImage = GfxImageCreate(1, 1);
	unsigned int * pData = GfxImageGetData(pImage);
	pData[0] = EGfxColor_White;
	TGfxTexture * pTexture = GfxTextureCreate(pImage);
	m_tSuicidInfo.pSuicidGauge = GfxSpriteCreate(pTexture);
	GfxSpriteSetScale(m_tSuicidInfo.pSuicidGauge, 0, SUICID_GAUGE_SIZE_Y);
	GfxSpriteSetColor(m_tSuicidInfo.pSuicidGauge, EGfxColor_Red);
	GfxSpriteSetPosition(m_tSuicidInfo.pSuicidGauge, SUICID_GAUGE_POS_X, SUICID_GAUGE_POS_Y);
	GfxSpriteSetFilteringEnabled(m_tSuicidInfo.pSuicidGauge, false);

	GfxImageDestroy(pImage);

}

void THUD::Update()
{
	UpdateVillagerCounter();
	UpdateVillagerSuicid();
}

void THUD::UpdateVillagerCounter()
{
	GfxTextSpritePrintf(m_pVillagerCounter, "%d villagers alive", 150); // Get Nbr Villager Alive
}

void THUD::UpdateVillagerSuicid()
{
	GfxSpriteSetScale(m_tSuicidInfo.pSuicidGauge, m_tSuicidInfo.iSuicidMalus, SUICID_GAUGE_SIZE_Y);
}

void THUD::Render() const
{
	GfxTextSpriteRender(m_pVillagerCounter, VILLAGER_COUNTER_POS_X, VILLAGER_COUNTER_POS_Y, EGfxColor_White, 2.f, false, false);
	GfxSpriteRender(m_tSuicidInfo.pSuicidGauge);
}

