
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Background.h"
#include "Parallax.h"
#include "Map.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Anim.h"
#include "Bird.h"
#include "Villager.h"
#include "Profession.h"
#include "Millitary.h"



using namespace Generics;

namespace
{
	const char * const IDLE_TILESET_NAME = "Millitary\\Millitary_Idle.tga";
	const char * const WALK_TILESET_NAME = "Millitary\\Millitary_Walk.tga";
	const char * const ACTION_TILESET_NAME = "Millitary\\Millitary_Action.tga";

	const int TIME_BETWEEN_SHOTS = 2 * SECONDS;

	const float SIGHT_RADIUS = 100.0f;
}


TGfxTexture * TMillitary::s_pIdleTileSet = nullptr;
TGfxTexture * TMillitary::s_pWalkTileSet = nullptr;
TGfxTexture * TMillitary::s_pActionTileSet = nullptr;

TMillitary::TMillitary()
{

}

TMillitary::~TMillitary()
{

}


void TMillitary::S_Initialize()
{
	s_pIdleTileSet = GfxTextureLoad(IDLE_TILESET_NAME);
	s_pWalkTileSet = GfxTextureLoad(WALK_TILESET_NAME);
	s_pActionTileSet = GfxTextureLoad(ACTION_TILESET_NAME);
}


void TMillitary::ProfessionUpdate()
{
	TBird ** pBirds = TMap::S_GetBirds();

	TBird * pClosestBird = nullptr;

	for (int i = 0; i < TMap::S_GetBirdsCount(); i++)
	{
		if (pBirds[i] != nullptr &&
			(pBirds[i]->GetPos() - m_pLinkedVillager->m_tPos).SquaredLength() <= (SIGHT_RADIUS * SIGHT_RADIUS))
		{
			if (pClosestBird == nullptr ||
				(pBirds[i]->GetPos() - m_pLinkedVillager->m_tPos).SquaredLength() < (pClosestBird->GetPos() - m_pLinkedVillager->m_tPos).SquaredLength())
			{
				pClosestBird = pBirds[i];
			}
		}
	}

	if (pClosestBird != nullptr)
	{
		pClosestBird->TakeHit();
	}
}
