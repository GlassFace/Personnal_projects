
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Background.h"
#include "Parallax.h"
#include "Map.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Anim.h"
#include "Villager.h"
#include "Building.h"
#include "Profession.h"
#include "Worker.h"
#include "House.h"
#include "Workshop.h"
#include "Enclosure.h"



using namespace Generics;

namespace
{
	const char * const ASSIGNED_VILLAGERS_TILESET_NAME = "AssignedToBuilding.tga";

	const TGfxVec2 ASSIGNED_VILLAGERS_TILESET_SIZE = TGfxVec2(92.0f, 60.0f);
}


TGfxTexture * TBuilding::s_pAssignedVillagersTileSet = nullptr;

TBuilding::TBuilding() :
TEntity(),
m_pAssignedVillagers(nullptr),
m_pAssignedVillagersSprite(nullptr),
m_iAssignedVillagersCount(0)
{
	m_pAssignedVillagersSprite = GfxSpriteCreate(s_pAssignedVillagersTileSet);
	GfxSpriteSetCutout(m_pAssignedVillagersSprite, 0, 0, int(ASSIGNED_VILLAGERS_TILESET_SIZE.x), int(ASSIGNED_VILLAGERS_TILESET_SIZE.y));
	GfxSpriteSetPivot(m_pAssignedVillagersSprite, ASSIGNED_VILLAGERS_TILESET_SIZE.x / 2.0f, ASSIGNED_VILLAGERS_TILESET_SIZE.y + m_tSize.y);
	GfxSpriteSetPosition(m_pAssignedVillagersSprite, m_tPos.x, m_tPos.y - m_tSize.y);
}

TBuilding::TBuilding(const TGfxVec2 & tPos, const TGfxVec2 & tSize) :
TEntity(tPos, tSize),
m_pAssignedVillagers(nullptr),
m_pAssignedVillagersSprite(nullptr),
m_iAssignedVillagersCount(0)
{
	m_pAssignedVillagersSprite = GfxSpriteCreate(s_pAssignedVillagersTileSet);
	GfxSpriteSetCutout(m_pAssignedVillagersSprite, 0, 0, int(ASSIGNED_VILLAGERS_TILESET_SIZE.x), int(ASSIGNED_VILLAGERS_TILESET_SIZE.y));
	GfxSpriteSetPivot(m_pAssignedVillagersSprite, ASSIGNED_VILLAGERS_TILESET_SIZE.x / 2.0f, ASSIGNED_VILLAGERS_TILESET_SIZE.y + m_tSize.y);
	GfxSpriteSetPosition(m_pAssignedVillagersSprite, m_tPos.x, m_tPos.y - m_tSize.y);
}

TBuilding::~TBuilding()
{
	if (m_pAssignedVillagers != nullptr)
	{
		for (int i = 0; i < m_iAssignedVillagersCount; i++)
		{
			m_pAssignedVillagers[i]->Unassign();
			m_pAssignedVillagers[i] = nullptr;
		}

		delete[] m_pAssignedVillagers;
		m_pAssignedVillagers = nullptr;
	}

	if (m_pAssignedVillagersSprite != nullptr)
	{
		GfxSpriteDestroy(m_pAssignedVillagersSprite);
		m_pAssignedVillagersSprite = nullptr;
	}
}


void TBuilding::S_InitializeBuildings()
{
	THouse::S_Initialize();
	TWorkshop::S_Initialize();
	TEnclosure::S_Initialize();

	s_pAssignedVillagersTileSet = GfxTextureLoad(ASSIGNED_VILLAGERS_TILESET_NAME);
}


void TBuilding::Update()
{
	SpecificUpdate();
}

bool TBuilding::DropCivilian(TVillager * pVillager)
{
	const TGfxVec2 tCurrentMouse = GetCurrentMouse();

	const bool bCollisionX = tCurrentMouse.x >= m_tPos.x - (m_tSize.x / 2.0f) && tCurrentMouse.x <= m_tPos.x + (m_tSize.x / 2.0f);
	const bool bCollisionY = tCurrentMouse.y >= m_tPos.y - m_tSize.y && tCurrentMouse.y <= m_tPos.y;

	if (bCollisionX && bCollisionY)
	{
		if (pVillager->IsOldEnough(m_iRequiredAge))
		{
			AssignVillager(pVillager);
		}

		return true;
	}
	
	return false;
}
