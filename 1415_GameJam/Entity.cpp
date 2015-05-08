
#include "flib.h"
#include "flib_vec2.h"
#include "Entity.h"


TEntity::TEntity() :
m_pSprite(nullptr),
m_tPos(0.0f, 0.0f),
m_tSize(0.0f, 0.0f)
{

}

TEntity::TEntity(const TGfxVec2 & tPos, const TGfxVec2 & tSize) :
m_pSprite(nullptr),
m_tPos(tPos),
m_tSize(tSize)
{

}

TEntity::~TEntity()
{
	if (m_pSprite != nullptr)
	{
		GfxSpriteDestroy(m_pSprite);
		m_pSprite = nullptr;
	}
}


const TGfxVec2 & TEntity::GetPos() const
{
	return m_tPos;
}

const TGfxVec2 & TEntity::GetSize() const
{
	return m_tSize;
}


void TEntity::Render()
{
	if (m_pSprite != nullptr)
	{
		GfxSpriteRender(m_pSprite);
	}
}
