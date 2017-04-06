#ifndef UPLIFTTERRAINGENERATOR2D
#define UPLIFTTERRAINGENERATOR2D

class UpliftTerrainGenerator {
	protected:
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