
#ifndef PRIEST_H_INCLUDED
#define PRIEST_H_INCLUDED

class TEnclosure;

class TPriest : public TProfession
{
public:

	TPriest();
	TPriest(TVillager * pLinkedVillager);
	~TPriest();


	static void S_Initialize();


	void ProfessionUpdate();


private:

	TAnim * m_pIdle;
	static TGfxTexture * s_pIdleTileSet;

	TAnim * m_pWalk;
	static TGfxTexture * s_pWalkTileSet;

	TAnim * m_pRun;

	TAnim * m_pAction;
	static TGfxTexture * s_pActionTileSet;

	TEnclosure * m_pEnclosureTarget;
	TVillager * m_pRescuedVillager;
};

#endif
