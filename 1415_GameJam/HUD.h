#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

const float SUICID_GAUGE_SIZE_X_MAX = 300.f;
const float SUICID_GAUGE_SIZE_Y = 20.f;
const float SUICID_GAUGE_POS_X = 1000.f;
const float SUICID_GAUGE_POS_Y = 100.f;
const float VILLAGER_COUNTER_POS_X = 100.f;
const float VILLAGER_COUNTER_POS_Y = 100.f;


struct TSuicidInfo
{
	TSuicidInfo()
	:pSuicidGauge(nullptr),
	iSuicidMalus(150),
	iTotalSuicid(0)
	{

	}
	TGfxSprite * pSuicidGauge;
	int iSuicidMalus;
	int iTotalSuicid;
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
	const TSuicidInfo & GetSuicidGauge() const
	{
		return m_tSuicidInfo;
	}
	void Initialize();
	void Update();
	void UpdateVillagerCounter();
	void UpdateVillagerSuicid();
	void OneMoreSuicid();
	void Render() const;
private:
	TGfxSprite * m_pVillagerCounter;
	TSuicidInfo m_tSuicidInfo;

};

#endif

