
#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED

class TVillager;

class TBuilding : public TEntity
{
public:

	TBuilding();
	TBuilding(const TGfxVec2 & tPos, const TGfxVec2 & tSize);
	virtual ~TBuilding();


	static void S_InitializeBuildings();


	void Update();
	virtual void SpecificUpdate() = 0;

	bool DropCivilian(TVillager * pVillager);

	virtual bool AssignVillager(TVillager * pVillager) = 0;
	virtual void UnassignVillager(TVillager * pVillager) = 0;


protected:

	EBuildingType m_eBuildingType;

	int m_iRequiredAge;

	TVillager ** m_pAssignedVillagers;
	int m_iAssignedVillagersCount;
};

#endif
