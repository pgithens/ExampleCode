#ifndef KOOPA_H
#define KOOPA_H

#include "enemies.h"

class Koopa : public enemies {
	public:
		Koopa(int = 0, int = 0);
		virtual void render( SDL_Rect& camera );
		virtual void render( SDL_Rect image, SDL_Rect& camera, Shell* shells[]);
};

Koopa::Koopa (int startX, int startY) : enemies (startX, startY, true) {}

void Koopa::render( SDL_Rect& camera ) {
	if( getAlive() ) {
		SDL_Rect image = getImageBox();
		gCoopaTexture.render( image.x - camera.x, image.y - camera.y );
	}
}

void Koopa::kill(SDL_Rect image, SDL_Rect& camera, Shell* shells[]) {
	dead();
	bool found = false;
	int i=0;
	while(!found && i<TOTAL_KOOPAS) {
		if (!shells[i].getAlive()) {
			found = true;
			shells[i].update(image.x, image.y);
		}
		else i++;
	}
	gPoofTexture.render( image.x - camera.x, image.y - camera.y );
}

#endif
