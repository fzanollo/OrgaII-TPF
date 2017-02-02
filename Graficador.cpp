//Include SDL functions and datatypes
#include "SDL.h"
#include <vector>
#include <iostream>

using namespace std;
//TODO agregar constructor con parametros, tiene que recibir el vector de valores
class Graficador {
		int posicionEjeX, posicionEjeY, nroParticionesDeX;
		SDL_Renderer* renderer;
		SDL_Window* window;
		std::vector<int> valores;
		SDL_bool done;
	public:
		Graficador() {
			posicionEjeX = 0;
			posicionEjeY = 700;
			nroParticionesDeX = 16;
			window = NULL;
			renderer = NULL;
			for (int i = 0; i < 100; ++i)
		    {
		        int v2 = rand() % 10 + 0; 
		         valores.push_back(v2);
		    }
		}

		void init() {//TODO definir mejor que hace
			SDL_Init(SDL_INIT_VIDEO);
			SDL_CreateWindowAndRenderer(1024, 768, 0, &window, &renderer);
			done = SDL_FALSE;
		}

		void graficar() {
			
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
			        int v1 = valores.at(i);
			        int v2 = valores.at(i+1);
			        cout << v2 << endl;
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

 int main(int argc, char const *argv[])
{
	/* code */
	Graficador gr;
	gr.init();
	gr.graficar();

	return 0;
}
