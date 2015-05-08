
#ifndef WORKSHOP_H_INCLUDED
#define WORKSHOP_H_INCLUDED

class TWorkshop : public TBuilding
{
public:

	TWorkshop();
	TWorkshop(const TGfxVec2 & tPos);
	~TWorkshop();


	void SpecificUpdate();

	bool AssignVillager(TVillager * pVillager);
	void UnassignVillager(TVillager * pVillager);

	void GetInput();
};

#endif
