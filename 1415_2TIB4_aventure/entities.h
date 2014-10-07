
#ifndef STRUCTURES
#define STRUCTURES


typedef struct direction direction;		// Structure for directions
struct direction
{
	bool right;				// Is going right
	bool left;				// Is goind left
	bool wasgoingright;		// Was going right last frame
	bool wasgoingleft;		// Was going left last frame
	bool jump;				// Is jumping
	bool wasfalling;		// Was falling last frame
	bool descending;		// Is descending during jump

	int movedelay;			// Delay between moves

	float yinitial;			// Y first position when jumping

	float v;				// Speed of movement
	float t;				// Time for jump equation
};


typedef struct hero hero;		// Hero structure
struct hero
{
	TGfxSprite * sprite;	// Sprite

	float x;				// X position
	float y;				// Y position

	direction dir;			// Directions structure
};




/*		MOVE HEADERS		*/

void CheckCollision(hero *Hero, const float screensizex, const float screensizey, const char grid[11][16]);	// Chek collisions

void GetInput(hero *Hero);			// Get input

void MoveHero(hero *Hero, const char grid[11][16], const int tilenumber[11][16], TGfxSprite *cases[20], const float screensizex, const float screensizey);	// Move hero




#endif