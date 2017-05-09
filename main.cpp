#include <iostream>
#include <cstdlib>
#include <vector>
#include <string.h>
#include "graficador2.h"
#include "upliftTerrainGenerator2D_C.h"
#include "upliftTerrainGenerator2D_ASM.h"

#include <time.h>

// #include <nonius/nonius.h++>
const string ERROR_MESSAGE = "ERROR: NOT ENOUGH PARAMETERS \nExpected order of parameters is:\n	divisions, nroPeaks, yMin, yMax, (seed (optional), 'v' if you want verbouse (only with custom seed)) \nYou can also set it to be interactive with an 'i'\n";

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
	bool debugging = false;

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

			if(argc >= 6){
				//set custom seed
				seed = atoi(argv[5]);

				if(argc >= 7){
					debugging = ((strcmp(argv[6], "v") == 0));
				}
			} else{
				seed = time(NULL);
			}
		}
		else {
			cout << ERROR_MESSAGE;
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
	vector<float> terrainC = cVersion2d.generateTerrain(divisions, nroPeaks, yMin, yMax, seed, debugging);
end = clock();
cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
cout << "cpu_time_used " << cpu_time_used << endl;
	
	//gr.graficar(terrainC);

	cout << endl;
	cout << "**********    2D ASM VERSION   **********" << endl;

start = clock();
	// CALCULO VERSION ASM
	vector<float> terrainASM = asmVersion2d.generateTerrain(divisions, nroPeaks, yMin, yMax, seed, debugging);
end = clock();
cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
cout << "cpu_time_used " << cpu_time_used << endl;

	gr.graficar(terrainASM);

	// nonius::configuration cfg;
	// //cfg.output_file = "example2.csv";
	// cfg.samples = 200;
 //    cfg.verbose = true;
 //    nonius::benchmark_registry benchmarks = {
 //        nonius::benchmark("version C", [=]{ UpliftTerrainGenerator2D_C cVersion2d; return cVersion2d.generateTerrain(divisions, nroPeaks, yMin, yMax, seed, debugging); }),
 //        nonius::benchmark("version ASM", [=]{ UpliftTerrainGenerator2D_ASM asmVersion2d; return asmVersion2d.generateTerrain(divisions, nroPeaks, yMin, yMax, seed, debugging); }),
 //    };

 //    nonius::go(cfg, benchmarks);
	
	return 0;
}