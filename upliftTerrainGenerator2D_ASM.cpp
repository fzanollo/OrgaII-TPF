#include "upliftTerrainGenerator2D.h"

extern "C" int fun(int* peaksPos, int* peaksSize, int nroPeaks, int divisions, float* terrainArray, int ruggedness);

/*
	divisions: cantidad de divisiones del espacio continuo (cantidad de x)
	nroPeaks: cantidad de picos
	yMin: altura minima de los picos
	yMax: altura maxima de los picos
	ruggedness: escarpado del terreno
*/
void UpliftTerrainGenerator2D_ASM::doTheMath(int divisions, int nroPeaks, int peaksPos [], int peaksSize [], int ruggedness){

	float terrainArray[divisions];


	fun(peaksPos, peaksSize, nroPeaks, divisions, terrainArray, ruggedness);

	for (int i = 0; i < divisions; ++i)
	{
		terrain.push_back(terrainArray[i]);
	}
	
}