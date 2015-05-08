
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

	void GetRandomName();

	void SetPosition(const TGfxVec2 & tPos)
	{
		 m_tPos = tPos;
		 GfxSpriteSetPosition(m_pSprite, m_tPos.x, m_tPos.y);
	}

	void SpecificUpdate();

	void RandomMove();

	void Die();

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

	TAnim * m_pWalk;

	static TGfxTexture * s_pTexture;
	static TGfxFile * s_pNamesFile;
};

#endif
