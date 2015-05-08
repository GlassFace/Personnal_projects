
#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

class TEntity
{
public:

	TEntity();
	TEntity(const TGfxVec2 & tPos, const TGfxVec2 & tSize);
	virtual ~TEntity();


	virtual void Update() = 0;

	const TGfxVec2 & GetPos() const;
	const TGfxVec2 & GetSize() const;

	TGfxSprite * GetSprite()
	{
		return m_pSprite;
	}


	void Render();


protected:

	TGfxSprite * m_pSprite;

	TGfxVec2 m_tPos;
	TGfxVec2 m_tSize;
};

#endif
