#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

struct TGfxVec2;

class TControl
{
public:
	TControl();
	~TControl();
	
	const TGfxVec2 & GetMousePosition() const;


	void Update();
	void CheckInput() const;
private:
	//TGfxVec2 m_tMousePosition;
	
};

#endif
