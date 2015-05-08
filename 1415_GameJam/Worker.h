
#ifndef WORKER_H_INCLUDED
#define WORKER_H_INCLUDED

class TWorker : public TProfession
{
public:

	TWorker();
	~TWorker();


	static void S_Initialize();


	void ProfessionUpdate();


private:

	TAnim * m_pIdle;
	static TGfxTexture * s_pIdleTileSet;

	TAnim * m_pWalk;
	static TGfxTexture * s_pWalkTileSet;

	TAnim * m_pAction;
	static TGfxTexture * s_pActionTileSet;
};

#endif
