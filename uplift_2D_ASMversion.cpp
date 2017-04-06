#ifndef UPLIFTTERRAINGENERATOR2D_ASM
#define UPLIFTTERRAINGENERATOR2D_ASM

#include <iostream>
#include <cstdlib>
#include <vector>

extern "C" int fun( float* matrix, int rows, int cols);

using namespace std;

/*
	divisions: cantidad de divisiones del espacio continuo (cantidad de x)
	nroPeaks: cantidad de picos
	yMin: altura minima de los picos
	yMax: altura maxima de los picos
	steepness: ?
*/
class UpliftTerrainGenerator2D_ASM {
	vector<float> generateTerrain(int divisions, int nroPeaks, int yMin, int yMax){ //steepness: ?
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

		//TODO: change output of fun...ponele
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