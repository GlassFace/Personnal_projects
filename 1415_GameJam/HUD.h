#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED


struct TSuicideInfo
{
	TSuicideInfo()
	:m_pSuicideGauge(nullptr),
	m_fSuicideMalus(0),
	m_iTotalSuicide(0)
	{

	}

	TGfxSprite * m_pSuicideGauge;
	float m_fSuicideMalus;
	int m_iTotalSuicide;
	int m_iLastFrameLost;
};



class THUD
{
public:
	THUD();
	~THUD();


	static void S_Initialize();
	void Initialize();

	static void S_Update();

	static void S_UpdateVillagerSuicideGauge();
	static void S_OneMoreSuicide();
	static void S_DisplayName();

	static const TSuicideInfo & GetSuicidInfo()
	{
		return s_tSuicideInfo;
	}

	const TGfxSprite * GetVillagerCounter() const
	{
		return s_pVillagerCounter;
	}

	const TSuicideInfo & GetSuicideGauge() const
	{
		return s_tSuicideInfo;
	}

	static int GetNumber(int iNbrVillager, int iColumn);
	static void S_SetTextSprite(TGfxSprite ** pSprite, int iNumber);

	static void S_Render();

private:

	static TGfxSprite * s_pVillagerCounter;
	static TSuicideInfo s_tSuicideInfo;

	static TGfxTexture * s_pMouseTexture;
	static TGfxSprite * s_pMouseSprite;

	static TGfxTexture * s_pDigitText;

	static TGfxTexture * s_pVillagerAliveTexture;
	static TGfxSprite * s_pVillagerAlive;
	static TGfxSprite ** s_pVillagerAliveText;

	static TGfxTexture * s_pVillagerDeadTexture;
	static TGfxSprite * s_pVillagerDead;
	static TGfxSprite ** s_pVillagerDeadText;

	static TGfxTexture * s_pSuicidometreTex;
	static TGfxTexture * s_pSuicidometreDecoTex;
	static TGfxSprite * s_pSuicidometre;
	static TGfxSprite * s_pSuicidometreDeco;


};

#endif

