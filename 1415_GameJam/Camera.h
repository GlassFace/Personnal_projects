#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

struct TGfxVec2;

class TCamera
{
public:

	TCamera();
	~TCamera();

	static void S_Initialize();
	static void S_Update();
	static void S_UpdateLocal();
	static void S_Render();

	static TGfxVec2 & S_GetWorldPosition()
	{
		return m_tWorldPosition - TGfxVec2((GfxGetDisplaySizeX()/2.f),0.f);
	}
	
	static void S_Scroll(float fXVelocity);


private:
	static TGfxVec2 m_tWorldPosition;
};

#endif
