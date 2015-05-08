
#ifndef FLOOR_H_INCLUDED
#define FLOOR_H_INCLUDED

struct TGfxSprite;
struct TGfxVec2;
 
class TFloor
{
public:
	TFloor();
	~TFloor();


	/*		Initialize		*/

	static void S_Initialize();


	/*		Update		*/

	static void S_Update();

	static void S_AddExtension(Generics::EDirection eSide);


	/*		Getters		*/

	static TGfxSprite ** GetExtensionSprite()
	{
		return s_pSprite;
	}

	static TGfxVec2 ** GetExtensionsPositions()
	{
		return s_pExtensionsPositions;
	}

	static float GetLeftSize()
	{
		return s_fLeftSize;
	}

	static float GetRightSize()
	{
		return s_fRightSize;
	}

	static TGfxSprite * GetPlatformSprite()
	{
		return s_pPlatformSprite;
	}

	static TGfxVec2 & GetPosition()
	{
		return s_tPosition;
	}


	/*		Render		*/

	static void S_Render();


private:

	static TGfxSprite ** s_pSprite;
	static TGfxVec2 ** s_pExtensionsPositions;

	static TGfxTexture * s_pFloorTexture;
	static TGfxTexture * s_pExtensionTexture;


	static TGfxSprite * s_pPlatformSprite;
	static float s_fLeftSize;
	static float s_fRightSize;
	static TGfxVec2 s_tPosition;
};

#endif
