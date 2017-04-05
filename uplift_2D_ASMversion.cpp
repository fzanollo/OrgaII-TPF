#include <iostream>
#include <cstdlib>
#include <vector>
#include <string.h>
#include "graficador.h"

extern "C" int fun( float* matrix, int rows, int cols);

using namespace std;

const string ERROR_MESSAGE = "ERROR: NOT ENOUGH PARAMETERS \nExpected order of parameters is:\n	divisions, nroPeaks, yMin, yMax, seed (optional) \nYou can also set it to be interactive with an 'i'\n";
/*
	divisions: cantidad de divisiones del espacio continuo (cantidad de x)
	nroPeaks: cantidad de picos
	yMin: altura minima de los picos
	yMax: altura maxima de los picos
	steepness: ?
*/
int divisions=10; //TODO?: hacer que no sean globales 
int nroPeaks = 4;
int yMin = 1;
int yMax = 10;
//? steepness= ?;

bool contains(vector<int> v, int e){
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		if(*it == e){
			return true;
		}
	}
	return false;
}

void getParameters(){
	cout << "Insert number of divisions: ";
	cin >> divisions;

	cout << "Insert number of peaks: ";
	cin >> nroPeaks;

	cout << "Insert minimum high (yMin): ";
	cin >> yMin;

	cout << "Insert maximum high (yMax): ";
	cin >> yMax;
}

vector<float> upliftTerrainGenerator(){
	//Terrain
	vector<float> terrain;

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
	//--------------------

	//AVG
	float influencia[nroPeaks][divisions];

	for (int i = 0; i < nroPeaks; ++i)
	{
		for (int j = 0; j < divisions; ++j)
		{
			float influence = peaksSize[i] - abs(peaksPos[i] - j);

			if(influence < 0) {
				influence = 0;
			}
			influencia[i][j] = influence;
			cout << " + " << influencia[i][j];
		}
		cout << endl;
	}
	cout<<endl;

	fun(( float*)influencia, nroPeaks, divisions);

	//change output of fun...ponele
	for (int i = 0; i < divisions; ++i)
	{
		terrain.push_back(influencia[0][i]);
		cout << " * " << influencia[0][i] ;
	}
	cout << endl;
	//--------------------

	//PRINT RESULTS
	cout << "Terrain: "<<endl;
	for (int i = 0; i < divisions; ++i)
	{
		cout << terrain[i] << ", ";
	}
	cout << endl;

	return terrain;
}

int main(int argc, char const *argv[])
{
	// initialize seed
	srand(time(NULL));

	if (argc <= 1){
		cout << ERROR_MESSAGE;
		return 0;
	}

	bool interactive = (strcmp(argv[1], "i") == 0);

	if (interactive){
		getParameters();
	} else{
		if(argc >= 5) {
			divisions = atoi(argv[1]);
			nroPeaks = atoi(argv[2]);
			yMin = atoi(argv[3]);
			yMax = atoi(argv[4]);

			//set custom seed
			if(argc >= 6){
				srand(atoi(argv[5]));
				cout << "seed is: " << atoi(argv[5]) << endl;
			}
		}
		else {
			cout << ERROR_MESSAGE;
		}
	}

	/* --------------------------- */

	vector<float> terrain = upliftTerrainGenerator();
	Graficador gr;
	gr.init();
	gr.graficar(terrain);
	
	return 0;
}