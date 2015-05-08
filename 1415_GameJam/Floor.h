#ifndef FLOOR_H_INCLUDED
#define FLOOR_H_INCLUDED


struct TGfxSprite;
struct TGfxVec2;
 
class TFloor
{
public:
	TFloor();
	~TFloor();

	static float GetLeftSize()
	{
		return s_fLeftSize;
	}
	static float GetRightSize()
	{
		return s_fRightSize;
	}
	static TGfxVec2 & GetPosition()
	{
		return s_tPosition;
	}

	static void S_Initialize();
	static void S_Update();
	static void S_Render();

	static void S_AddExtension(bool bSide);

private:

	static TGfxSprite ** s_pSprite;
	static TGfxVec2 ** s_pPosition;

	static TGfxTexture * s_pFloorTexture;
	static TGfxTexture * s_pExtensionTexture;


	static TGfxSprite * s_pPlatformSprite;
	static float s_fLeftSize;
	static float s_fRightSize;
	static TGfxVec2 s_tPosition;


};

#endif
