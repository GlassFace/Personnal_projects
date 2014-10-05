
typedef struct bullet bullet;		// Bullet structure
struct bullet
{
	TGfxSprite * sprite;		// Sprite

	float x;		// X position
	float y;		// Y position

	bool right;		// Goind right
	bool left;		// Goind left

	bool exist;		// Have been created
};


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

	float xrelative;		// X fake position for falling equation

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