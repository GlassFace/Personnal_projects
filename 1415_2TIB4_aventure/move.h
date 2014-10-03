
void CheckCollision(float *herox, float *heroy, const bool *right, const bool *left, const float screensizex, const float screensizey, const char grid[][15]);

void GetInput(bool *right, bool *left, bool *jump, bool *wasgoingleft, bool *wasgoingright, int *delay, bool *wasfalling, float *jumpmaxheight, float *heroy);			// Get input

void MoveHero(TGfxSprite *hero, float *herox, float *heroy, int *delay, bool *wasgoingleft, bool *wasgoingright, bool *wasfalling, bool *jump, float *jumpmaxheight, const char grid[][15], const float screensizex, const float screensizey);	// Move hero