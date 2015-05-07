
#ifndef DYNAMIC_H_INCLUDED
#define DYNAMIC_H_INCLUDED

class TDynamic : public TEntity
{
public:

	TDynamic();
	TDynamic(const TGfxVec2 & tPos, const TGfxVec2 & tSize, const float fSpeed);
	virtual ~TDynamic();


	void Update();
	virtual void SpecificUpdate() = 0;


protected:

	float m_fSpeed;
};

#endif
