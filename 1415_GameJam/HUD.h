#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

const float SUICIDE_GAUGE_SIZE_X_MAX = 300.f;
const float SUICIDE_GAUGE_SIZE_Y = 20.f;
const float SUICIDE_GAUGE_POS_X = 1520.f;
const float SUICIDE_GAUGE_POS_Y = 100.f;
const float SUICIDE_GAUGE_SPEED = 1.f;
const float SUICIDE_MALUS = 10.f;

const float VILLAGER_COUNTER_POS_X = 100.f;
const float VILLAGER_COUNTER_POS_Y = 100.f;


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

	const TGfxSprite * GetVillagerCounter() const
	{
		return m_pVillagerCounter;
	}
	const TSuicideInfo & GetSuicideGauge() const
	{
		return m_tSuicideInfo;
	}
	static void S_Initialize();
	static void S_Update();
	static void S_UpdateVillagerCounter();
	static void S_UpdateVillagerSuicideGauge();
	static void S_OneMoreSuicide();
	static void S_Render();
private:
	static TGfxSprite * m_pVillagerCounter;
	static TSuicideInfo m_tSuicideInfo;

};

#endif

