#include <iostream>
#include <cstdlib>
#include <vector>
#include <string.h>
#include "graficador.h"
#include "upliftTerrainGenerator2D_C.h"
#include "upliftTerrainGenerator2D_ASM.h"

const string ERROR_MESSAGE = "ERROR: NOT ENOUGH PARAMETERS \nExpected order of parameters is:\n	divisions, nroPeaks, yMin, yMax, seed (optional) \nYou can also set it to be interactive with an 'i'\n";

using namespace std;

int main(int argc, char const *argv[])
{
	// initialize seed and default variables
	unsigned int seed = 200;
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

	UpliftTerrainGenerator2D_ASM asmVersion2d;
	UpliftTerrainGenerator2D_C cVersion2d;
	
	cout << endl;

	cout << "**********    2D C VERSION   **********" << endl;
	vector<float> terrain = cVersion2d.generateTerrain(divisions, nroPeaks, yMin, yMax, seed);
	Graficador gr;
	gr.init();
	gr.graficar(terrain);

	cout << endl;

	cout << "**********    2D ASM VERSION   **********" << endl;
	terrain = asmVersion2d.generateTerrain(divisions, nroPeaks, yMin, yMax, seed);
	gr.init();
	gr.graficar(terrain);
	
	return 0;
}