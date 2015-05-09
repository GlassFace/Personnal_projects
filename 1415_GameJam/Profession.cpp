
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
#include "Profession.h"
#include "Worker.h"
#include "Millitary.h"
#include "Priest.h"


TProfession::TProfession() :
m_pLinkedVillager(nullptr)
{

}

TProfession::TProfession(TVillager * pLinkedVillager) :
m_pLinkedVillager(pLinkedVillager)
{

}

TProfession::~TProfession()
{

}


void TProfession::S_InitializeProfessions()
{
	TWorker::S_Initialize();
	TMillitary::S_Initialize();
	TPriest::S_Initialize();
}
