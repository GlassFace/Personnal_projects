
void CheckCollision(float *herox, float *heroy, const float screensizex, const float screensizey, const char grid[][15]);

void GetInput(float *herox, float *heroy);			// Get input

void MoveHero(TGfxSprite *hero, float *herox, float *heroy, const char grid[][15], TGfxSprite *cases[15], const float screensizex, const float screensizey);	// Move hero



typedef struct direction direction;		// Structure for directions
struct direction
{
	bool right;
	bool left;
	bool wasgoingright;
	bool wasgoingleft;
	bool jump;
	bool wasfalling;

	float fallequationx;
};