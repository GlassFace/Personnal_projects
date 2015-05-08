
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

	void Move();

	void SetFallVelocity(const float fVelocity);

	virtual void Die() = 0;


protected:

	Generics::EDirection m_eDirection;

	float m_fSpeed;
	TGfxVec2 m_tVelocity;

	int m_iLastMoveChoice;
	int m_iNextMoveChoice;

	int m_iLastMove;
};

#endif
