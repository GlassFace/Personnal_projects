
void CheckCollision(float *herox, const bool *right, const bool *left, const float screensizex, const float screensizey, const char grid[][14]);

void GetInput(bool *right, bool *left);			// Get input

void MoveHero(TGfxSprite *hero, float *herox, float *heroy, int *delay, const char grid[][14], const float screensizex, const float screensizey, const int TILE);	// Move hero