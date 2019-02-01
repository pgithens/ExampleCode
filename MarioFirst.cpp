

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_audio.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

// Music
Mix_Chunk *gMusic = NULL;
// Random globals
bool onGround=false;
bool isRunning=false;
bool isWalking=false;
bool WalkL = false;
bool WalkR = false;
bool isDead = false;
bool deathAni = false;
bool holdingJump = false;
bool endLevel = false;
bool killedEnemy = false;
bool enteredPipe = false;
bool enteredSilver = false;
bool levelChange = false;
bool axTouch = false;
int newx;
std::string level = "tiling/W11.map";

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The dimensions of the level
const int LEVEL_WIDTH = 6784;
const int LEVEL_HEIGHT = 480;

//Tile constants
const int TILE_WIDTH = 32; 
const int TILE_HEIGHT = 32; 
const int TOTAL_TILES = 3180;
const int TOTAL_TILE_SPRITES = 100;

//The different tile sprites

const int SKY_TYPE 	= 0;
const int GROUND_TYPE 	= 1;
const int SPECIAL_TYPE 	= 2;
const int GOAL_TYPE     = 3;
const int PIPE_ENTER 	= 4;
const int AXE_TYPE      = 5;
const int SILVER_TYPE   = 6;

const int TILE_G1 		= 0;
const int TILE_BRICK 		= 1;
const int TILE_STONE 		= 2;
const int TILE_Q1 		= 3;
const int TILE_HQ1 		= 4;
const int TILE_G2 		= 5;
const int TILE_BRICK2 		= 6;
const int TILE_STONE2 		= 7;
const int TILE_Q2 		= 8;
const int TILE_HQ2 		= 9;
const int TILE_SKY 		= 10;
const int TILE_BUSHL 		= 11;
const int TILE_BUSHR 		= 12;
const int TILE_BUSHM 		= 13;
const int TILE_MOUNL 		= 14;
const int TILE_MOUNM1 		= 15;
const int TILE_MOUNM3 		= 16;
const int TILE_MOUNR 		= 17;
const int TILE_MOUNT 		= 18;
const int TILE_MOUNM2		= 19;
const int TILE_OP1 		= 20;
const int TILE_OP2 		= 21;
const int TILE_OP3 		= 22;
const int TILE_OP4 		= 23;
const int TILE_OPS1 		= 24;
const int TILE_OPS2 		= 25;
const int TILE_OPS3 		= 26;
const int TILE_OPS4 		= 27;
const int TILE_OPS5 		= 28;
const int TILE_OPS6 		= 29;
const int TILE_UP1 		= 30;
const int TILE_UP2 		= 31;
const int TILE_UP3 		= 32;
const int TILE_UP4 		= 33;
const int TILE_UPS1 		= 34;
const int TILE_UPS2 		= 35;
const int TILE_UPS3 		= 36;
const int TILE_UPS4 		= 37;
const int TILE_UPS5 		= 38;
const int TILE_UPS6 		= 39;
const int TILE_CP1 		= 40;
const int TILE_CP2 		= 41;
const int TILE_CP3 		= 42;
const int TILE_CP4 		= 43;
const int TILE_CPS1		= 44;
const int TILE_CPS2 		= 45;
const int TILE_CPS3 		= 46;
const int TILE_CPS4 		= 47;
const int TILE_CPS5 		= 48;
const int TILE_CPS6 		= 49;
const int TILE_CLOUD1 		= 50;
const int TILE_CLOUD2 		= 51;
const int TILE_CLOUD3 		= 52;
const int TILE_CLOUD4 		= 53;
const int TILE_CLOUD5 		= 54;
const int TILE_CLOUD6 		= 55;
const int TILE_VINE 		= 56;
const int TILE_CLDBLK 		= 57;
const int TILE_BRBT 		= 58;
const int TILE_BRTP 		= 59;
const int TILE_CASTLETOP 	= 60;
const int TILE_CASTLEMID 	= 61;
const int TILE_CASTLEWINDR 	= 62;
const int TILE_CASTLEWALL 	= 63;
const int TILE_CASTLEWINDL	= 64;
const int TILE_CASTLEDOORT 	= 65;
const int TILE_BLACK 		= 66;
const int TILE_FLAGPOLE 	= 67;
const int TILE_FLAGTOP 		= 68;
const int TILE_EASTEREGG 	= 69;
const int TILE_BOWBLOCK 	= 70;
const int TILE_BOWQBLK 		= 71;
const int TILE_BOWQBLKH 	= 72;
const int TILE_AXE 		= 73;
const int TILE_CHAIN 		= 74;
const int TILE_DRAWBRDG 	= 75;
const int TILE_LAVATOP 		= 76;
const int TILE_WATERTOP 	= 77;
const int TILE_SNOWTOP 		= 78;
const int TILE_BBTOP 		= 79;
const int TILE_TRUNK 		= 80;
const int TILE_SMTREETOP 	= 81;
const int TILE_BGTREEBTM 	= 82;
const int TILE_BGTREETOP 	= 83;
const int TILE_FENCE 		= 84;
const int TILE_SNWBUSH 		= 85;
const int TILE_LAVABTM 		= 86;
const int TILE_WATERBTM 	= 87;
const int TILE_MUSHSTMTOP 	= 88;
const int TILE_BBMID 		= 89;
const int TILE_TREEGRNDL 	= 90;
const int TILE_TREEGRNDM 	= 91;
const int TILE_TREEGRNDR 	= 92;
const int TILE_BIGTRNK 		= 93;
const int TILE_MUSHL 		= 94;
const int TILE_MUSHM 		= 95;
const int TILE_MUSHR 		= 96; 
const int TILE_SNWBOT 		= 97;
const int TILE_MUSSTMBOT 	= 98;
const int TILE_BBBOT 		= 99;

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();
		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//The tile
class Tile
{
    public:
		//Initializes position and type
		Tile( int x, int y, int tileType, int colType );

		//Shows the tile
		void render( SDL_Rect& camera );

		//Get the tile type
		int getType();

		//Get the tile collision attribute
		int getAttribute();

		//Get the collision box
		SDL_Rect getBox();

    private:
		//The attributes of the tile
		SDL_Rect mBox;

		//The tile type
		int mType;

		// Tile collision attribute
		int cType;
};


class enemies {
	public:
		// dimensions
		static const int EN_WIDTH = 32;
		static const int EN_HEIGHT = 32;
		static const int EN_HEAD_HEIGHT = 20;
		static const int EN_BODY_HEIGHT = 32-EN_HEAD_HEIGHT;

		// Maximum axis velocity of the enemy
		static const int EN_VEL = 10;

		//Initializes the variables
		enemies(int startX, int startY, bool startAlive);

		//Update Position and liveness
		void update(int newX, int newY);

		//Moves the dot and check collision against tiles
		void move( Tile *tiles[], SDL_Rect& camera );

		//Centers the camera over the enemy

		//Shows the enemy on the screen
		virtual void render( SDL_Rect& camera, bool walk, SDL_RendererFlip flipType ) = 0;

		//Enemy is Killed
		//virtual
		void kill( SDL_Rect image, SDL_Rect& camera);

		//Get Head Collision Box
		SDL_Rect getHeadBox();

		//Get Body Collision Box
		SDL_Rect getBodyBox();

		//Get Image Box
		SDL_Rect getImageBox();
	
		//Living?
		bool getAlive();

	protected:
		//Is it alive?		
		bool alive;

		//Collision box of the enemy
		SDL_Rect head;
		SDL_Rect body;
		SDL_Rect image;
		//The velocity of the enemy
		int mVelX, mVelY;
};

class Goomba : public enemies {
	public:
		Goomba(int = 0, int = 0);
		virtual void render( SDL_Rect& camera, bool walk, SDL_RendererFlip flipType );
};

class Shell : public enemies {
	public:
		Shell(int = 0, int = 0);
		virtual void render( SDL_Rect& camera, bool walk, SDL_RendererFlip flipType );
};

class Koopa : public enemies {
	public:
		Koopa(int = 0, int = 0);
		virtual void render( SDL_Rect& camera, bool walk, SDL_RendererFlip flipType );
};

class Dot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 31;
		static const int DOT_HEIGHT = 31;

		//Maximum axis velocity of the dot
		static const int X_DOT_VEL = 10;
		static const int Y_DOT_VEL = 10;

		//Initializes the variables
		Dot();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e, Tile *[] );

		//Moves the dot and check collision against tiles
		void move( Tile *tiles[], Goomba *goombas[], Koopa *koopas[], SDL_Rect& camera );

		//Centers the camera over the dot
		void setCamera( SDL_Rect& camera );

		//Shows the dot on the screen
		void render( SDL_Rect& camera, SDL_RendererFlip, bool walk );

    private:
		//Collision box of the dot
		SDL_Rect mBox;

		//The velocity of the dot
		int mVelX, mVelY;
};


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia( Tile* tiles[] );

//Frees media and shuts down SDL
void close( Tile* tiles[] );

//Box collision detector
bool checkCollision( SDL_Rect a, SDL_Rect b );

//Checks collision box against set of tiles
bool touchesWall( SDL_Rect box, Tile* tiles[] );

bool touchesFloor( SDL_Rect box, Tile* tiles[] );

bool touchesFlagpole( SDL_Rect box, Tile* tiles[] );

bool touchesAxe( SDL_Rect box, Tile* tiles[] );

bool touchesSilver( SDL_Rect box, Tile * tiles[] );

bool touchesPipe( SDL_Rect box, Tile* tiles[] );

bool touchesGoomba( SDL_Rect box, Goomba *goombas[], SDL_Rect& camera );

bool touchesKoopa( SDL_Rect box, Koopa *koopas[], SDL_Rect& camera );

//Sets tiles from tile map
bool setTiles( Tile *tiles[] );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gDotTexture;
LTexture gTileTexture;
LTexture gGoombaTexture;
LTexture gGoomba2Texture;
LTexture gKoopa2Texture;
LTexture gKoopaTexture;
LTexture gShellTexture;
LTexture gPuffTexture;
LTexture gDeathTexture;
LTexture gDot2Texture;
LTexture gDot3Texture;
LTexture gDotJumpTexture;
LTexture gFlagTexture;
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color keyimage
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	
	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y,  SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

Tile::Tile( int x, int y, int tileType, int colType )
{
    //Get the offsets
    mBox.x = x;
    mBox.y = y;

    //Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    //Get the tile type
    mType = tileType;

    //Get the tile collision attribute
    cType = colType;
}

void Tile::render( SDL_Rect& camera )
{
    //If the tile is on screen
    if( checkCollision( camera, mBox ) )
    {
        //Show the tile
        gTileTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gTileClips[ mType ] );
    }
}

int Tile::getType()
{
    return mType;
}

int Tile::getAttribute()
{
    return cType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}

Dot::Dot()
{
    //Initialize the collision box
    mBox.x = 96;
    mBox.y = 384;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Dot::handleEvent( SDL_Event& e , Tile *tiles[])
{
  
   if(axTouch == false && enteredSilver == false && enteredPipe == false && deathAni==false && endLevel == false) {
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch(e.key.keysym.sym )
        {
            case SDLK_x: 
	    case SDLK_UP:
		if(onGround) {
			mVelY -= 3*Y_DOT_VEL;
		}
		onGround=false;
		break;
            case SDLK_LEFT: WalkL = true; break;
            case SDLK_RIGHT: WalkR = true; break;
	    case SDLK_z:
		isRunning=true; 
		 break;
        }
    }

    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_x:
	    case SDLK_UP: 
		mVelY += 2*Y_DOT_VEL;
		break;
            case SDLK_LEFT:
		WalkL = false;
		 break;
            case SDLK_RIGHT: 
		WalkR = false; 
		break;
	    case SDLK_z:
		isRunning=false;
		break;
        }
     
    } 
	}
}

void Dot::move( Tile *tiles[], Goomba *goombas[], Koopa *koopas[], SDL_Rect& camera )
{
    //Move the dot left or right
    mBox.x += mVelX; 

    //If the dot went too far to the left or right or touched a wall
    if( ( mBox.x < 0 ) || ( mBox.x + DOT_WIDTH > LEVEL_WIDTH ) || touchesWall( mBox, tiles ) )
    {
        //move back
        mBox.x -= mVelX;
	mVelX = 0;
    }
    if(WalkL) {
	mVelX-=2;
    }
    if(WalkR) {
	mVelX+=2;
    }
    if(WalkL || WalkR) {
	if((!isRunning) && mVelX>9) {
		mVelX = 9;
	}
	if((!isRunning) && mVelX<-9) {
		mVelX = -9;
	}	
	
	if(isRunning && mVelX>14) {
		mVelX = 14;
	}
	if(isRunning && mVelX<-14) {
		mVelX = -14;
	}
    }
    if(!(WalkL || WalkR) && mVelX > 0) {
	mVelX -= 7;
	if(mVelX < 0) {
		mVelX = 0;
	}
    }
    if(!(WalkL || WalkR) && mVelX < 0) {
	mVelX += 7;
	if(mVelX > 0) {
		mVelX = 0;
	}
    }
    if(killedEnemy) {
	mVelY=-15;
	killedEnemy=false;
    }	
    //Move the dot up or down
    mBox.y += mVelY;
    if(!touchesFloor(mBox, tiles) && enteredPipe == false && enteredSilver == false) {
	if (mVelY < 24) { // Max falling speed
	     mVelY+=3; // Strength of gravity
	}
    }
    // Dying via falling down ---------------------
    if(mBox.y>448 && deathAni == false) {
	mBox.y=447;
	mVelX = 0;
	mVelY = -30;
	WalkL = false;
			WalkR = false;
	isRunning = false;
	deathAni = true;
	axTouch = false;
    }
    if(deathAni) {
	if(mBox.y>448) {
		deathAni = false;
		isDead=true;
	}
    } 
    if(isDead) {
	if(level.compare("tiling/W11.map")==0 || level.compare("tiling/W22.map")==0) {
		mBox.x = 64;
		mBox.y = 384;
	}
	else if(level.compare("tiling/W33.map")==0) {
		mBox.x = 64;
		mBox.y = 192;
	}
	else {
		mBox.x = 4100;
		mBox.y = 100;
	}
	isDead = false;
	deathAni = false;
    }

    if(touchesSilver(mBox, tiles) && !enteredSilver) {
	mVelX = -3;
	enteredSilver = true;
	newx = mBox.x;
    }
    if(enteredSilver) {
	//if(mBox.x < newx - 18) {
		mBox.x = 4260;
		mBox.y = 288;
		mVelX = 0;
		enteredSilver = false;
		WalkR = false;
		WalkL = false;
		level = "tiling/WEE.map";
		isRunning = false;
		levelChange=true;
		gMusic = Mix_LoadWAV("w22w.wav");
		Mix_PlayChannel(0, gMusic, -1); 

		setTiles(tiles);
	//}
    }
    // Pipe warp
    if(touchesPipe(mBox, tiles) && !deathAni && !enteredPipe) {
	mVelX = 3;
	enteredPipe = true;
	newx = mBox.x;
    }
    if(enteredPipe) {
	//if(mBox.x > newx + 18) {
		mBox.x = 5050;
		mBox.y = 352;
		mVelX = 0;
		mVelY=-30;
		enteredPipe = false;
		WalkR = false;
		WalkL = false;
		level = "tiling/W22.map";
		levelChange = true;
		gMusic = Mix_LoadWAV("w11.wav");
		Mix_PlayChannel(0, gMusic, -1); 

		setTiles(tiles);
	//}
    }
	
    // -------------------------------------------
    int m;
    while(touchesFloor(mBox, tiles)&&!deathAni) {
		m = mBox.y % 32;
		if(mVelY>=0) {
			mBox.y = mBox.y - m;
			onGround = true;
		}
		if(mVelY<0) {
				mBox.y = mBox.y + (32-m);
		}
		if(m==0 && mVelY==0) {
			mBox.y-=32;
		}
		mVelY=0;
    }
    if(onGround && mVelY > 4) {
	onGround=false;
    }
    //If the dot went too far up or down or touched a wall
    if( ( ( mBox.y + DOT_HEIGHT > LEVEL_HEIGHT ) || touchesWall( mBox, tiles )) && !deathAni )
    {
        //move back
        mBox.y -= mVelY;
    }

    if( touchesGoomba( mBox, goombas, camera ) && deathAni == false) {
	mVelX = 0;
	mVelY = -30;
	WalkL = false;
	WalkR = false;
	isRunning = 0;
	deathAni = true;
    }

    if( touchesKoopa( mBox, koopas, camera )&& deathAni == false) {
	mVelX = 0;
	mVelY = -30;
	WalkL = false;
	WalkR = false;
	isRunning = 0;
	deathAni = true;
    }

	
    //If the user touches the flagpole
    if(touchesFlagpole(mBox, tiles)) {
	mVelX=0;
	mVelY=0;
	endLevel = true;
    }
    if(touchesAxe(mBox, tiles)&&axTouch==false) {
	mVelX=5;
	axTouch=true;
	WalkR = true;
	WalkL = false;
	isRunning = 0;
    }
        
    if(endLevel) {
	if(!touchesFloor(mBox, tiles)) {
		mVelY = 16;
	}
	if(onGround) {
		mVelX=6;
	}
	if(mBox.x>6560){
		if(level.compare("tiling/W11.map")==0) {
			level = "tiling/W22.map";
			mBox.x = 64;
			mBox.y = 384;
			gMusic = Mix_LoadWAV("w22w.wav");
			Mix_PlayChannel(0, gMusic, -1); 
		}
		else if(level.compare("tiling/W22.map")==0) {
			level = "tiling/W33.map";
			mBox.x = 64;
			mBox.y = 192;
			gMusic = Mix_LoadWAV("w33.wav");
			Mix_PlayChannel(0, gMusic, -1); 

		}
		setTiles(tiles);
		mVelX=0;
		endLevel=false;
		WalkL=false; WalkR=false; isRunning=false;
		levelChange=true;
	}
    }
    
}

void Dot::setCamera( SDL_Rect& camera )
{
	//Center the camera over the dot
	camera.x = ( mBox.x + DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( mBox.y + DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if( camera.x < 0 )
	{ 
		camera.x = 0;
	}
	if( camera.y < 0 )
	{
		camera.y = 0;
	}
	if( camera.x > LEVEL_WIDTH - camera.w )
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if( camera.y > LEVEL_HEIGHT - camera.h )
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

void Dot::render( SDL_Rect& camera, SDL_RendererFlip flipType, bool walk )
{
    //Show the dot
    	if(mVelX < 0) flipType = SDL_FLIP_HORIZONTAL;
	if(mVelX > 0) flipType = SDL_FLIP_NONE;
	if(deathAni) gDeathTexture.render( mBox.x - camera.x, mBox.y - camera.y );
	else if(endLevel && mVelY == 16 && mVelX == 0) gFlagTexture.render(mBox.x - camera.x, mBox.y - camera.y );
	else if(!onGround) gDotJumpTexture.render(mBox.x - camera.x, mBox.y - camera.y, NULL, 0.0, NULL, flipType);
	else{
		if(WalkL || WalkR) {
			if(walk)	gDot2Texture.render( mBox.x - camera.x, mBox.y - camera.y, NULL, 0.0, NULL, flipType );
			else		gDot3Texture.render(mBox.x-camera.x, mBox.y - camera.y, NULL, 0.0, NULL, flipType );
		}
		else {
			gDotTexture.render(mBox.x-camera.x, mBox.y -camera.y, NULL, 0.0, NULL, flipType );
		}
	}
}

enemies::enemies(int startX, int startY, bool startAlive) {
	alive = startAlive;

	head.x = startX;
	head.y = startY-8;
	head.w = EN_WIDTH;
	head.h = EN_HEAD_HEIGHT;

	body.x = startX;
	body.y = startY + EN_HEAD_HEIGHT;
	body.w = EN_WIDTH;
	body.h = EN_BODY_HEIGHT;	

	image.x = startX;
	image.y = startY;
	image.w = EN_WIDTH;
	image.h = EN_HEIGHT;
	

// Initialize the velocity
	mVelX = -3;
	mVelY = 0;
}

void enemies::update(int newX, int newY) { 
	this->head.x = newX;
	this->head.y = newY;
	this->body.x = newX;
	this->body.y = newY + EN_HEAD_HEIGHT;
	this->image.x = newX;
	this->image.y = newY;
}

SDL_Rect enemies::getHeadBox() {
	return head;
}

SDL_Rect enemies::getBodyBox() {
	return body;
}

SDL_Rect enemies::getImageBox() {
	return image;
}


bool enemies::getAlive() {
	return alive;
}

void enemies::move( Tile *tiles[], SDL_Rect& camera ) {
	if(alive && checkCollision(camera, body)) {
		//Move the enemie left or right
		head.x += mVelX;
		body.x += mVelX;
		image.x += mVelX;
	
		//If the enemy went too far to the left or right or touched a wall
		if( (head.x < 0 ) || ( head.x + EN_WIDTH > LEVEL_WIDTH ) || touchesWall( head, tiles ) ) {
			// move back
			head.x -= mVelX;
			body.x -= mVelX;
			image.x -= mVelX;
			mVelX = (-1)*mVelX;
		}
		
		// Move the dot up or down
		head.y +=mVelY;
		body.y +=mVelY;
		image.y +=mVelY;
		
    		if(!touchesFloor(body, tiles)) {
			if (mVelY < 24) { // Max falling speed
			     mVelY+=3; // Strength of gravity
			}
		}

		if(touchesFloor(body, tiles)) {
			body.y-=mVelY;
			head.y-=mVelY;
			image.y-=mVelY;
			mVelY = 0;
		}

		//If the enemy went to far down
		if( ( body.y + EN_BODY_HEIGHT > LEVEL_HEIGHT ) ) {
			alive = false;
			gPuffTexture.render( image.x - camera.x, image.y - camera.y );
//			kill(image, camera);
		}
	
		//If the dot went too far up or down or touched a wall
		if( ( head.y < 0 ) || touchesWall( head, tiles ) ) { 
			head.y -=mVelY;
			body.y -=mVelY;
			image.y -=mVelY;
		}
	}
}	


void enemies::render( SDL_Rect& camera, bool walk, SDL_RendererFlip flipType ) {
	// show the enemy
 	printf("%d\n", walk);
	if(mVelX < 0) flipType = SDL_FLIP_HORIZONTAL;
	if(mVelX > 0) flipType = SDL_FLIP_NONE;
	if(alive && checkCollision( camera, image) ) gDotTexture.render( image.x - camera.x, image.y - camera.y, NULL, 0.0, NULL, flipType );
}

void enemies::kill( SDL_Rect image, SDL_Rect& camera ) {
	alive = false;
	gPuffTexture.render( image.x - camera.x, image.y - camera.y );
	killedEnemy = true;
}


Shell::Shell (int startX, int startY) : enemies (startX, startY, false) {}

void Shell::render( SDL_Rect& camera, bool walk, SDL_RendererFlip flipType ) {
	SDL_Rect image = getImageBox();
	printf("%d\n", walk);
	if(mVelX < 0) flipType = SDL_FLIP_HORIZONTAL;
	if(mVelX > 0) flipType = SDL_FLIP_NONE;
	if( getAlive() && checkCollision( camera, image ) ) {
		SDL_Rect image = getImageBox();
		gKoopaTexture.render( image.x - camera.x, image.y - camera.y, NULL, 0.0, NULL, flipType );
	}
}


Koopa::Koopa (int startX, int startY) : enemies (startX, startY, true) {}

void Koopa::render( SDL_Rect& camera, bool walk, SDL_RendererFlip flipType ) {
	SDL_Rect image = getImageBox();
	if(mVelX > 0) flipType = SDL_FLIP_HORIZONTAL;
	if(mVelX < 0) flipType = SDL_FLIP_NONE;
	if( getAlive() && checkCollision(camera, image ) ) {
		SDL_Rect image = getImageBox();
		if(walk)	gKoopaTexture.render( image.x - camera.x, image.y - camera.y - 32, NULL, 0.0, NULL, flipType );
		else		gKoopa2Texture.render(image.x-camera.x, image.y - camera.y -32, NULL, 0.0, NULL, flipType );
	}
}

Goomba::Goomba (int startX, int startY) : enemies (startX, startY, true) {}

void Goomba::render( SDL_Rect& camera, bool walk, SDL_RendererFlip flipType  ) {
	SDL_Rect image = getImageBox();
	if(mVelX < 0) flipType = SDL_FLIP_HORIZONTAL;
	if(mVelX > 0) flipType = SDL_FLIP_NONE;
	if( getAlive() && checkCollision(camera, image ) ) {
		SDL_Rect image = getImageBox();
		if(walk)	gGoombaTexture.render( image.x - camera.x, image.y - camera.y, NULL, 0.0, NULL, flipType );
		else		gGoomba2Texture.render(image.x - camera.x, image.y - camera.y, NULL, 0.0, NULL, flipType );
	}
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0) {
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}
		//Create window
		gWindow = SDL_CreateWindow( "Super Mario Brothers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia( Tile* tiles[] )
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if( !gDotTexture.loadFromFile( "tiling/stand.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	
	gMusic = Mix_LoadWAV( "w11.wav");
	if(gMusic == NULL) {
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success=false;
	}
	//if(!Mix_PlayingMusic()) {
		Mix_PlayChannel(0, gMusic, -1);
	//}
	if( !gDot2Texture.loadFromFile("tiling/walk1.bmp") )
	{
		printf( "Failed to load dot texture!\n" );
	}

	if(!gDot3Texture.loadFromFile("tiling/walk2.bmp") )
	{
		printf( "Failed to load dot texture!\n" );
	}

	if(!gDotJumpTexture.loadFromFile("tiling/jump.bmp") )
	{
		printf("Failed to load dot texture\n" );
	}

	if(!gFlagTexture.loadFromFile("tiling/flag.bmp") )
	{
		printf("Failed to load dot texture\n" );
	}
	// Load Mario Death
	if( !gDeathTexture.loadFromFile( "tiling/die.bmp" ) )
	{
		printf( "Failed to load death texture\n");
		success = false;
	}

	//Load Koopa texture
	if( !gKoopaTexture.loadFromFile("tiling/kgwalk1.bmp") )
	{
		printf( "Failed to load koopa texture!\n" );
	}
	//Load Koopa texture
	if( !gKoopa2Texture.loadFromFile("tiling/kgwalk2.bmp") )
	{
		printf( "Failed to load koopa texture!\n" );
	}

	//Load Goomba Texture
	if( !gGoombaTexture.loadFromFile("tiling/gwalk1.bmp") )
	{
		printf( "Failed to load goomba texture\n");
	}
	//Load Goomba Texture
	if( !gGoomba2Texture.loadFromFile("tiling/gwalk2.bmp") )
	{
		printf( "Failed to load goomba texture\n");
	}
	
	if( !gPuffTexture.loadFromFile( "tiling/dot.bmp" ) )
	{
		printf( "Failed to load puff texture\n");
	}

	//Load tile texture
	if( !gTileTexture.loadFromFile( "tiling/tiles.png" ) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}

	//Load tile map
	if( !setTiles( tiles ) )
	{
		printf( "Failed to load tile set!\n" );
		success = false;
	}

	return success;
}

void close( Tile* tiles[] )
{
	//Deallocate tiles
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( tiles[ i ] == NULL )
		 {
			delete tiles[ i ];
			tiles[ i ] = NULL;
		 }
	}

	//Free loaded images
	gDotTexture.free();
	gTileTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	// Free music
	Mix_FreeChunk(gMusic);
	gMusic = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

bool setTiles( Tile* tiles[] )
{
	//Success flag
	bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map( level);

    //If the map couldn't be loaded
    if( !map.is_open() )
    {
		printf( "Unable to load map file!\n" );
		tilesLoaded = false;
    }
	else
	{
		//Initialize the tiles
		for( int i = 0; i < TOTAL_TILES; ++i )
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if( map.fail() )
			{
				//Stop loading map
				printf( "Error loading map: Unexpected end of file!\n" );
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
			{
				int tileAttribute;
				if( (tileType >= TILE_G1 && tileType <= TILE_STONE) || (tileType >= TILE_HQ1 && tileType <=TILE_STONE2) || tileType == TILE_HQ2 ) {
					tileAttribute = GROUND_TYPE;
				}
				else if( (tileType >= TILE_OP1 && tileType <= TILE_CPS5 && tileType != TILE_UPS4) ) {
					tileAttribute = GROUND_TYPE;
				}
				else if((tileType == TILE_UPS4)) {
					tileAttribute = PIPE_ENTER;
				}
				else if( (tileType >= TILE_MUSHL && tileType <= TILE_MUSHR) ) {
					tileAttribute = GROUND_TYPE;
				}
				else if( (tileType >= TILE_BOWBLOCK && tileType <= TILE_BOWQBLKH) || tileType == TILE_DRAWBRDG ) {
					tileAttribute = GROUND_TYPE;
				}
				else if( (tileType == TILE_VINE) ) {
					tileAttribute = GROUND_TYPE;
				}
				else if( (tileType == TILE_Q1 || tileType == TILE_Q2 || tileType == TILE_BOWQBLK) ) {
					tileAttribute = SPECIAL_TYPE;
				}
				else if((tileType == TILE_FLAGPOLE || tileType == TILE_FLAGTOP)) {
					tileAttribute = GOAL_TYPE;
				}
				else if((tileType == TILE_AXE)) {
					tileAttribute = AXE_TYPE;
				}
				else if((tileType == TILE_CPS6)) {
					tileAttribute = SILVER_TYPE;
				}
				else {
					tileAttribute = SKY_TYPE;
				}
				
				tiles[ i ] = new Tile( x, y, tileType, tileAttribute );
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf( "Error loading map: Invalid tile type at %d!\n", i );
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if( x >= LEVEL_WIDTH )
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}
		
		//Clip the sprite sheet
		if( tilesLoaded )
		{


				gTileClips[ TILE_G1 ].y = 0;
				gTileClips[ TILE_G1 ].x = 0;
				gTileClips[ TILE_G1 ].w = TILE_WIDTH;
				gTileClips[ TILE_G1 ].h = TILE_HEIGHT;

				gTileClips[ TILE_BRICK ].y = 0;
				gTileClips[ TILE_BRICK ].x = 32;
				gTileClips[ TILE_BRICK ].w = TILE_WIDTH;
				gTileClips[ TILE_BRICK ].h = TILE_HEIGHT;

				gTileClips[ TILE_STONE ].y = 0;
				gTileClips[ TILE_STONE ].x = 64;
				gTileClips[ TILE_STONE ].w = TILE_WIDTH;
				gTileClips[ TILE_STONE ].h = TILE_HEIGHT;

				gTileClips[ TILE_Q1 ].y = 0;
				gTileClips[ TILE_Q1 ].x = 96;
				gTileClips[ TILE_Q1 ].w = TILE_WIDTH;
				gTileClips[ TILE_Q1 ].h = TILE_HEIGHT;

				gTileClips[ TILE_HQ1 ].y = 0;
				gTileClips[ TILE_HQ1 ].x = 128;
				gTileClips[ TILE_HQ1 ].w = TILE_WIDTH;
				gTileClips[ TILE_HQ1 ].h = TILE_HEIGHT;

				gTileClips[ TILE_G2 ].y = 0;
				gTileClips[ TILE_G2 ].x = 160;
				gTileClips[ TILE_G2 ].w = TILE_WIDTH;
				gTileClips[ TILE_G2 ].h = TILE_HEIGHT;

				gTileClips[ TILE_BRICK2 ].y = 0;
				gTileClips[ TILE_BRICK2 ].x = 192;
				gTileClips[ TILE_BRICK2 ].w = TILE_WIDTH;
				gTileClips[ TILE_BRICK2 ].h = TILE_HEIGHT;

				gTileClips[ TILE_STONE2 ].y = 0;
				gTileClips[ TILE_STONE2 ].x = 224;
				gTileClips[ TILE_STONE2 ].w = TILE_WIDTH;
				gTileClips[ TILE_STONE2 ].h = TILE_HEIGHT;

				gTileClips[ TILE_Q2 ].y = 0;
				gTileClips[ TILE_Q2 ].x = 256;
				gTileClips[ TILE_Q2 ].w = TILE_WIDTH;
				gTileClips[ TILE_Q2 ].h = TILE_HEIGHT;

				gTileClips[ TILE_HQ2 ].y = 0;
				gTileClips[ TILE_HQ2 ].x = 288;
				gTileClips[ TILE_HQ2 ].w = TILE_WIDTH;
				gTileClips[ TILE_HQ2 ].h = TILE_HEIGHT;

				gTileClips[ TILE_SKY ].y = 32;
				gTileClips[ TILE_SKY ].x = 0;
				gTileClips[ TILE_SKY ].w = TILE_WIDTH;
				gTileClips[ TILE_SKY ].h = TILE_HEIGHT;

				gTileClips[ TILE_BUSHL ].y = 32;
				gTileClips[ TILE_BUSHL ].x = 32;
				gTileClips[ TILE_BUSHL ].w = TILE_WIDTH;
				gTileClips[ TILE_BUSHL ].h = TILE_HEIGHT;

				gTileClips[ TILE_BUSHR ].y = 32;
				gTileClips[ TILE_BUSHR ].x = 64;
				gTileClips[ TILE_BUSHR ].w = TILE_WIDTH;
				gTileClips[ TILE_BUSHR ].h = TILE_HEIGHT;

				gTileClips[ TILE_BUSHM ].y = 32;
				gTileClips[ TILE_BUSHM ].x = 96;
				gTileClips[ TILE_BUSHM ].w = TILE_WIDTH;
				gTileClips[ TILE_BUSHM ].h = TILE_HEIGHT;

				gTileClips[ TILE_MOUNL ].y = 32;
				gTileClips[ TILE_MOUNL ].x = 128;
				gTileClips[ TILE_MOUNL ].w = TILE_WIDTH;
				gTileClips[ TILE_MOUNL ].h = TILE_HEIGHT;

				gTileClips[ TILE_MOUNM1 ].y = 32;
				gTileClips[ TILE_MOUNM1 ].x = 160;
				gTileClips[ TILE_MOUNM1 ].w = TILE_WIDTH;
				gTileClips[ TILE_MOUNM1 ].h = TILE_HEIGHT;

				gTileClips[ TILE_MOUNM3 ].y = 32;
				gTileClips[ TILE_MOUNM3 ].x = 192;
				gTileClips[ TILE_MOUNM3 ].w = TILE_WIDTH;
				gTileClips[ TILE_MOUNM3 ].h = TILE_HEIGHT;

				gTileClips[ TILE_MOUNR ].y = 32;
				gTileClips[ TILE_MOUNR ].x = 224;
				gTileClips[ TILE_MOUNR ].w = TILE_WIDTH;
				gTileClips[ TILE_MOUNR ].h = TILE_HEIGHT;

				gTileClips[ TILE_MOUNT ].y = 32;
				gTileClips[ TILE_MOUNT ].x = 256;
				gTileClips[ TILE_MOUNT ].w = TILE_WIDTH;
				gTileClips[ TILE_MOUNT ].h = TILE_HEIGHT;

				gTileClips[ TILE_MOUNM2 ].y = 32;
				gTileClips[ TILE_MOUNM2 ].x = 288;
				gTileClips[ TILE_MOUNM2 ].w = TILE_WIDTH;
				gTileClips[ TILE_MOUNM2 ].h = TILE_HEIGHT;

				gTileClips[ TILE_OP1 ].y = 64;
				gTileClips[ TILE_OP1 ].x = 0;
				gTileClips[ TILE_OP1 ].w = TILE_WIDTH;
				gTileClips[ TILE_OP1 ].h = TILE_HEIGHT;

				gTileClips[ TILE_OP2 ].y = 64;
				gTileClips[ TILE_OP2 ].x = 32;
				gTileClips[ TILE_OP2 ].w = TILE_WIDTH;
				gTileClips[ TILE_OP2 ].h = TILE_HEIGHT;

				gTileClips[ TILE_OP3 ].y = 64;
				gTileClips[ TILE_OP3 ].x = 64;
				gTileClips[ TILE_OP3 ].w = TILE_WIDTH;
				gTileClips[ TILE_OP3 ].h = TILE_HEIGHT;

				gTileClips[ TILE_OP4 ].y = 64;
				gTileClips[ TILE_OP4 ].x = 96;
				gTileClips[ TILE_OP4 ].w = TILE_WIDTH;
				gTileClips[ TILE_OP4 ].h = TILE_HEIGHT;

				gTileClips[ TILE_OPS1 ].y = 64;
				gTileClips[ TILE_OPS1 ].x = 128;
				gTileClips[ TILE_OPS1 ].w = TILE_WIDTH;
				gTileClips[ TILE_OPS1 ].h = TILE_HEIGHT;

				gTileClips[ TILE_OPS2 ].y = 64;
				gTileClips[ TILE_OPS2 ].x = 160;
				gTileClips[ TILE_OPS2 ].w = TILE_WIDTH;
				gTileClips[ TILE_OPS2 ].h = TILE_HEIGHT;

				gTileClips[ TILE_OPS3 ].y = 64;
				gTileClips[ TILE_OPS3 ].x = 192;
				gTileClips[ TILE_OPS3 ].w = TILE_WIDTH;
				gTileClips[ TILE_OPS3 ].h = TILE_HEIGHT;

				gTileClips[ TILE_OPS4 ].y = 64;
				gTileClips[ TILE_OPS4 ].x = 224;
				gTileClips[ TILE_OPS4 ].w = TILE_WIDTH;
				gTileClips[ TILE_OPS4 ].h = TILE_HEIGHT;

				gTileClips[ TILE_OPS5 ].y = 64;
				gTileClips[ TILE_OPS5 ].x = 256;
				gTileClips[ TILE_OPS5 ].w = TILE_WIDTH;
				gTileClips[ TILE_OPS5 ].h = TILE_HEIGHT;

				gTileClips[ TILE_OPS6 ].y = 64;
				gTileClips[ TILE_OPS6 ].x = 288;
				gTileClips[ TILE_OPS6 ].w = TILE_WIDTH;
				gTileClips[ TILE_OPS6 ].h = TILE_HEIGHT;

				gTileClips[ TILE_UP1 ].y = 96;
				gTileClips[ TILE_UP1 ].x = 0;
				gTileClips[ TILE_UP1 ].w = TILE_WIDTH;
				gTileClips[ TILE_UP1 ].h = TILE_HEIGHT;

				gTileClips[ TILE_UP2 ].y = 96;
				gTileClips[ TILE_UP2 ].x = 32;
				gTileClips[ TILE_UP2 ].w = TILE_WIDTH;
				gTileClips[ TILE_UP2 ].h = TILE_HEIGHT;

				gTileClips[ TILE_UP3 ].y = 96;
				gTileClips[ TILE_UP3 ].x = 64;
				gTileClips[ TILE_UP3 ].w = TILE_WIDTH;
				gTileClips[ TILE_UP3 ].h = TILE_HEIGHT;

				gTileClips[ TILE_UP4 ].y = 96;
				gTileClips[ TILE_UP4 ].x = 96;
				gTileClips[ TILE_UP4 ].w = TILE_WIDTH;
				gTileClips[ TILE_UP4 ].h = TILE_HEIGHT;

				gTileClips[ TILE_UPS1 ].y = 96;
				gTileClips[ TILE_UPS1 ].x = 128;
				gTileClips[ TILE_UPS1 ].w = TILE_WIDTH;
				gTileClips[ TILE_UPS1 ].h = TILE_HEIGHT;

				gTileClips[ TILE_UPS2 ].y = 96;
				gTileClips[ TILE_UPS2 ].x = 160;
				gTileClips[ TILE_UPS2 ].w = TILE_WIDTH;
				gTileClips[ TILE_UPS2 ].h = TILE_HEIGHT;

				gTileClips[ TILE_UPS3 ].y = 96;
				gTileClips[ TILE_UPS3 ].x = 192;
				gTileClips[ TILE_UPS3 ].w = TILE_WIDTH;
				gTileClips[ TILE_UPS3 ].h = TILE_HEIGHT;

				gTileClips[ TILE_UPS4 ].y = 96;
				gTileClips[ TILE_UPS4 ].x = 224;
				gTileClips[ TILE_UPS4 ].w = TILE_WIDTH;
				gTileClips[ TILE_UPS4 ].h = TILE_HEIGHT;

				gTileClips[ TILE_UPS5 ].y = 96;
				gTileClips[ TILE_UPS5 ].x = 256;
				gTileClips[ TILE_UPS5 ].w = TILE_WIDTH;
				gTileClips[ TILE_UPS5 ].h = TILE_HEIGHT;

				gTileClips[ TILE_UPS6 ].y = 96;
				gTileClips[ TILE_UPS6 ].x = 288;
				gTileClips[ TILE_UPS6 ].w = TILE_WIDTH;
				gTileClips[ TILE_UPS6 ].h = TILE_HEIGHT;

				gTileClips[ TILE_CP1 ].y = 128;
				gTileClips[ TILE_CP1 ].x = 0;
				gTileClips[ TILE_CP1 ].w = TILE_WIDTH;
				gTileClips[ TILE_CP1 ].h = TILE_HEIGHT;

				gTileClips[ TILE_CP2 ].y = 128;
				gTileClips[ TILE_CP2 ].x = 32;
				gTileClips[ TILE_CP2 ].w = TILE_WIDTH;
				gTileClips[ TILE_CP2 ].h = TILE_HEIGHT;

				gTileClips[ TILE_CP3 ].y = 128;
				gTileClips[ TILE_CP3 ].x = 64;
				gTileClips[ TILE_CP3 ].w = TILE_WIDTH;
				gTileClips[ TILE_CP3 ].h = TILE_HEIGHT;

				gTileClips[ TILE_CP4 ].y = 128;
				gTileClips[ TILE_CP4 ].x = 96;
				gTileClips[ TILE_CP4 ].w = TILE_WIDTH;
				gTileClips[ TILE_CP4 ].h = TILE_HEIGHT;

				gTileClips[ TILE_CPS1 ].y = 128;
				gTileClips[ TILE_CPS1 ].x = 128;
				gTileClips[ TILE_CPS1 ].w = TILE_WIDTH;
				gTileClips[ TILE_CPS1 ].h = TILE_HEIGHT;

				gTileClips[ TILE_CPS2 ].y = 128;
				gTileClips[ TILE_CPS2 ].x = 160;
				gTileClips[ TILE_CPS2 ].w = TILE_WIDTH;
				gTileClips[ TILE_CPS2 ].h = TILE_HEIGHT;

				gTileClips[ TILE_CPS3 ].y = 128;
				gTileClips[ TILE_CPS3 ].x = 192;
				gTileClips[ TILE_CPS3 ].w = TILE_WIDTH;
				gTileClips[ TILE_CPS3 ].h = TILE_HEIGHT;

				gTileClips[ TILE_CPS4 ].y = 128;
				gTileClips[ TILE_CPS4 ].x = 224;
				gTileClips[ TILE_CPS4 ].w = TILE_WIDTH;
				gTileClips[ TILE_CPS4 ].h = TILE_HEIGHT;

				gTileClips[ TILE_CPS5 ].y = 128;
				gTileClips[ TILE_CPS5 ].x = 256;
				gTileClips[ TILE_CPS5 ].w = TILE_WIDTH;
				gTileClips[ TILE_CPS5 ].h = TILE_HEIGHT;

				gTileClips[ TILE_CPS6 ].y = 128;
				gTileClips[ TILE_CPS6 ].x = 288;
				gTileClips[ TILE_CPS6 ].w = TILE_WIDTH;
				gTileClips[ TILE_CPS6 ].h = TILE_HEIGHT;

				gTileClips[ TILE_CLOUD1 ].y = 160;
				gTileClips[ TILE_CLOUD1 ].x = 0;
				gTileClips[ TILE_CLOUD1 ].w = TILE_WIDTH;
				gTileClips[ TILE_CLOUD1 ].h = TILE_HEIGHT;

				gTileClips[ TILE_CLOUD2 ].y = 160;
				gTileClips[ TILE_CLOUD2 ].x = 32;
				gTileClips[ TILE_CLOUD2 ].w = TILE_WIDTH;
				gTileClips[ TILE_CLOUD2 ].h = TILE_HEIGHT;

				gTileClips[ TILE_CLOUD3 ].y = 160;
				gTileClips[ TILE_CLOUD3 ].x = 64;
				gTileClips[ TILE_CLOUD3 ].w = TILE_WIDTH;
				gTileClips[ TILE_CLOUD3 ].h = TILE_HEIGHT;

				gTileClips[ TILE_CLOUD4 ].y = 160;
				gTileClips[ TILE_CLOUD4 ].x = 96;
				gTileClips[ TILE_CLOUD4 ].w = TILE_WIDTH;
				gTileClips[ TILE_CLOUD4 ].h = TILE_HEIGHT;

				gTileClips[ TILE_CLOUD5 ].y = 160;
				gTileClips[ TILE_CLOUD5 ].x = 128;
				gTileClips[ TILE_CLOUD5 ].w = TILE_WIDTH;
				gTileClips[ TILE_CLOUD5 ].h = TILE_HEIGHT;

				gTileClips[ TILE_CLOUD6 ].y = 160;
				gTileClips[ TILE_CLOUD6 ].x = 160;
				gTileClips[ TILE_CLOUD6 ].w = TILE_WIDTH;
				gTileClips[ TILE_CLOUD6 ].h = TILE_HEIGHT;

				gTileClips[ TILE_VINE ].y = 160;
				gTileClips[ TILE_VINE ].x = 192;
				gTileClips[ TILE_VINE ].w = TILE_WIDTH;
				gTileClips[ TILE_VINE ].h = TILE_HEIGHT;

				gTileClips[ TILE_CLDBLK ].y = 160;
				gTileClips[ TILE_CLDBLK ].x = 224;
				gTileClips[ TILE_CLDBLK ].w = TILE_WIDTH;
				gTileClips[ TILE_CLDBLK ].h = TILE_HEIGHT;

				gTileClips[ TILE_BRBT ].y = 160;
				gTileClips[ TILE_BRBT ].x = 256;
				gTileClips[ TILE_BRBT ].w = TILE_WIDTH;
				gTileClips[ TILE_BRBT ].h = TILE_HEIGHT;

				gTileClips[ TILE_BRTP ].y = 160;
				gTileClips[ TILE_BRTP ].x = 288;
				gTileClips[ TILE_BRTP ].w = TILE_WIDTH;
				gTileClips[ TILE_BRTP ].h = TILE_HEIGHT;

				gTileClips[ TILE_CASTLETOP ].y = 192;
				gTileClips[ TILE_CASTLETOP ].x = 0;
				gTileClips[ TILE_CASTLETOP ].w = TILE_WIDTH;
				gTileClips[ TILE_CASTLETOP ].h = TILE_HEIGHT;

				gTileClips[ TILE_CASTLEMID ].y = 192;
				gTileClips[ TILE_CASTLEMID ].x = 32;
				gTileClips[ TILE_CASTLEMID ].w = TILE_WIDTH;
				gTileClips[ TILE_CASTLEMID ].h = TILE_HEIGHT;

				gTileClips[ TILE_CASTLEWINDR ].y = 192;
				gTileClips[ TILE_CASTLEWINDR ].x = 64;
				gTileClips[ TILE_CASTLEWINDR ].w = TILE_WIDTH;
				gTileClips[ TILE_CASTLEWINDR ].h = TILE_HEIGHT;

				gTileClips[ TILE_CASTLEWALL ].y = 192;
				gTileClips[ TILE_CASTLEWALL ].x = 96;
				gTileClips[ TILE_CASTLEWALL ].w = TILE_WIDTH;
				gTileClips[ TILE_CASTLEWALL ].h = TILE_HEIGHT;

				gTileClips[ TILE_CASTLEWINDL ].y = 192;
				gTileClips[ TILE_CASTLEWINDL ].x = 128;
				gTileClips[ TILE_CASTLEWINDL ].w = TILE_WIDTH;
				gTileClips[ TILE_CASTLEWINDL ].h = TILE_HEIGHT;

				gTileClips[ TILE_CASTLEDOORT ].y = 192;
				gTileClips[ TILE_CASTLEDOORT ].x = 160;
				gTileClips[ TILE_CASTLEDOORT ].w = TILE_WIDTH;
				gTileClips[ TILE_CASTLEDOORT ].h = TILE_HEIGHT;

				gTileClips[ TILE_BLACK ].y = 192;
				gTileClips[ TILE_BLACK ].x = 192;
				gTileClips[ TILE_BLACK ].w = TILE_WIDTH;
				gTileClips[ TILE_BLACK ].h = TILE_HEIGHT;

				gTileClips[ TILE_FLAGPOLE ].y = 192;
				gTileClips[ TILE_FLAGPOLE ].x = 224;
				gTileClips[ TILE_FLAGPOLE ].w = TILE_WIDTH;
				gTileClips[ TILE_FLAGPOLE ].h = TILE_HEIGHT;

				gTileClips[ TILE_FLAGTOP ].y = 192;
				gTileClips[ TILE_FLAGTOP ].x = 256;
				gTileClips[ TILE_FLAGTOP ].w = TILE_WIDTH;
				gTileClips[ TILE_FLAGTOP ].h = TILE_HEIGHT;

				gTileClips[ TILE_EASTEREGG ].y = 192;
				gTileClips[ TILE_EASTEREGG ].x = 288;
				gTileClips[ TILE_EASTEREGG ].w = TILE_WIDTH;
				gTileClips[ TILE_EASTEREGG ].h = TILE_HEIGHT;

				gTileClips[ TILE_BOWBLOCK ].y = 224;

				gTileClips[ TILE_BOWBLOCK ].x = 0;
				gTileClips[ TILE_BOWBLOCK ].w = TILE_WIDTH;
				gTileClips[ TILE_BOWBLOCK ].h = TILE_HEIGHT;

				gTileClips[ TILE_BOWQBLK ].y = 224;
				gTileClips[ TILE_BOWQBLK ].x = 32;
				gTileClips[ TILE_BOWQBLK ].w = TILE_WIDTH;
				gTileClips[ TILE_BOWQBLK ].h = TILE_HEIGHT;

				gTileClips[ TILE_BOWQBLKH ].y = 224;
				gTileClips[ TILE_BOWQBLKH ].x = 64;
				gTileClips[ TILE_BOWQBLKH ].w = TILE_WIDTH;
				gTileClips[ TILE_BOWQBLKH ].h = TILE_HEIGHT;

				gTileClips[ TILE_AXE ].y = 224;
				gTileClips[ TILE_AXE ].x = 96;
				gTileClips[ TILE_AXE ].w = TILE_WIDTH;
				gTileClips[ TILE_AXE ].h = TILE_HEIGHT;

				gTileClips[ TILE_CHAIN ].y = 224;
				gTileClips[ TILE_CHAIN ].x = 128;
				gTileClips[ TILE_CHAIN ].w = TILE_WIDTH;
				gTileClips[ TILE_CHAIN ].h = TILE_HEIGHT;

				gTileClips[ TILE_DRAWBRDG ].y = 224;
				gTileClips[ TILE_DRAWBRDG ].x = 160;
				gTileClips[ TILE_DRAWBRDG ].w = TILE_WIDTH;
				gTileClips[ TILE_DRAWBRDG ].h = TILE_HEIGHT;

				gTileClips[ TILE_LAVATOP ].y = 224;
				gTileClips[ TILE_LAVATOP ].x = 192;
				gTileClips[ TILE_LAVATOP ].w = TILE_WIDTH;
				gTileClips[ TILE_LAVATOP ].h = TILE_HEIGHT;

				gTileClips[ TILE_WATERTOP ].y = 224;
				gTileClips[ TILE_WATERTOP ].x = 224;
				gTileClips[ TILE_WATERTOP ].w = TILE_WIDTH;
				gTileClips[ TILE_WATERTOP ].h = TILE_HEIGHT;

				gTileClips[ TILE_SNOWTOP ].y = 224;
				gTileClips[ TILE_SNOWTOP ].x = 256;
				gTileClips[ TILE_SNOWTOP ].w = TILE_WIDTH;
				gTileClips[ TILE_SNOWTOP ].h = TILE_HEIGHT;

				gTileClips[ TILE_BBTOP ].y = 224;
				gTileClips[ TILE_BBTOP ].x = 288;
				gTileClips[ TILE_BBTOP ].w = TILE_WIDTH;
				gTileClips[ TILE_BBTOP ].h = TILE_HEIGHT;

				gTileClips[ TILE_TRUNK ].y = 256;
				gTileClips[ TILE_TRUNK ].x = 0;
				gTileClips[ TILE_TRUNK ].w = TILE_WIDTH;
				gTileClips[ TILE_TRUNK ].h = TILE_HEIGHT;

				gTileClips[ TILE_SMTREETOP ].y = 256;
				gTileClips[ TILE_SMTREETOP ].x = 32;
				gTileClips[ TILE_SMTREETOP ].w = TILE_WIDTH;
				gTileClips[ TILE_SMTREETOP ].h = TILE_HEIGHT;

				gTileClips[ TILE_BGTREEBTM ].y = 256;
				gTileClips[ TILE_BGTREEBTM ].x = 64;
				gTileClips[ TILE_BGTREEBTM ].w = TILE_WIDTH;
				gTileClips[ TILE_BGTREEBTM ].h = TILE_HEIGHT;

				gTileClips[ TILE_BGTREETOP ].y = 256;
				gTileClips[ TILE_BGTREETOP ].x = 96;
				gTileClips[ TILE_BGTREETOP ].w = TILE_WIDTH;
				gTileClips[ TILE_BGTREETOP ].h = TILE_HEIGHT;

				gTileClips[ TILE_FENCE ].y = 256;
				gTileClips[ TILE_FENCE ].x = 128;
				gTileClips[ TILE_FENCE ].w = TILE_WIDTH;
				gTileClips[ TILE_FENCE ].h = TILE_HEIGHT;

				gTileClips[ TILE_SNWBUSH ].y = 256;
				gTileClips[ TILE_SNWBUSH ].x = 160;
				gTileClips[ TILE_SNWBUSH ].w = TILE_WIDTH;
				gTileClips[ TILE_SNWBUSH ].h = TILE_HEIGHT;

				gTileClips[ TILE_LAVABTM ].y = 256;
				gTileClips[ TILE_LAVABTM ].x = 192;
				gTileClips[ TILE_LAVABTM ].w = TILE_WIDTH;
				gTileClips[ TILE_LAVABTM ].h = TILE_HEIGHT;

				gTileClips[ TILE_WATERBTM ].y = 256;
				gTileClips[ TILE_WATERBTM ].x = 224;
				gTileClips[ TILE_WATERBTM ].w = TILE_WIDTH;
				gTileClips[ TILE_WATERBTM ].h = TILE_HEIGHT;

				gTileClips[ TILE_MUSHSTMTOP ].y = 256;
				gTileClips[ TILE_MUSHSTMTOP ].x = 256;
				gTileClips[ TILE_MUSHSTMTOP ].w = TILE_WIDTH;
				gTileClips[ TILE_MUSHSTMTOP ].h = TILE_HEIGHT;

				gTileClips[ TILE_BBMID ].y = 256;
				gTileClips[ TILE_BBMID ].x = 288;
				gTileClips[ TILE_BBMID ].w = TILE_WIDTH;
				gTileClips[ TILE_BBMID ].h = TILE_HEIGHT;

				gTileClips[ TILE_TREEGRNDL ].y = 288;
				gTileClips[ TILE_TREEGRNDL ].x = 0;
				gTileClips[ TILE_TREEGRNDL ].w = TILE_WIDTH;
				gTileClips[ TILE_TREEGRNDL ].h = TILE_HEIGHT;

				gTileClips[ TILE_TREEGRNDM ].y = 288;
				gTileClips[ TILE_TREEGRNDM ].x = 32;
				gTileClips[ TILE_TREEGRNDM ].w = TILE_WIDTH;
				gTileClips[ TILE_TREEGRNDM ].h = TILE_HEIGHT;

				gTileClips[ TILE_TREEGRNDR ].y = 288;
				gTileClips[ TILE_TREEGRNDR ].x = 64;
				gTileClips[ TILE_TREEGRNDR ].w = TILE_WIDTH;
				gTileClips[ TILE_TREEGRNDR ].h = TILE_HEIGHT;

				gTileClips[ TILE_BIGTRNK ].y = 288;
				gTileClips[ TILE_BIGTRNK ].x = 96;
				gTileClips[ TILE_BIGTRNK ].w = TILE_WIDTH;
				gTileClips[ TILE_BIGTRNK ].h = TILE_HEIGHT;

				gTileClips[ TILE_MUSHL ].y = 288;
				gTileClips[ TILE_MUSHL ].x = 128;
				gTileClips[ TILE_MUSHL ].w = TILE_WIDTH;
				gTileClips[ TILE_MUSHL ].h = TILE_HEIGHT;

				gTileClips[ TILE_MUSHM ].y = 288;
				gTileClips[ TILE_MUSHM ].x = 160;
				gTileClips[ TILE_MUSHM ].w = TILE_WIDTH;
				gTileClips[ TILE_MUSHM ].h = TILE_HEIGHT;

				gTileClips[ TILE_MUSHR ].y = 288;
				gTileClips[ TILE_MUSHR ].x = 192;
				gTileClips[ TILE_MUSHR ].w = TILE_WIDTH;
				gTileClips[ TILE_MUSHR ].h = TILE_HEIGHT;

				gTileClips[ TILE_SNWBOT ].y = 288;
				gTileClips[ TILE_SNWBOT ].x = 224;
				gTileClips[ TILE_SNWBOT ].w = TILE_WIDTH;
				gTileClips[ TILE_SNWBOT ].h = TILE_HEIGHT;

				gTileClips[ TILE_MUSSTMBOT ].y = 288;
				gTileClips[ TILE_MUSSTMBOT ].x = 256;
				gTileClips[ TILE_MUSSTMBOT ].w = TILE_WIDTH;
				gTileClips[ TILE_MUSSTMBOT ].h = TILE_HEIGHT;

				gTileClips[ TILE_BBBOT ].y = 288;
				gTileClips[ TILE_BBBOT ].x = 288;
				gTileClips[ TILE_BBBOT ].w = TILE_WIDTH;
				gTileClips[ TILE_BBBOT ].h = TILE_HEIGHT;


		}
	}

    //Close the file
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}

bool touchesFloor( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( (( tiles[ i ]->getAttribute() == GROUND_TYPE) || (tiles[i] ->getAttribute() == SPECIAL_TYPE)) && enteredPipe == false && enteredSilver==false) 
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
//		SDL_Rect floor = tiles[i]->getBox();
//                return floor.y;
		return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

bool touchesWall( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( (( tiles[ i ]->getAttribute() == GROUND_TYPE ) || ( tiles[ i ]->getAttribute() == SPECIAL_TYPE )) && enteredPipe == false && enteredSilver==false)
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}


bool touchesPipe( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getAttribute() == PIPE_ENTER) )
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}
bool touchesFlagpole( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getAttribute() == GOAL_TYPE ) )
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}


bool touchesAxe( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getAttribute() == AXE_TYPE ) )
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}


bool touchesSilver( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getAttribute() == SILVER_TYPE ) )
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}


bool touchesGoomba( SDL_Rect box, Goomba* goombas[], SDL_Rect& camera )
{
	

    //Go through the goombas
      int TOTAL_GOOMBAS = 20;
      for( int it = 0; it < TOTAL_GOOMBAS; it++ ) {
	//If the box hits the Coopas body
	if(!goombas[it]->getAlive()) continue;
	if( checkCollision( box, goombas[it]->getBodyBox() ) ) {
		return true;
	}


	//If the box hits the Goombas head
	else if( checkCollision( box, goombas[it]->getHeadBox() ) && !deathAni) {
		goombas[it]->kill(goombas[it]->getImageBox(), camera);
		return false;
	}
	
	//If the box hits the Coopas body

    }

   //If no goombas were touched
    return false;
}

bool touchesKoopa( SDL_Rect box, Koopa* koopas[], SDL_Rect& camera )
{
   int TOTAL_KOOPAS = 20;
    //Go through the coopas
   for( int it = 0; it < TOTAL_KOOPAS; it++ ) {
	//If the box hits the Koopas head
	//If the box hits the Koopas body
	if(!koopas[it]->getAlive()) continue;
	if( checkCollision( box, koopas[it]->getBodyBox() ) ) {
		return true;
	}

	//If the box hits the koopas head	
	else if( checkCollision( box, koopas[it]->getHeadBox() ) && !deathAni) {
		koopas[it]->kill(koopas[it]->getImageBox(), camera);
		return false;
	}
	
    }

    //If no Koopas were touched
    return false;
}



int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		int TOTAL_GOOMBAS = 20;
		int TOTAL_KOOPAS = 20;
		//The level tiles
		Tile* tileSet[ TOTAL_TILES ];

		//The level Enemies
		Goomba* goombas[ TOTAL_GOOMBAS ];
		Koopa* koopas[ TOTAL_KOOPAS ];
//		Shell* shells[ TOTAL_KOOPAS ];
		
		goombas[0] = new Goomba(335, 384);
		koopas[0] = new Koopa(385, 384);
		goombas[1] = new Goomba(635, 384);
		koopas[1] = new Koopa(680, 384);
		goombas[2] = new Goomba(980, 384);
		koopas[2] = new Koopa(1020, 384);
		goombas[3] = new Goomba(1280, 384);
		koopas[3] = new Koopa(1320, 384);
		goombas[4] = new Goomba(1535, 384);
		koopas[4] = new Koopa(1580, 384);
		goombas[5] = new Goomba(1890, 384);
		koopas[5] = new Koopa(1940, 384);
		goombas[6] = new Goomba(2135, 384);
		koopas[6] = new Koopa(2180, 384);
		goombas[7] = new Goomba(2435, 384);
		koopas[7] = new Koopa(2480, 384);
		goombas[8] = new Goomba(2735, 384);
		koopas[8] = new Koopa(2780, 384);
		goombas[9] = new Goomba(3035, 384);
		koopas[9] = new Koopa(3080, 384);
		goombas[10] = new Goomba(3335, 384);
		koopas[10] = new Koopa(3380, 384);
		goombas[11] = new Goomba(3635, 384);
		koopas[11] = new Koopa(3680, 384);
		goombas[12] = new Goomba(3935, 384);
		koopas[12] = new Koopa(3980, 384);
		goombas[13] = new Goomba(4235, 384);
		koopas[13] = new Koopa(4280, 384);
		goombas[14] = new Goomba(4535, 264);
		koopas[14] = new Koopa(4580, 296);
		goombas[15] = new Goomba(4835, 264);
		koopas[15] = new Koopa(4880, 264);
		goombas[16] = new Goomba(5135, 384);
		koopas[16] = new Koopa(5180, 384);
		goombas[17] = new Goomba(5435, 384);
		koopas[17] = new Koopa(5480, 384);
		goombas[18] = new Goomba(5720, 384);
		koopas[18] = new Koopa(5790, 296);
		goombas[19] = new Goomba(6200, 384);
		koopas[19] = new Koopa(6210, 384);


		bool walk = true;
		int count = 0;
		//Load media
		if( !loadMedia( tileSet ) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Dot dot;

			//Level camera
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
			SDL_RendererFlip marioFlip = SDL_FLIP_NONE;
			SDL_RendererFlip koopaFlip = SDL_FLIP_NONE;
			SDL_RendererFlip goombaFlip = SDL_FLIP_NONE;
			//While application is running
			while( !quit ) {
					//Handle events on queue
					while( SDL_PollEvent( &e ) != 0 )
					{
						//User requests quit
						if( e.type == SDL_QUIT )
						{
							quit = true;
						}
	
						//Handle input for the dot
						dot.handleEvent( e, tileSet );
					}
	
					//Move the dot
					dot.move( tileSet, goombas, koopas, camera );
					for(int i=0; i<TOTAL_KOOPAS; i++) {
						koopas[i]->move(tileSet, camera);
					}
					for(int i=0; i<TOTAL_GOOMBAS; i++) {
						goombas[i]->move(tileSet, camera);
					}
					dot.setCamera( camera );
	
					//Clear screen
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear( gRenderer );
	
					//Render level
					for( int i = 0; i < TOTAL_TILES; ++i )
					{
						tileSet[ i ]->render( camera );
					}
					for(int i=0; i<TOTAL_KOOPAS; i++) {
						koopas[i]->render(camera, walk, koopaFlip);
					}
					for(int i=0; i<TOTAL_GOOMBAS; i++) {
						goombas[i]->render(camera, walk, goombaFlip);
					}
					if(count%6>=3) walk = true;
					else walk = false;
	
					//Render dot
					dot.render( camera, marioFlip, walk );
	
					//Update screen
					SDL_RenderPresent( gRenderer );
					if(count >= 6) count = 0;
					else count++;
				}
				deathAni = false;
				levelChange = false;
			
		}
		
		//Free resources and close SDL
		close( tileSet );
	}

	return 0;
}
