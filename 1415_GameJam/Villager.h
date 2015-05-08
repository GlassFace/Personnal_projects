
#ifndef VILLAGER_H_INCLUDED
#define VILLAGER_H_INCLUDED

class TAnim;

class TVillager : public TDynamic
{
public:

	TVillager();
	TVillager(const TGfxVec2 & tPos);
	~TVillager();


	static void S_Initialize();

	TGfxSprite * GetSprite() const
	{
		return m_pSprite;
	}
	const TGfxVec2 & GetPosition() const
	{
		return m_tPos;
	}

	void GetRandomName();

	void SetPosition(const TGfxVec2 & tPos)
	{
		 m_tPos = tPos + TGfxVec2(0.0f, m_tSize.y / 2.0f);
		 GfxSpriteSetPosition(m_pSprite, m_tPos.x, m_tPos.y);
	}

	void SpecificUpdate();

	void RandomMove();

	void Die();

	bool IsAlive() const;
	bool IsMouseOver(const TGfxVec2 & tMousePos) const;

	void Render() const;

protected:

	enum EState
	{
		EState_Alive,
		EState_Dead
	};
	
	EState m_eState;

	char * m_pName;

	enum EAction
	{
		EAction_Idle,
		EAction_Walking,
		EAction_Running,
		EAction_Action
	};

	EAction m_eAction;

	int m_iStartMoveTime;
	int m_iMoveDuration;
	int m_iIdleDuration;

private:

	TAnim * m_pIdle;
	static TGfxTexture * s_pIdleTileSet;
	TAnim * m_pWalk;
	static TGfxTexture * s_pWalkTileSet;

	static TGfxFile * s_pNamesFile;
};

#endif
