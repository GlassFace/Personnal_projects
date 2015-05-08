#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED



struct TSuicideInfo
{
	TSuicideInfo()
	:m_pSuicideGauge(nullptr),
	m_fSuicideMalus(300),
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


	static void S_Update();

	static void S_UpdateVillagerCounter();
	static void S_UpdateVillagerSuicideGauge();
	static void S_OneMoreSuicide();
	static void S_DisplayName();
	const TGfxSprite * GetVillagerCounter() const
	{
		return m_pVillagerCounter;
	}

	const TSuicideInfo & GetSuicideGauge() const
	{
		return m_tSuicideInfo;
	}


	static void S_Render();

private:

	static TGfxSprite * m_pVillagerCounter;
	static TSuicideInfo m_tSuicideInfo;
};

#endif

