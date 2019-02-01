#ifndef GOOMBA_H
#define GOOMBA_H

#include "enemies.h"

class Goomba : public enemies {
	public:
		Goomba(int = 0, int = 0);
		virtual void render( SDL_Rect& camera );
};

Goomba::Goomba (int startX, int startY) : enemies (startX, startY, true) {}

void Goomba::render( SDL_Rect& camera ) {
	if( getAlive() ) {
		SDL_Rect image = getImageBox();
		gGoombaTexture.render( image.x - camera.x, image.y - camera.y );
	}
}

#endif
