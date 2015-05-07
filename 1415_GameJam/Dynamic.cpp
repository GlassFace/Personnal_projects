
#include "flib.h"
#include "flib_vec2.h"
#include "Entity.h"
#include "Dynamic.h"


TDynamic::TDynamic() :
TEntity(),
m_fSpeed(0.0f)
{

}

TDynamic::TDynamic(const TGfxVec2 & tPos, const TGfxVec2 & tSize, const float fSpeed) :
TEntity(tPos, tSize),
m_fSpeed(fSpeed)
{

}

TDynamic::~TDynamic()
{

}
