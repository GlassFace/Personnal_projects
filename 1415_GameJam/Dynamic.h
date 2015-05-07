
#ifndef DYNAMIC_H_INCLUDED
#define DYNAMIC_H_INCLUDED

class TDynamic : public TEntity
{
public:

	TDynamic();
	TDynamic(const TGfxVec2 & tPos, const TGfxVec2 & tSize, const float fSpeed);
	virtual ~TDynamic();


	virtual void S_Initialize() = 0;


protected:

	float m_fSpeed;
};

#endif
