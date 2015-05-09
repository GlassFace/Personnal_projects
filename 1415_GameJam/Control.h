#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

class TVillager;
struct TGfxVec2;

class TControl
{
public:
	TControl();
	~TControl();
	
	const TGfxVec2 & GetMousePosition() const;


	static void S_Update();
	static void S_CheckInput();


private:

	static TVillager * s_pDraggedVillager;
};

#endif
