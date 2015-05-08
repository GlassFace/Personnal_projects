
#ifndef GENERICS_H_INCLUDED
#define GENERICS_H_INCLUDED

namespace Generics
{
	enum EDirection : bool
	{
		EDirection_Right = true,
		EDirection_Left = false
	};

	const int SECONDS = 1000;
	const int PERCENTS = 100;

	const TGfxVec2 GetCurrentMouse();
}

#endif
