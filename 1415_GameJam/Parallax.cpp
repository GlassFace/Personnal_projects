#include "flib.h"
#include "flib_vec2.h"
#include "Background.h"
#include "Parallax.h"

namespace
{
	const char * const PARALLAX_1 = "BackGround\\Parallax_Front.tga";
	const char * const PARALLAX_2 = "BackGround\\Parallax_Back.tga";
	const char * const PARALLAX_3 = "BackGround\\Background.tga";
}

TGfxTexture * TParallax::m_pTexBackground1 = nullptr;
TGfxTexture * TParallax::m_pTexBackground2 = nullptr;
TGfxTexture * TParallax::m_pTexBackground3 = nullptr;

TParallax::TParallax()
{

}

TParallax::~TParallax()
{

}

void TParallax::Initialize()
{
	m_pTexBackground1 = GfxTextureLoad(PARALLAX_1);
	m_pTexBackground2 = GfxTextureLoad(PARALLAX_2);
	m_pTexBackground3 = GfxTextureLoad(PARALLAX_3);

	m_pBackground1 = new TBackground(m_pTexBackground1);
	m_pBackground2 = new TBackground(m_pTexBackground2);
	m_pSprite = GfxSpriteCreate(m_pTexBackground3);
}

void TParallax::Update()
{
}
void TParallax::Scroll(float fX)
{
	float fSpeedBG1 = fX;
	float fSpeedBG2 = fX * 0.6;

	m_pBackground1->Scroll(fSpeedBG1);
	m_pBackground2->Scroll(fSpeedBG2);
}

void TParallax::Render() const
{
	GfxSpriteRender(m_pSprite);
	m_pBackground2->Render();
	m_pBackground1->Render();
}