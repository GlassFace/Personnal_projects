#include "flib.h"
#include "control.h"


TControl::TControl()
{

}

TControl::~TControl()
{

}

void TControl::Update()
{
	CheckInput();
}

void TControl::CheckInput() const
{
	if (GfxInputIsPressed(EGfxInputID_KeyArrowLeft))
	{
		// Scroll;
	}
	if (GfxInputIsPressed(EGfxInputID_KeyArrowRight))
	{
		// Scroll;
	}
	if (GfxInputIsPressed(EGfxInputID_MouseLeft))
	{
		for (int i = 0;; i++)
		{
			// Check if pressed on villager;
		}
	}
}