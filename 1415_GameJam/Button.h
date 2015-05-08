#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "flib_vec2.h"

class TButton
{
public:
	TButton();
	~TButton();

	const TGfxVec2 & GetPosition() const
	{
		return m_tPosition;
	}
private:
	TGfxVec2 m_tPosition;
	
};

#endif
