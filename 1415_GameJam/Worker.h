
#ifndef WORKER_H_INCLUDED
#define WORKER_H_INCLUDED

class TWorker : public TProfession
{
public:

	TWorker();
	TWorker(EBuildingType eBuildingToConstruct);
	~TWorker();


	static void S_Initialize();


	void ProfessionUpdate();

	void SetBuildingsToCreate(EBuildingType eBuildingToConstruct);


private:

	float GetBuildingSize();


	TAnim * m_pIdle;
	static TGfxTexture * s_pIdleTileSet;

	TAnim * m_pWalk;
	static TGfxTexture * s_pWalkTileSet;

	TAnim * m_pAction;
	static TGfxTexture * s_pActionTileSet;


	TGfxVec2 m_tDestinationToConstruct;
	int m_iStartConstructionTime;

	EBuildingType m_eConstructionToDo;
};

#endif
