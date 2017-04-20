#include <vector>
#include "struct.h"

#define SIZE             50
using namespace std;

class CityModeller
{
private:
	vector<building*>* buildingStore;
	vector<road*>*     roadStore;
	vector<Vertex2>*  buildings;
	vector<singlegrid*>* cross;
	vector<singlegrid*>* buildingBase;
	vector<singlegrid*>* space;

private:
	void loadBuffer();
	
public:
	CityModeller();
	~CityModeller();
	void generateCityLayoutData(bool firsttime);
	void render();
	std::vector<Vertex2>* getBuffer();
	void clearBuffer();
	
public:
	bool grids[SIZE][SIZE];
	int w, h, l; //width length height of a building
	int wMax, hMax, lMax;
	int row1, row2, column1, column2;
    float lastT = 0;
};