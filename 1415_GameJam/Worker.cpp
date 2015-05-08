
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Anim.h"
#include "Villager.h"
#include "Profession.h"
#include "Worker.h"



namespace
{
	const char * const IDLE_TILESET_NAME = "Worker\Worker_Idle.tga";
	const char * const WALK_TILESET_NAME = "Worker\Worker_Walk.tga";
	const char * const ACTION_TILESET_NAME = "Worker\Worker_Action.tga";
}


TGfxTexture * TWorker::s_pIdleTileSet = nullptr;
TGfxTexture * TWorker::s_pWalkTileSet = nullptr;
TGfxTexture * TWorker::s_pActionTileSet = nullptr;

TWorker::TWorker() :
m_pIdle(nullptr),
m_pWalk(nullptr),
m_pAction(nullptr)
{
	m_pIdle = new TAnim(s_pIdleTileSet, 1, 32, 64);
	m_pWalk = new TAnim(s_pWalkTileSet, 7, 32, 64);
	m_pAction = new TAnim(s_pActionTileSet, 7, 32, 64);
}

TWorker::~TWorker()
{

}


void TWorker::S_Initialize()
{
	s_pIdleTileSet = GfxTextureLoad(IDLE_TILESET_NAME);
	s_pWalkTileSet = GfxTextureLoad(WALK_TILESET_NAME);
	s_pActionTileSet = GfxTextureLoad(ACTION_TILESET_NAME);
}


void TWorker::ProfessionUpdate()
{

}
