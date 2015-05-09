#ifndef BIRD_H_INCLUDED
#define BIRD_H_INCLUDED

struct TGfxVec2;
class TAnim;
class TVillager;

const int NBR_BLOOD_SPRITE = 3;

struct TBloodInfo
{
	TGfxSprite * m_pSprite;
	int iAnimBegin;
};

class TBird : public TDynamic
{
public:

	TBird();
	TBird(const TGfxVec2 & tPos);
	~TBird();


	static void S_Initialize();

	void Initialize();

	TGfxSprite * GetSprite() const
	{
		return m_pSprite;
	}
	const TGfxVec2 & GetPosition() const
	{
		return m_tPos;
	}

	void SetPosition(const TGfxVec2 & tPos)
	{
		m_tPos = tPos;
		GfxSpriteSetPosition(m_pSprite, m_tPos.x, m_tPos.y);
	}

	void SpecificUpdate();

	void FindTarget();
	void GoToTarget();
	void Escape();

	void Die();

	bool IsAlive() const;
	bool IsMouseOver(const TGfxVec2 & tMousePos) const;
	void TakeHit();
	void UpdateBlood();
	void Render() const;

protected:

	enum EState
	{
		EState_Alive,
		EState_Dead
	};

	enum EBirdAction
	{
		EBirdAction_ToTarget,
		EBirdAction_DelivringTarget,
	};

	TVillager * m_pTarget;
	TBloodInfo * m_pBlood[NBR_BLOOD_SPRITE];
	TAnim * m_pFly;
	EState m_eState;
	EBirdAction m_eAction;
	

	static TGfxTexture * s_pBirdBlood;
	static TGfxTexture * s_pBirdTileSet;
	static TGfxFile * s_pNamesFile;

	int m_iLastMove;
	int m_iHitLeft;
};

#endif

