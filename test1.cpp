#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char const *argv[])
{
	int size=10;
	int nroPeaks = 2;

	//Terrain
	double terrain[size];

	for (int i = 0; i < size; ++i)
	{
		terrain[i] = 0;
	}

	//Peaks
	// cout << "Peaks: ";
	// for (int i = 0; i < nroPeaks; ++i)
	// {
	// 	int position = rand() % size;
	// 	cout << position << ", ";
	// 	terrain[position] = 2;
	// }
	// cout << endl;

	int peaksPos[nroPeaks] = {2, 6};
	int peaksSize[nroPeaks] = {2, 4};

	//AVG
	for (int i = 0; i < size; ++i)
	{
		double sum = 0;
		int cant = 0;

		for (int p = 0; p < nroPeaks; ++p)
		{
			double influence = peaksSize[p] - abs(peaksPos[p] - i);

			if (influence > 0)
			{
				cant++;
				sum += influence;
			}
		}

		/* el tema era entre que hacer el avg, aca lo hacemos entre:
			si no hay influencia de nadie => el valor es 0
			si solo hay influencia de una montaña => 2 (piso y montaña)
			cc (influencia de mas de una montaña) => cant de montañas
		 */
		if (cant==0) 
		{
			terrain[i] = 0;
		}
		else{
			terrain[i] = (cant==1) ? sum / 2 : sum / cant;
		}
	}

	//PRINT RESULTS
	cout << "Terrain: "<<endl;
	for (int i = 0; i < size; ++i)
	{
		cout << terrain[i] << ", ";
	}
	cout << endl;

	return 0;
}