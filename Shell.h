#ifndef SHELL_H
#define SHELL_H

#include "enemies.h"

class Shell : public enemies {
	public:
		Shell(int = 0, int = 0);
		virtual void render( SDL_Rect& camera );
};

Shell::Shell (int startX, int startY) : enemies (startX, startY, false) {}

void Coopa::render( SDL_Rect& camera ) {
	if( getAlive() ) {
		SDL_Rect image = getImageBox();
		gCoopaTexture.render( image.x - camera.x, image.y - camera.y );
	}
}

#endif
