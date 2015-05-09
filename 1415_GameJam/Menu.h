#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

struct TButton
{
	TGfxSprite * m_pSprite;
	TGfxVec2 m_tPosition;
	TGfxVec2 m_tSize;
	bool m_bActive;
};

class TMenu
{
public:

	static void S_Initialize();
	static void S_InitializeGame();
	static void S_MenuClose();
	static void S_MenuOpen();

	static bool S_CheckOnButton(float fPosX, float fPosY);

	static bool S_GetActive()
	{
		return s_bOpen;
	}

	static void S_Update();
	static int GetNumber(int iNbrVillager, int iColumn);
	static void S_SetTextSprite(TGfxSprite ** pSprite, int iNumber);
	static void S_Render();

private:
	enum eMenuState
	{
		eMenuState_Open,
		eMenuState_Close,
		eMenuState_OnScore,
	};

	static TGfxTexture * s_pBackgroundTexture;
	static TGfxTexture * s_pButtonPlayTexture;
	static TGfxTexture * s_pScoreTexture;

	static TGfxSprite * s_pBackground;
	static TButton * s_pButtonPlay;
	static TGfxSprite * s_pScoreSprite;
	static TGfxSprite ** s_pScoreDigit;
	static TGfxTexture * s_pDigitTexture;

	static bool s_bOpen;
};

#endif
