#include "upliftTerrainGenerator2D.h"

using namespace std;

vector<float> UpliftTerrainGenerator2D::generateTerrain(int divisions, int nroPeaks, int yMin, int yMax, int ruggedness, unsigned int seed, bool debugging){
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

	doTheMath(divisions, nroPeaks, peaksPos, peaksSize, ruggedness);

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