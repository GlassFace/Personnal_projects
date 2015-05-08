
#ifndef VILLAGER_H_INCLUDED
#define VILLAGER_H_INCLUDED

#include "Dynamic.h"

class TVillager : public TDynamic
{
public:

	TVillager();
	TVillager(const TGfxVec2 & tPos);
	~TVillager();


	static void S_Initialize();

	void GetRandomName();

	void SetPosition(TGfxVec2 & tPos)
	{
		 m_tPos = tPos;
		 GfxSpriteSetPosition(m_pSprite, m_tPos.x, m_tPos.y);
	}

	void SpecificUpdate();

	void RandomMove();
	void Move();

	void Die();

	bool IsMouseOver(const TGfxVec2 & tMousePos) const;

	void Render() const;

protected:

	enum EState
	{
		EState_Alive,
		EState_Dead
	};

	TGfxVec2 m_tVelocity;
	
	EState m_eState;

	int m_iLastMoveChoice;
	int m_iNextMoveChoice;

	int m_iLastMove;

	char * m_pName;

	static TGfxTexture * s_pTexture;
	static TGfxFile * s_pNamesFile;
};

#endif
