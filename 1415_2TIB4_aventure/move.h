
void CheckCollision(float *herox, const bool *right, const bool *left, const float screensizex, const float screensizey, const char grid[][15]);

void GetInput(bool *right, bool *left);			// Get input

void MoveHero(TGfxSprite *hero, float *herox, float *heroy, int *delay, const char grid[][15], const float screensizex, const float screensizey);	// Move hero