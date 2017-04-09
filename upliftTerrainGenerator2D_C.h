#ifndef UPLIFTTERRAINGENERATOR2D_C
#define UPLIFTTERRAINGENERATOR2D_C

#include <iostream>
#include <cstdlib>
#include <vector>
#include "upliftTerrainGenerator2D.h"

using namespace std;

/*
	divisions: cantidad de divisiones del espacio continuo (cantidad de x)
	nroPeaks: cantidad de picos
	yMin: altura minima de los picos
	yMax: altura maxima de los picos
	steepness: ?
*/
class UpliftTerrainGenerator2D_C: public UpliftTerrainGenerator2D {
	void doTheMath(int divisions, int nroPeaks, int peaksPos [], int peaksSize []){
		//DEBUG ++++++++++++++++++++++++++++++++
		for (int a = 0; a < nroPeaks; ++a)
		{
			for (int b = 0; b < divisions; ++b)
			{
				float influence = peaksSize[a] - abs(peaksPos[a] - b);

				if(influence < 0) {
					influence = 0;
				}
				cout << " + " << influence;
			}
			cout << endl;
		}
		cout<<endl;
		//+++++++++++++++++++++++++++++++++++++

		for (int i = 0; i < divisions; ++i)
		{
			float influenceSum = 0;
			int peaksSum = 0;

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
					peaksSum++;
					influenceSum += influence;
				}
			}

			/* el tema era entre que hacer el avg, aca lo hacemos entre:
				si no hay influencia de nadie => el valor es 0
				si solo hay influencia de un pico => 2 (piso y pico)
				cc (influencia de mas de un pico) => peaksSum de picos
			 */
			if (peaksSum==0) 
			{
				terrain.push_back(0);
			}
			else{
				terrain.push_back((peaksSum==1) ? influenceSum / 2 : influenceSum / peaksSum);
			}
		}
	}
};
#endif