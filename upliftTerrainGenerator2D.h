#ifndef UPLIFTTERRAINGENERATOR2D
#define UPLIFTTERRAINGENERATOR2D

#include <iostream>

class UpliftTerrainGenerator2D {
	public:
		vector<float> generateTerrain(int divisions, int nroPeaks, int yMin, int yMax, unsigned int seed, bool debugging){
			//initialize random
			srand(seed);

			int peaksPos[nroPeaks];
			int peaksSize[nroPeaks];
			vector<int> positions;

			for (int i = 0; i < divisions; ++i)
			{
				positions.push_back(i);
			}

			// crea los picos en alguna posicion
			for (int i = 0; i < nroPeaks; ++i)
			{
				int randElem = rand() % positions.size();
				int position = positions[randElem];

				//siempre en posiciones distintas (borra la pos usada)
				positions.erase(positions.begin() + randElem);

				int size = rand() % (yMax-yMin+1) + yMin; //in the range [yMin, yMax]

				peaksPos[i] = position; 
				peaksSize[i] = size; 
			}

			//FOR DEBUGGING
			if(debugging){
				cout << "Peaks:" << endl;
				for (int i = 0; i < nroPeaks; ++i)
				{
					cout << "  position " << peaksPos[i] << " size " << peaksSize[i] << endl;
				}
			}
			//--------------------

			//*********************

			doTheMath(divisions, nroPeaks, peaksPos, peaksSize);

			//*********************

			//FOR DEBUGGING: PRINT RESULTS
			if(debugging){
				cout << "Terrain: "<<endl;
				for (int i = 0; i < divisions; ++i)
				{
					cout << terrain[i] << ", ";
				}
				cout << endl;
			}
			//--------------------

			return terrain;
		}

	protected:
		vector<float> terrain;

		virtual void doTheMath(int divisions, int nroPeaks, int peaksPos [], int peaksSize []){
			cout << "ESTO NO DEBERIA PASAR, estas en doTheMath de la clase base!!" << endl;
		};

		bool contains(vector<int> v, int e){
			for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
			{
				if(*it == e){
					return true;
				}
			}
			return false;
		}
};

#endif