//Paul Githens
//Graphics Test
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_height = 480;

int main( int argc, char* args[] ) {
	//The Window we'll be rendering to 
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		cout << "SDL could not initialize! SDL_error: " << SDL_GetError() << endl;
	}
	else {
		//Create Window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_height, SDL_WINDOW_SHOWN );
		if( window == NULL ) cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
		else {
			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );

			//Fill the surface white
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF) );
			
			//Update the surface
			SDL_UpdateWindowSurface( window );

			//Wait two seconds
			SDL_Delay( 2000 );
		}
	}
	//Destroy window
	SDL_DestroyWindow( window );

	// Quit SDL subsystems
	SDL_Quit();

	return 0;

}

