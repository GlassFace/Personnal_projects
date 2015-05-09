#include "flib.h"
#include "flib_vec2.h"
#include <math.h>
#include "Menu.h"
#include "Background.h"
#include "Parallax.h"
#include "Map.h"
#include "HUD.h"


namespace
{
	const char * const NUMBER = "HUD\\FigureSet.tga";
	const char * const BACKGROUND = "Menu_Background.tga";
	const char * const BUTTON_PLAY = "Play.tga";
	const char * const SCORE = "Score.tga";

	const int NBR_SPRITE_2 = 5;

}

TGfxTexture * TMenu::s_pBackgroundTexture = nullptr;
TGfxTexture * TMenu::s_pButtonPlayTexture = nullptr;
TGfxTexture * TMenu::s_pScoreTexture = nullptr;

TGfxSprite * TMenu::s_pBackground = nullptr;
TButton * TMenu::s_pButtonPlay = nullptr;
TGfxSprite * TMenu::s_pScoreSprite = nullptr;
TGfxSprite ** TMenu::s_pScoreDigit = nullptr;
TGfxTexture * TMenu::s_pDigitTexture = nullptr;

bool TMenu::s_bOpen;

void TMenu::S_Initialize()
{
	///
	//s_pButtonPlay = new TButton();
	s_pScoreDigit = new TGfxSprite *[NBR_SPRITE_2]{ 0 };

	s_pDigitTexture = GfxTextureLoad(NUMBER);

	for (int i = 0; i < NBR_SPRITE_2; i++)
	{
		s_pScoreDigit[i] = GfxSpriteCreate(s_pDigitTexture);
		GfxSpriteSetPivot(s_pScoreDigit[i], 15, 30);
		GfxSpriteSetPosition(s_pScoreDigit[i], GfxGetDisplaySizeX()/2.f + i * 30, GfxGetDisplaySizeY()/2.f);
	}

	////
	s_pBackgroundTexture = GfxTextureLoad(BACKGROUND);
	s_pButtonPlayTexture = GfxTextureLoad(BUTTON_PLAY);
	s_pScoreTexture = GfxTextureLoad(SCORE);

	s_pBackground = GfxSpriteCreate(s_pBackgroundTexture);
	GfxSpriteSetPivot(s_pBackground, GfxGetDisplaySizeX() / 2.f, GfxGetDisplaySizeY() / 2.f);
	GfxSpriteSetPosition(s_pBackground, GfxGetDisplaySizeX() / 2.f, GfxGetDisplaySizeY() / 2.f);


	s_pButtonPlay->m_pSprite = GfxSpriteCreate(s_pButtonPlayTexture);
	GfxSpriteSetPivot(s_pButtonPlay->m_pSprite, 112.f, 50.f);
	s_pButtonPlay->m_tPosition = TGfxVec2(GfxGetDisplaySizeX() / 2.f, GfxGetDisplaySizeY() / 2.f);
	s_pButtonPlay->m_tSize = TGfxVec2(225.f, 100.f);
	s_pButtonPlay->m_bActive = true;
	GfxSpriteSetPosition(s_pButtonPlay->m_pSprite, s_pButtonPlay->m_tPosition.x, s_pButtonPlay->m_tPosition.y);


	s_pScoreSprite = GfxSpriteCreate(s_pScoreTexture);
	GfxSpriteSetPosition(s_pScoreSprite, GfxGetDisplaySizeX() / 2.f, GfxGetDisplaySizeY() / 2.f - 200.f);



	
	
}
void TMenu::S_InitializeGame()
{

}

void TMenu::S_MenuClose()
{
	s_bOpen = false;
}

void TMenu::S_MenuOpen()
{
	s_bOpen = true;
	S_Initialize();
}
bool TMenu::S_CheckOnButton(float fPosX, float fPosY)
{
	if (fPosX < (s_pButtonPlay->m_tPosition.x + s_pButtonPlay->m_tSize.x/2.f)
		&& fPosX > (s_pButtonPlay->m_tPosition.x - s_pButtonPlay->m_tSize.x / 2.f)
		&& fPosY <(s_pButtonPlay->m_tPosition.y + s_pButtonPlay->m_tSize.y / 2.f)
		&& fPosY >(s_pButtonPlay->m_tPosition.y - s_pButtonPlay->m_tSize.y / 2.f))
	{
			return true;
	}
	else
	{
		return false;
	}
}

int TMenu::GetNumber(int iNbrVillager, int iColumn)
{
	int iNumber = iNbrVillager;
	for (int i = 0; i < iColumn; i++)
	{
		iNumber = iNumber / 10;
	}

	int iDigit = iNumber % 10;

	return iDigit;

}


void TMenu::S_SetTextSprite(TGfxSprite ** pSprite, int iNumber)
{
	GfxSpriteSetCutout(pSprite[0], (30 * GetNumber(iNumber, 2)), 0, 30, 60);
	GfxSpriteSetCutout(pSprite[1], (30 * GetNumber(iNumber, 1)), 0, 30, 60);
	GfxSpriteSetCutout(pSprite[2], (30 * GetNumber(iNumber, 0)), 0, 30, 60);
	
}
void TMenu::S_Update()
{


	float fScore = ((TMap::S_GetVillagerCount() * 100.f) * (TMap::S_GetVillagerCount() / (THUD::GetSuicidInfo().m_iTotalSuicide)));
	int iScore = int(floorf(fScore));
	S_SetTextSprite(s_pScoreDigit, iScore);
}
void TMenu::S_Render()
{
	GfxSpriteRender(s_pBackground);
	GfxSpriteRender(s_pButtonPlay->m_pSprite);
	GfxSpriteRender(s_pScoreSprite);
	
}