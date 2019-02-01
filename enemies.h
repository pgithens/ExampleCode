class enemies {
	public:
		// dimensions
		static const int EN_WIDTH = 32;
		static const int EN_HEIGHT = 32;
		static const int EN_HEAD_HEIGHT = 5;
		static const int EN_BODY_HEIGHT = 32-EN_HEAD_HEIGHT;

		// Maximum axis velocity of the enemy
		static const int EN_VEL = 10;

		//Initializes the variables
		enemies(int startX, int startY, bool startAlive);

		//Update Position and liveness
		update(int newX, int newY, bool newALive);

		//Moves the dot and check collision against tiles
		void move( Tile *tiles[] );

		//Centers the camera over the enemy
		void setCamera( SDL_Rect& camera );

		//Shows the enemy on the screen
		virtual void render( SDL_Rect& camera ) = 0;

		//Enemy is Killed
		virtual void kill( SDL_Rect image, SDL_Rect& camera, Shell *shells[] ) = 0;

		//Get Head Collision Box
		SDL_Rect getHeadBox();

		//Get Body Collision Box
		SDL_Rect getBodyBox();

		//Get Image Box
		SDL_Rect getImageBox();
	
		//Living?
		bool getAlive();

	private:
		//Is it alive?		
		bool alive;

		//Collision box of the enemy
		SDL_Rect head;
		SDL_Rect body;
		SDL_Rect image;
	
		//The velocity of the enemy
		int mVelX, mVelY;
};

enemies::enemies(int startX, int startY, bool startAlive) {
	alive = startAlive;

	head.x = startX;
	head.y = startY;
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
	mVelX = -EN_VEL;
	mVelY = 0;
}

enemies::update(int newX, int newY, bool newAlive) {
	alive = newAlive;

	head.x = newX;
	head.y = newY;

	body.x = newX;
	body.y = newY + EN_HEAD_HEIGHT;

	image.x = newX;
	image.y = newY;
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

void enemies::move( Tile *tiles[] ) {
	if(alive) {
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
	
		//If the enemy went to far down
		if( ( body.y + EN_BODY_HEIGHT > LEVEL_HEIGHT ) ) {
			kill();
		}
	
		//If the dot went too far up or down or touched a wall
		if( ( head.y < 0 ) || touchesWall( head, tiles ) ) {      //( mBox.y + EN_HEIGHT > LEVEL_HEIGHT ) || touchesWall( mBox, tiles ) ) {
			head.y -=mVelY;
			body.y -=mVelY;
			image.y -=mVelY;
		}
	}
}
	
void enemies::setCamera( SDL_Rect& camera ) {
	//Center the camera over the dot
	camera.x = ( head.x + EN_WIDTH / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( head.y + EN_Height / 2 ) - SCREEN_WIDTH / 2;

	//Keep the camera in bounds
	if(camera.x < 0 )
		camera.x = 0;
	if(camera.y < 0 ) 
		camear.y = 0;
	if( camera.x > LEVEL_WIDTH - camera.w ) 
		camera.x = LEVEL_WIDTH - camera.w;
	if(camera.y > LEVEL_HEIGHT - camera.h)
		camera.y = LEVEL_HEIGHT - camera.h;

}


void enemeis::render( SDL_Rect& camera ) {
	// show the enemy
	if(alive) gDotTexture.render( image.x - camera.x, image.y - camera.y );
}

void enemies::kill( SDL_Rect image, SDL_Rect& camera ) {
	alive = false;
	gPuffTexture.render( image.x - camera.x, image.y - camera.y );
}



