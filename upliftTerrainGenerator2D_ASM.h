#ifndef UPLIFTTERRAINGENERATOR2D_ASM
#define UPLIFTTERRAINGENERATOR2D_ASM

#include <iostream>
#include <cstdlib>
#include <vector>
#include "upliftTerrainGenerator2D.h"

extern "C" int fun( float* matrix, int rows, int cols);

using namespace std;

/*
	divisions: cantidad de divisiones del espacio continuo (cantidad de x)
	nroPeaks: cantidad de picos
	yMin: altura minima de los picos
	yMax: altura maxima de los picos
	steepness: ?
*/
class UpliftTerrainGenerator2D_ASM: public UpliftTerrainGenerator2D {
	void doTheMath(int divisions, int nroPeaks, int peaksPos [], int peaksSize []){
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
	}
};

#endif