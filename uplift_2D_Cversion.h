#ifndef UPLIFTTERRAINGENERATOR2D_C
#define UPLIFTTERRAINGENERATOR2D_C

#include <iostream>
#include <cstdlib>
#include <vector>
#include "upliftTerrainGenerator.h"

using namespace std;

/*
	divisions: cantidad de divisiones del espacio continuo (cantidad de x)
	nroPeaks: cantidad de picos
	yMin: altura minima de los picos
	yMax: altura maxima de los picos
	steepness: ?
*/
class UpliftTerrainGenerator2D_C: public UpliftTerrainGenerator {
	public:
		vector<float> generateTerrain(int divisions, int nroPeaks, int yMin, int yMax){ //steepness: ?
			//Terrain
			vector<float> terrain;

			//They all start in 0
			for (int i = 0; i < divisions; ++i)
			{
				terrain.push_back(0);
			}

			// EXAMPLE
			// int peaksPos[nroPeaks] = {2, 6};
			// int peaksSize[nroPeaks] = {2, 4};

			int peaksPos[nroPeaks];
			int peaksSize[nroPeaks];

			vector<int> positions;

			for (int i = 0; i < nroPeaks; ++i)
			{
				//always in different positions //TODO: add logic to choose positions not completly random
				int position = rand() % divisions;
				while(contains(positions, position)){
					position = rand() % divisions;
				}
				positions.push_back(position);

				int size = rand() % (yMax-yMin+1) + yMin; //in the range [yMin, yMax]

				peaksPos[i] = position; 
				peaksSize[i] = size; 
			}

			//FOR DEBUGGING //TODO mostrar solo si esta en modo verbose
			cout << "Peaks:" << endl;
			for (int i = 0; i < nroPeaks; ++i)
			{
				cout << "  position " << peaksPos[i] << " size " << peaksSize[i] << endl;
			}

			//AVG
			for (int i = 0; i < divisions; ++i)
			{
				float sum = 0;
				int cant = 0;

				for (int p = 0; p < nroPeaks; ++p)
				{
					float influence;
					if (peaksSize[p] > abs(peaksPos[p] - i)){
						influence = peaksSize[p] - abs(peaksPos[p] - i);
					} else {
						influence = 0;
					}

					if (influence > 0)
					{
						cant++;
						sum += influence;
					}
				}

				/* el tema era entre que hacer el avg, aca lo hacemos entre:
					si no hay influencia de nadie => el valor es 0
					si solo hay influencia de un pico => 2 (piso y pico)
					cc (influencia de mas de un pico) => cant de picos
				 */
				if (cant==0) 
				{
					terrain[i] = 0;
				}
				else{
					terrain[i] = (cant==1) ? sum / 2 : sum / cant;
				}
			}

			//PRINT RESULTS
			cout << "Terrain: "<<endl;
			for (int i = 0; i < divisions; ++i)
			{
				cout << terrain[i] << ", ";
			}
			cout << endl;

			return terrain;
		}

	private:
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