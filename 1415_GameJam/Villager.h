
#ifndef VILLAGER_H_INCLUDED
#define VILLAGER_H_INCLUDED

enum EAction
{
	EAction_Idle,
	EAction_Walking,
	EAction_Running,
	EAction_Action,
	EAction_Grab,
};

class TAnim;
class TProfession;
class TBuilding;

class TVillager : public TDynamic
{
	friend TProfession;
	friend class TWorker;

public:

	TVillager();
	TVillager(const TGfxVec2 & tPos);
	~TVillager();


	static void S_Initialize();

	void GetRandomName();


	void SpecificUpdate();

	void RandomMove();

	void Die();

	bool IsAlive() const;
	bool IsOldEnough(const int iAgeNeeded) const;
	bool IsMouseOver(const TGfxVec2 & tMousePos) const;

	char * GetName() const
	{
		return m_pName;
	}

	TGfxSprite * GetNameSprite() const
	{
		return m_pSpriteName;
	}

	const TGfxVec2 & GetNameLocal() const
	{
		return m_tLocalName;
	}

	EAction GetAction() const
	{
		return m_eAction;
	}

	TProfession * GetProfession()
	{
		return m_pProfession;
	}

	void SetPosition(const TGfxVec2 & tPos)
	{
		m_tPos = tPos + TGfxVec2(0.0f, m_tSize.y / 2.0f);
		GfxSpriteSetPosition(m_pSprite, m_tPos.x, m_tPos.y);
	}

	void SetLocalName(const TGfxVec2 & tPos)
	{
		m_tLocalName = tPos;
	}

	void SetProfession(TProfession * pProfession, TBuilding * pBuilding);
	void Unassign();

	void SetAction(EAction eAction);


	void Render() const;

protected:

	enum EState
	{
		EState_Alive,
		EState_Dead
	};
	
	EState m_eState;

	int iNum;

	char * m_pName;
	int m_iAge;

	EAction m_eAction;

	TProfession * m_pProfession;
	TBuilding * m_pAssignedBuilding;

	int m_iStartMoveTime;
	int m_iMoveDuration;
	int m_iIdleDuration;

private:

	TGfxSprite * m_pSpriteName;
	TGfxVec2 m_tLocalName;

	TAnim * m_pIdle;
	static TGfxTexture * s_pIdleTileSet;
	TAnim * m_pWalk;
	static TGfxTexture * s_pWalkTileSet;

	static TGfxFile * s_pNamesFile;
};

#endif
