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


	static void S_Initialize();


	static void S_Update();
	static void S_CheckInput();


	static void S_Render();

private:

	static TVillager * s_pDraggedVillager;
};

#endif
