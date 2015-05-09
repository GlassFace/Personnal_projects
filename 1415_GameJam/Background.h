#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

struct TGfxVec2;

const int NBR_SPRITE = 3;
struct TSpriteInfo
{
	TSpriteInfo()
	:m_pSprite(nullptr),
	m_tPosition(0.f, 0.f)
	{

	}
	TGfxSprite * m_pSprite;
	TGfxVec2 m_tPosition;
	
};

class TBackground
{
public:
	TBackground(TGfxTexture * pTexture);
	~TBackground();
	
	static void S_Initialize();
	void Scroll(float fX);
	void CorrectParallax();
	void Update();
	void Render();

	const TGfxVec2 GetExtremLeft() const;
	const TGfxVec2 GetExtremRight() const;

private:
	static TGfxTexture * m_pTexture;

	TSpriteInfo * m_pSprite[NBR_SPRITE];
};

#endif
