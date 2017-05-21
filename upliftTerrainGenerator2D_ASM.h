#ifndef UPLIFTTERRAINGENERATOR2D_ASM
#define UPLIFTTERRAINGENERATOR2D_ASM

#include <cstdlib>
#include <vector>
#include "upliftTerrainGenerator2D.h"

extern "C" int fun(int* peaksPos, int* peaksSize, int nroPeaks, int divisions, float* terrainArray, int ruggedness);

using namespace std;

/*
	divisions: cantidad de divisiones del espacio continuo (cantidad de x)
	nroPeaks: cantidad de picos
	yMin: altura minima de los picos
	yMax: altura maxima de los picos
	steepness: ?
*/
class UpliftTerrainGenerator2D_ASM: public UpliftTerrainGenerator2D {
	void doTheMath(int divisions, int nroPeaks, int peaksPos [], int peaksSize [], int ruggedness){

		float *terrainArray = new float[divisions] ;
 

		fun(peaksPos, peaksSize, nroPeaks, divisions, terrainArray, ruggedness);

		for (int i = 0; i < divisions; ++i)
		{
			terrain.push_back(terrainArray[i]);
		}
		
		delete terrainArray;
	}
};

#endif