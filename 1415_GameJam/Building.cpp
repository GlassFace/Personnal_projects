
#include "flib.h"
#include "flib_vec2.h"
#include "Entity.h"
#include "Building.h"


TBuilding::TBuilding() :
TEntity()
{

}

TBuilding::TBuilding(const TGfxVec2 & tPos, const TGfxVec2 & tSize) :
TEntity(tPos, tSize)
{

}

TBuilding::~TBuilding()
{

}
