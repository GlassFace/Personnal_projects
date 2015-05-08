
#include "flib.h"
#include "flib_vec2.h"
#include "Anim.h"


TAnim::TAnim()
{

}

TAnim::TAnim(const char * pTileSetName, int iFPS, int iSizeX, int iSizeY) :
m_pTileSet(nullptr),
m_pSprite(nullptr),
m_iSizeX(iSizeX),
m_iSizeY(iSizeY),
m_iFrames(0),
m_iCurrentFrame(0),
m_iFPS(iFPS)
{
	m_pTileSet = GfxTextureLoad(pTileSetName);
	m_pSprite = GfxSpriteCreate(m_pTileSet);

	m_iFrames = GfxSpriteGetSizeX(m_pSprite) / iSizeX;

	GfxSpriteSetCutout(m_pSprite, 0, 0, iSizeX, iSizeY);
}

TAnim::~TAnim()
{

}
