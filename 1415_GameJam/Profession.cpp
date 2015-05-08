
#include "flib.h"
#include "flib_vec2.h"
#include "generics.h"
#include "Map.h"
#include "Entity.h"
#include "Dynamic.h"
#include "Anim.h"
#include "Villager.h"
#include "Profession.h"
#include "Worker.h"


TProfession::TProfession()
{

}

TProfession::~TProfession()
{

}


void TProfession::S_InitializeProfessions()
{
	TWorker::S_Initialize();
}
