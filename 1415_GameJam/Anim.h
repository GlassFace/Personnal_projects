
#ifndef ANIM_H_INCLUDED
#define ANIM_H_INCLUDED

class TAnim
{
public:

	TAnim();
	TAnim(const char * pTileSetName, int iFPS, int iSizeX, int iSizeY);
	~TAnim();

	TGfxSprite * Play(const Generics::EDirection eDirectionFacing);

private:

	TGfxTexture * m_pTileSet;
	TGfxSprite * m_pSprite;

	int m_iSizeX;
	int m_iSizeY;

	int m_iFrames;
	int m_iCurrentFrame;

	int m_iLastFrameChange;
	int m_iFPS;		// Frames per second
};

#endif
