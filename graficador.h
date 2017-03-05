#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include "SDL.h"
#include <vector>

using namespace std;
//TODO agregar constructor con parametros, tiene que recibir el vector de valores
class Graficador {
		int posicionEjeX, posicionEjeY, nroParticionesDeX;
		SDL_Renderer* renderer;
		SDL_Window* window;
		std::vector<double> valores;
		SDL_bool done;
	public:
		Graficador() {
			posicionEjeX = 0;
			posicionEjeY = 700;
			window = NULL;
			renderer = NULL;
		}

		void init() {//TODO definir mejor que hace
			SDL_Init(SDL_INIT_VIDEO);
			SDL_CreateWindowAndRenderer(1024, 768, 0, &window, &renderer);
			done = SDL_FALSE;
		}

		void graficar(vector<float> v) {
			valores = v;
			nroParticionesDeX = v.size();
			
			int pixelesPorParticion= (1024 / nroParticionesDeX);
			int multValorY = 40;
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

                SDL_RenderDrawLine(renderer, posicionEjeX, posicionEjeY, posicionEjeX+1024, posicionEjeY);
                SDL_RenderDrawLine(renderer, 0, 400, 1024, 400);
//TODO pasar a funcion------------------------------
			    for (int i = 0; i < valores.size()-1; ++i)
			    {
			        float v1 = valores.at(i);
			        float v2 = valores.at(i+1);
			        SDL_RenderDrawLine(renderer, 
			            posicionEjeX+i*pixelesPorParticion,                    posicionEjeY, 
			            posicionEjeX+i*pixelesPorParticion,                    posicionEjeY-(v1*multValorY));

			        SDL_RenderDrawLine(renderer, 
			            posicionEjeX+(i*pixelesPorParticion),       posicionEjeY-(v1*multValorY), 
			            posicionEjeX+((i+1)*pixelesPorParticion),   posicionEjeY-(v2*multValorY));
			    }
//------------------------------
                SDL_RenderPresent(renderer);
			while (!done) 
            {

                while (SDL_PollEvent(&event)) 
                {
                    if (event.type == SDL_QUIT) 
                    {
                        done = SDL_TRUE;
                    }
                }
            }
	        if (renderer) 
	        {
	            SDL_DestroyRenderer(renderer);
	        }
	        if (window) 
	        {
	            SDL_DestroyWindow(window);
	        }
	        SDL_Quit();
    	}
    
		
};

#endif