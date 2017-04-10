#ifndef UPLIFTTERRAINGENERATOR2D_ASM
#define UPLIFTTERRAINGENERATOR2D_ASM

#include <cstdlib>
#include <vector>
#include "upliftTerrainGenerator2D.h"

extern "C" int fun( float* matrix, int rows, int cols, float* terrain);

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
		float* influencia = new float [nroPeaks * divisions];

		for (int i = 0; i < nroPeaks; ++i)
		{
			for (int j = 0; j < divisions; ++j)
			{
				float influence = peaksSize[i] - abs(peaksPos[i] - j);

				if(influence < 0) {
					influence = 0;
				}
				influencia[ j + divisions * i ] = influence;
			}
		}

		float terrainArray[divisions];

		fun(( float*)influencia, nroPeaks, divisions, terrainArray);

		for (int i = 0; i < divisions; ++i)
		{
			terrain.push_back(terrainArray[i]);
		}

		delete[] influencia;
	}
};

#endif