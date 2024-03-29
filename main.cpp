#include <iostream>
#include <cstdlib>
#include <vector>
#include <string.h>
#include "graficador2.h"
#include "upliftTerrainGenerator2D.h"

#include <time.h>

const string ERROR_MESSAGE = "ERROR: NOT ENOUGH PARAMETERS \nExpected order of parameters is:\n	divisions, nroPeaks, yMin, yMax, ruggedness, (seed (optional), 'v' if you want verbouse (only with custom seed)) \nYou can also set it to be interactive with an 'i'\n";

using namespace std;

int main(int argc, char const *argv[])
{
	// initialize seed and default variables
	unsigned int seed = 200;
	int divisions=10;
	int nroPeaks = 4;
	int yMin = 1;
	int yMax = 10;
	int ruggedness= 1;
	bool debugging = false;

	if (argc <= 1){
		cout << ERROR_MESSAGE;
		return 1;
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

		cout << "Insert ruggedness: ";
		cin >> ruggedness;
	} else{
		if(argc >= 6) {
			divisions = atoi(argv[1]);
			nroPeaks = atoi(argv[2]);
			yMin = atoi(argv[3]);
			yMax = atoi(argv[4]);
			ruggedness = atoi(argv[5]);

			cout<< "ruggedness = " << ruggedness << endl;

			if(argc >= 7){
				//set custom seed
				seed = atoi(argv[6]);

				if(argc >= 8){
					debugging = ((strcmp(argv[7], "v") == 0));
				}
			} else{
				seed = time(NULL);
			}
		}
		else {
			cout << ERROR_MESSAGE;
			return 1;
		}
	}

	/* --------------------------- */

	UpliftTerrainGenerator2D_ASM asmVersion2d;
	UpliftTerrainGenerator2D_C cVersion2d;
	Graficador gr;

	clock_t start, end;
    double cpu_time_used;
	
	cout << "seed is: " << seed << endl;
	cout << endl;
	cout << "**********    2D C VERSION   **********" << endl;

start = clock();
	// CALCULO VERSION C
	vector<float> terrain = cVersion2d.generateTerrain(divisions, nroPeaks, yMin, yMax, ruggedness, seed, debugging);
end = clock();
cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
cout << "cpu_time_used " << cpu_time_used << endl;

	gr.init();
	gr.graficar(terrain);

	cout << endl;
	cout << "**********    2D ASM VERSION   **********" << endl;

start = clock();
	// CALCULO VERSION ASM
	terrain = asmVersion2d.generateTerrain(divisions, nroPeaks, yMin, yMax, ruggedness, seed, debugging);
end = clock();
cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
cout << "cpu_time_used " << cpu_time_used << endl;

	gr.init();
	gr.graficar(terrain);
	
	return 0;
}