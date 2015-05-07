
#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED

class TVillager;

class TBuilding : public TEntity
{
public:

	TBuilding();
	TBuilding(const TGfxVec2 & tPos, const TGfxVec2 & tSize);
	virtual ~TBuilding();


	void DropCivilian(TVillager & tVillager) const;

protected:


};

#endif
