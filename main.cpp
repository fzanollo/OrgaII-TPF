#include <iostream>
#include <cstdlib>
#include <vector>
#include <string.h>
#include "graficador.h"
#include "uplift_2D_Cversion.h"
#include "uplift_2D_ASMversion.h"

const string ERROR_MESSAGE = "ERROR: NOT ENOUGH PARAMETERS \nExpected order of parameters is:\n	divisions, nroPeaks, yMin, yMax, seed (optional) \nYou can also set it to be interactive with an 'i'\n";

using namespace std;

int main(int argc, char const *argv[])
{
	// initialize seed and default variables
	srand(time(NULL));
	int divisions=10;
	int nroPeaks = 4;
	int yMin = 1;
	int yMax = 10;
	//? steepness= ?;

	if (argc <= 1){
		cout << ERROR_MESSAGE;
		return 0;
	}

	bool interactive = (strcmp(argv[1], "i") == 0);

	if (interactive){
		cout << "Insert number of divisions: ";
		cin >> divisions;

		cout << "Insert number of peaks: ";
		cin >> nroPeaks;

		cout << "Insert minimum high (yMin): ";
		cin >> yMin;

		cout << "Insert maximum high (yMax): ";
		cin >> yMax;
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

	UpliftTerrainGenerator2D_ASM asmVersion;

	vector<float> terrain = asmVersion.generateTerrain(divisions, nroPeaks, yMin, yMax);
	Graficador gr;
	gr.init();
	gr.graficar(terrain);
	
	return 0;
}