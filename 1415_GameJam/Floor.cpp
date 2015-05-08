#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "floor.h"



using namespace Generics;


namespace
{
	const char * const SPRITE_FLOOR_NAME = "Terrain.tga";
	const char * const SPRITE_EXTENSION_NAME = "Extension.tga";

	const float FLOOR_POSITION_X = 960.f;
	const float FLOOR_POSITION_Y = 830.f;
	const float FLOOR_SIZE_X = 1750.f;

	const int MAX_EXTENSION = 30;
	const float EXTENSION_SIZE_X = 250.f;
	const float EMPTY_SPACE_MARGIN = 200.f;
	const float FLOOR_PENETRATION = 20.f;
}

TGfxSprite ** TFloor::s_pSprite = nullptr;
TGfxVec2 ** TFloor::s_pExtensionsPositions = nullptr;

TGfxTexture * TFloor::s_pFloorTexture = nullptr;
TGfxTexture * TFloor::s_pExtensionTexture = nullptr;

TGfxSprite * TFloor::s_pPlatformSprite = nullptr;

float TFloor::s_fLeftSize;
float TFloor::s_fRightSize;

TGfxVec2 TFloor::s_tPosition;


TFloor::TFloor()
{

}

TFloor::~TFloor()
{

}


void TFloor::S_Initialize()
{
	s_pSprite = new TGfxSprite *[MAX_EXTENSION]{ 0 };
	s_pExtensionsPositions = new TGfxVec2 *[MAX_EXTENSION]{ 0 };

	s_pFloorTexture = GfxTextureLoad(SPRITE_FLOOR_NAME);
	s_pExtensionTexture = GfxTextureLoad(SPRITE_EXTENSION_NAME);


	s_tPosition = TGfxVec2(FLOOR_POSITION_X, FLOOR_POSITION_Y);
	s_pPlatformSprite = GfxSpriteCreate(s_pFloorTexture);
	GfxSpriteSetPivot(s_pPlatformSprite, FLOOR_SIZE_X / 2.f, 0.f);
	GfxSpriteSetPosition(s_pPlatformSprite, s_tPosition.x, s_tPosition.y);
	s_fLeftSize = FLOOR_SIZE_X / 2.f;
	s_fRightSize = FLOOR_SIZE_X / 2.f;

}

void TFloor::S_Update()
{
	 
}


void TFloor::S_Render()
{
	GfxSpriteRender(s_pPlatformSprite);

	for (int i = 0; i < MAX_EXTENSION; i++)
	{
		if (s_pSprite[i] != 0)
		{
			GfxSpriteRender(s_pSprite[i]);
		}
	}

}

void TFloor::S_AddExtension(EDirection eSide) // left = true  / right = false
{
	for (int i = 0; i < MAX_EXTENSION; i++)
	{
		if (s_pSprite[i] == 0)
		{
			if (eSide == EDirection_Left)
			{
				float fPositionX = (s_tPosition.x - s_fLeftSize) - (EXTENSION_SIZE_X / 2.f) + FLOOR_PENETRATION;
				s_pExtensionsPositions[i] = new TGfxVec2(fPositionX, s_tPosition.y);
				s_fLeftSize += EXTENSION_SIZE_X - FLOOR_PENETRATION;
			}
			else
			{
				float fPositionX = (s_tPosition.x + s_fRightSize) + (EXTENSION_SIZE_X / 2.f) - FLOOR_PENETRATION;
				s_pExtensionsPositions[i] = new TGfxVec2(fPositionX, s_tPosition.y);
				s_fRightSize += EXTENSION_SIZE_X - FLOOR_PENETRATION;
			}
			s_pSprite[i] = GfxSpriteCreate(s_pExtensionTexture);
			GfxSpriteSetPosition(s_pSprite[i], s_pExtensionsPositions[i]->x, s_pExtensionsPositions[i]->y);
			GfxSpriteSetPivot(s_pSprite[i], EXTENSION_SIZE_X / 2.f, 0.f);
			return;
		}
	}
}