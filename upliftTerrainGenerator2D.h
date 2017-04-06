#ifndef UPLIFTTERRAINGENERATOR2D
#define UPLIFTTERRAINGENERATOR2D

class UpliftTerrainGenerator2D {
	public:
		vector<float> generateTerrain(int divisions, int nroPeaks, int yMin, int yMax, unsigned int seed){
			//initialize random
			srand(seed);

			int peaksPos[nroPeaks];
			int peaksSize[nroPeaks];
			vector<int> positions;

			// crea los picos en alguna posicion
			for (int i = 0; i < nroPeaks; ++i)
			{
				//always in different positions //TODO: add logic to choose positions not completly random
				int position = rand() % divisions;
				while(contains(positions, position)){
					position = rand() % divisions;
				}
				positions.push_back(position);

				int size = rand() % (yMax-yMin+1) + yMin; //in the range [yMin, yMax]

				peaksPos[i] = position; 
				peaksSize[i] = size; 
			}

			//FOR DEBUGGING //TODO mostrar solo si esta en modo verbose
			cout << "Peaks:" << endl;
			for (int i = 0; i < nroPeaks; ++i)
			{
				cout << "  position " << peaksPos[i] << " size " << peaksSize[i] << endl;
			}
			//--------------------

			//*********************

			doTheMath(divisions, nroPeaks, peaksPos, peaksSize);

			//*********************

			//FOR DEBUGGING: PRINT RESULTS
			cout << "Terrain: "<<endl;
			for (int i = 0; i < divisions; ++i)
			{
				cout << terrain[i] << ", ";
			}
			cout << endl;
			//--------------------

			return terrain;
		}

	protected:
		vector<float> terrain;

		virtual void doTheMath(int divisions, int nroPeaks, int peaksPos [], int peaksSize []){
			cout << "ESTO NO DEBERIA PASAR, estas en doTheMath de la clase base!!" << endl;
		};

		bool contains(vector<int> v, int e){
			for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
			{
				if(*it == e){
					return true;
				}
			}
			return false;
		}
};

#endif