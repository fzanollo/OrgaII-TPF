#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <vector>

using namespace std;

class Graficador {
	int scrollPixelQuantity = 10;

	int ancho;
	int escala;
	int width;
	int height;

	int viewWidth;

	int viewSize;

	SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Event event;

	public:
		Graficador() {
			scrollPixelQuantity = 10;

			ancho = 10;
			escala = 10;
			width = 1024;
			height = 768;

			viewWidth = floor(width / ancho) + 3;

			viewSize = viewWidth+2;
		}

		void init(){
		    SDL_Init(SDL_INIT_VIDEO);

		    window = SDL_CreateWindow("SDL_CreateTexture",
		                    SDL_WINDOWPOS_UNDEFINED,
		                    SDL_WINDOWPOS_UNDEFINED,
		                    1024, 768,
		                    SDL_WINDOW_RESIZABLE);

		    renderer = SDL_CreateRenderer(window, -1, 0);

		    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 768);
		}

		void graficar(vector<float> terrain){
		    
		    //-------------------------------
		    int from = 0;
		    renderFromToTerrain(renderer, texture, from, terrain);
		    //-------------------------------

		    bool quit = false;
		    //Event handler 
		    SDL_Event e;

		    //While application is running 
		    while( !quit ) {
				//Handle events on queue 
				while( SDL_PollEvent( &e ) != 0 ) { 

					//User requests quit 
					if( e.type == SDL_QUIT ) { 
						quit = true; 
					} 
					//User presses a key 
					else if( e.type == SDL_KEYUP ) { 
						switch( e.key.keysym.sym ) { 
							case SDLK_LEFT: 
								if(from > 0){
									from -= scrollPixelQuantity;
								    renderFromToTerrain(renderer, texture, from, terrain);
								}
								
								break; 
							case SDLK_RIGHT: 
								if(from < terrain.size() - viewWidth){
									from += scrollPixelQuantity;
		    						renderFromToTerrain(renderer, texture, from, terrain);
								}

								break; 
							default: 
								//cout << "solo se pueden usar izq y der" << endl;
								break; 
						} 
					} 
				}
			}

		    if (renderer) {
	            SDL_DestroyRenderer(renderer);
	        }

	        if (window) {
	            SDL_DestroyWindow(window);
	        }

	        SDL_Quit();
		}

	private:
		void renderFromToTerrain(SDL_Renderer *renderer, SDL_Texture *texture, int from, vector<float> terrain){	
			//Clean screen ---------------------
		    SDL_SetRenderTarget(renderer, texture);
		    SDL_SetRenderDrawColor(renderer, 0x80, 0xb3, 0xff, 0x00);
		    SDL_RenderClear(renderer);

		    //Do stuff -----------
			Sint16 puntosX[viewSize];
			Sint16 puntosY[viewSize];

		    puntosX[0] = 0;
		    puntosY[0] = height-1;

		    int terrainIndex = from;

		    for(int i=0; i < viewWidth; i++){
		    	puntosX[i+1] = i*ancho;

		    	if(terrainIndex < terrain.size()){
		    		puntosY[i+1] = height - terrain[terrainIndex]*escala;
		    		terrainIndex++;
		    	}else{
		    		puntosY[i+1] = height - 1;
		    	}
		    }

		    puntosX[viewSize-1] = width-1;	
		    puntosY[viewSize-1] = height-1;

		    //filledPolygonRGBA (SDL_Renderer *renderer, const Sint16 *vx, const Sint16 *vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		    filledPolygonRGBA (renderer, puntosX, puntosY, viewSize, 128, 0, 0, 255);

		    //Refresh screen -----------
		    SDL_SetRenderTarget(renderer, NULL);
		    SDL_RenderCopy(renderer, texture, NULL, NULL);
		    SDL_RenderPresent(renderer);
		}

};

#endif