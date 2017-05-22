#ifndef UPLIFTTERRAINGENERATOR2D
#define UPLIFTTERRAINGENERATOR2D

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

/*
	divisions: cantidad de divisiones del espacio continuo (cantidad de x)
	nroPeaks: cantidad de picos
	yMin: altura minima de los picos
	yMax: altura maxima de los picos
	ruggedness: escarpado del terreno
*/

class UpliftTerrainGenerator2D {
	public:
		vector<float> generateTerrain(int divisions, int nroPeaks, int yMin, int yMax, int ruggedness, unsigned int seed, bool debugging);
	protected:
		vector<float> terrain;

		virtual void doTheMath(int divisions, int nroPeaks, int peaksPos [], int peaksSize [], int ruggedness){
			cout << "ESTO NO DEBERIA PASAR, estas en doTheMath de la clase base!!" << endl;
		}
};

class UpliftTerrainGenerator2D_C: public UpliftTerrainGenerator2D {
	protected:
		void doTheMath(int divisions, int nroPeaks, int peaksPos [], int peaksSize [], int ruggedness);
};

class UpliftTerrainGenerator2D_ASM: public UpliftTerrainGenerator2D {
	protected:
	void doTheMath(int divisions, int nroPeaks, int peaksPos [], int peaksSize [], int ruggedness);
};

#endif