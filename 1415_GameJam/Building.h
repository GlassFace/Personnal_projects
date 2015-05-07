
#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED

class TCivilian;

class TBuilding : public TEntity
{
public:

	TBuilding();
	TBuilding(const TGfxVec2 & tPos, const TGfxVec2 & tSize);
	virtual ~TBuilding();


	virtual void S_Initialize() = 0;


	void DropCivilian(TCivilian & tCivilian) const;

protected:


};

#endif
