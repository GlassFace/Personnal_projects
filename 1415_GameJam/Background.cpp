#include "flib.h"
#include "flib_vec2.h"
#include "Background.h"

namespace
{
	const int IMG_SIZE_X = 1920;
	const int IMG_SIZE_Y = 1080;
}
TBackground::TBackground(TGfxTexture * pTexture)
{
	for (int i = 0; i < NBR_SPRITE; i++)
	{
		m_pSprite[i] = new TSpriteInfo();
		m_pSprite[i]->m_tPosition = TGfxVec2(-IMG_SIZE_X / 2.f + i * IMG_SIZE_X, IMG_SIZE_Y / 2.f);
		m_pSprite[i]->m_pSprite = GfxSpriteCreate(pTexture);
		GfxSpriteSetPosition(m_pSprite[i]->m_pSprite, m_pSprite[i]->m_tPosition.x, m_pSprite[i]->m_tPosition.y);
		GfxSpriteSetPivot(m_pSprite[i]->m_pSprite, IMG_SIZE_X / 2.f, IMG_SIZE_Y / 2.f);
	}
}
void TBackground::Scroll(float fX)
{
	for (int i = 0; i < NBR_SPRITE; i++)
	{
		m_pSprite[i]->m_tPosition.x += fX;
		GfxSpriteSetPosition(m_pSprite[i]->m_pSprite, m_pSprite[i]->m_tPosition.x, m_pSprite[i]->m_tPosition.y);
	}
}
void TBackground::CorrectParallax()
{
	for (int i = 0; i < NBR_SPRITE; i++)
	{
		if (m_pSprite[i]->m_tPosition.x < -IMG_SIZE_X)
		{
			GfxDbgPrintf("ok\n");
			m_pSprite[i]->m_tPosition.x = GetExtremRight().x + IMG_SIZE_X;
		}
		if (m_pSprite[i]->m_tPosition.x > 2 * IMG_SIZE_X)
		{
			m_pSprite[i]->m_tPosition.x = GetExtremLeft().x - IMG_SIZE_X;
		}
		GfxSpriteSetPosition(m_pSprite[i]->m_pSprite, m_pSprite[i]->m_tPosition.x, m_pSprite[i]->m_tPosition.y);
	}
}
void TBackground::Update()
{
	CorrectParallax();
}
void TBackground::Render()
{
	for (int i = 0; i < NBR_SPRITE; i++)
	{
		GfxSpriteRender(m_pSprite[i]->m_pSprite);
	}
}


const TGfxVec2 TBackground::GetExtremLeft() const
{
	TGfxVec2 tLeftOne(IMG_SIZE_X / 2.f, IMG_SIZE_Y / 2.f);

	for (int i = 0; i < NBR_SPRITE; i++)
	{
		if (m_pSprite[i]->m_tPosition.x < tLeftOne.x)
		{
			tLeftOne = m_pSprite[i]->m_tPosition;
		}
	}
	return tLeftOne;
}

const TGfxVec2 TBackground::GetExtremRight() const
{
	TGfxVec2 tRightOne(IMG_SIZE_X / 2.f, IMG_SIZE_Y / 2.f);

	for (int i = 0; i < NBR_SPRITE; i++)
	{
		if (m_pSprite[i]->m_tPosition.x > tRightOne.x)
		{
			tRightOne = m_pSprite[i]->m_tPosition;
		}
	}

	return tRightOne;
}