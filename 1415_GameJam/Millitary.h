
#ifndef MILLITARY_H_INCLUDED
#define MILLITARY_H_INCLUDED

class TMillitary : public TProfession
{
public:

	TMillitary();
	TMillitary(TVillager * pLinkedVillager);
	~TMillitary();


	void S_Initialize();


	void ProfessionUpdate();


private:

	TAnim * m_pIdle;
	static TGfxTexture * s_pIdleTileSet;

	TAnim * m_pWalk;
	static TGfxTexture * s_pWalkTileSet;

	TAnim * m_pAction;
	static TGfxTexture * s_pActionTileSet;


	int m_iLastAttackTime;
};

#endif
