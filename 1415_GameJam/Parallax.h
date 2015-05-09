#ifndef PARALLAX_H_INCLUDED
#define PARALLAX_H_INCLUDED

class TParallax
{
public:
	TParallax();
	~TParallax();

	void Initialize();
	void Update();
	void Scroll(float fX);
	void Render() const;
protected:
	static TGfxTexture * m_pTexBackground1;
	static TGfxTexture * m_pTexBackground2;
	static TGfxTexture * m_pTexBackground3;

	TBackground * m_pBackground1;
	TBackground * m_pBackground2;
	TGfxSprite * m_pSprite;
};
#endif
