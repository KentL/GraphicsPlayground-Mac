#include "CityModeller.h"
#include <time.h>
#include <algorithm>
#include <stdlib.h> 

#define BEGININGGRID	 0
#define ROADLENGTH		 50
#define MAXLENGTH		6
#define MAXWIDTH		6
#define UNITLENGHT 50
#define ZERO     0
#define ONETIME  0.33333333
#define TWICE    0.66666666
#define TRIPLE   1
#define SPACE    10
#define ROADHEIGHT 0
#define TEXGRIDSPERROW 8
#define TEXGRIDSPERCOLUMN 5
#define TEXSAMPLEGAP   0.05
#define MAX_LENGTH_IN_GRID 3
#define MAX_WIDTH_IN_GRID 3


CityModeller::CityModeller()
{
	buildingStore = new vector < building* >();
	roadStore = new vector<road*>();
	buildings = new vector<Vertex2>();
	cross = new vector<singlegrid*>();
	buildingBase = new vector<singlegrid*>();
	space = new vector<singlegrid*>();
	srand((unsigned)time(NULL));
}

CityModeller::~CityModeller()
{
	clearBuffer();
}

void CityModeller::generateCityLayoutData(bool firsttime)
{
	if (!firsttime)
	{
		//clear store buffer
		clearBuffer();
	}

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			grids[i][j] = true;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//gengerate roads'data
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	row1 = rand() % SIZE;
	row2 = rand() % SIZE;
	while (row1 == row2)
	{
		row2 = rand() % SIZE;
	}
	column1 = 0;// rand() % SIZE;
	column2 = rand() % SIZE;
	while (column1 == column2)
	{
		column2 = rand() % SIZE;
	}
	int closercolumn = std::min(column1, column2);
	int furthercolumn = std::max(column1, column2);
	int closerrow = std::min(row1, row2);
	int furtherrow = std::max(row1, row2);
	// road fragements
	road* road_row1_1 = new road({ row1, BEGININGGRID, row1, closercolumn - 1 });
	road* road_row1_2 = new road({ row1, closercolumn + 1, row1, furthercolumn - 1 });
	road* road_row1_3 = new road({ row1, furthercolumn + 1, row1, ROADLENGTH });

	road* road_row2_1 = new road({ row2, BEGININGGRID, row2, closercolumn - 1 });
	road* road_row2_2 = new road({ row2, closercolumn + 1, row2, furthercolumn - 1 });
	road* road_row2_3 = new road({ row2, furthercolumn + 1, row2, ROADLENGTH });

	road* road_column1_1 = new road({ BEGININGGRID, column1, closerrow - 1, column1 });
	road* road_column1_2 = new road({ closerrow + 1, column1, furtherrow - 1, column1 });
	road* road_column1_3 = new road({ furtherrow + 1, column1, ROADLENGTH, column1 });

	road* road_column2_1 = new road({ BEGININGGRID, column2, closerrow - 1, column2 });
	road* road_column2_2 = new road({ closerrow + 1, column2, furtherrow - 1, column2 });
	road* road_column2_3 = new road({ furtherrow + 1, column2, ROADLENGTH, column2 });
	// crossing 
	singlegrid* cross1 = new singlegrid({ row1, column1 });
	singlegrid* cross2 = new singlegrid({ row1, column2 });
	singlegrid* cross3 = new singlegrid({ row2, column2 });
	singlegrid* cross4 = new singlegrid({ row2, column1 });

	roadStore->push_back(road_row1_1);
	roadStore->push_back(road_row1_2);
	roadStore->push_back(road_row1_3);
	roadStore->push_back(road_row2_1);
	roadStore->push_back(road_row2_2);
	roadStore->push_back(road_row2_3);
	roadStore->push_back(road_column1_1);
	roadStore->push_back(road_column1_2);
	roadStore->push_back(road_column1_3);
	roadStore->push_back(road_column2_1);
	roadStore->push_back(road_column2_2);
	roadStore->push_back(road_column2_3);

	cross->push_back(cross1);
	cross->push_back(cross2);
	cross->push_back(cross3);
	cross->push_back(cross4);



	for (int i = 0; i < SIZE; i++)
	{
		grids[row1][i] = false;
		grids[row2][i] = false;
		grids[i][column1] = false;
		grids[i][column2] = false;
	}
	/*
	for (int a = 0; a < SIZE; a++)
	{
		for (int b = 0; b < SIZE; b++)
		{
			printf("%d  ", grids[a][b]);
		}
		printf("\n");
	}

	printf("\n\n\n");
	*/
	//space grids
	for (int ii = 0; ii < SIZE; ii++)
	{
		for (int jj = 0; jj <SIZE; jj++)
		{
			if (grids[ii][jj])
			{
				space->push_back(new singlegrid({ ii, jj }));
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//generate buildings'data
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (grids[i][j])
			{
				{	//buildings'length and width are counted from the selected grid to right(column+1) and to down(row+1)


					//get the largest extension scope(limited by the road)
					if (column1 < j)
					{
						lMax = MAX_LENGTH_IN_GRID;
					}
					else
					{
						if (lMax == 0)
							printf("before lmas is 0\n");
						lMax = std::min(MAX_LENGTH_IN_GRID, column1 - j);

						if (lMax == 0)
							printf("after lmas is 0\n");
					}
					if (column2 > j)
					{
						lMax = std::min(lMax, (column2 - j));
					}

					if (row1 < i)
					{
						wMax = MAX_WIDTH_IN_GRID;
					}
					else
					{
						wMax = std::min(MAX_WIDTH_IN_GRID, row1 - i);
					}
					if (row2 > i)
					{
						wMax = std::min(wMax, (row2 - i));
					}

					//get the largest extension scope(limited by other buildings)
					for (int yoffset = 0; yoffset < lMax; yoffset++)
					{
						if (grids[i][j + yoffset])
						{
							for (int xoffset = 0; xoffset < wMax; xoffset++)
							{
								if (!grids[i + xoffset][j + yoffset])
								{
									wMax = xoffset;
									break;
								}
							}
						}
						else
						{
							lMax = yoffset;
							break;
						}
					}

					for (int xoffset = 0; xoffset < wMax; xoffset++)
					{
						for (int yoffset = 0; yoffset < lMax; yoffset++)
						{
							if (!grids[i + xoffset][j + yoffset])
							{
								lMax = yoffset;
								break;
							}
						}
					}

					w = rand() % wMax + 3;
					l = rand() % lMax + 3;
					h = rand() % 10 + 1;

					building* blding = new building({ l, w, h, glm::vec2(i, j) });
					buildingStore->push_back(blding);
				}
				for (int m = 0; m < l; m++)
				{
					for (int n = 0; n < w; n++)
					{
						grids[i + n][j + m] = false;
						buildingBase->push_back(new singlegrid({ i + n, j + m }));
					}
				}
			}
		}
	}

	loadBuffer();
}

void CityModeller::loadBuffer()
{
		//building vertex and road vertex,using interleaved buffer
		for (int i = 0; i < buildingStore->size(); i++)
		{
			//choose texture for window side of the buildings
			int windowRank = rand() % 6  ;
			int windowcoordinatex = windowRank % 4;
			int windowcoordinatey = (int)windowRank / 4;
			//choose roottop texture
			int rooftopcoordinatex = rand() % 4;
			int rooftopcoordinatey = 0;
			//*************************************************************************************************************************************************
			//data for top
			//*************************************************************************************************************************************************
			
			//vertex0
			if (buildingStore->size() >2500)
			{
				//int a = buildings->size();
				throw exception();	
			}
 			buildings->push_back({ buildingStore->at(i)->gridCoordinate.y*UNITLENGHT + SPACE, buildingStore->at(i)->height*UNITLENGHT, buildingStore->at(i)->gridCoordinate.x*UNITLENGHT + SPACE, 1.0 / TEXGRIDSPERROW*rooftopcoordinatex, 1.0 / TEXGRIDSPERCOLUMN, 0, 1, 0 });
			
			//vertex1
			buildings->push_back({ buildings->at(5 * 6 * i).x + (buildingStore->at(i)->length*UNITLENGHT) - 2 * SPACE, buildings->at(5 * 6 * i).y, buildings->at(5 * 6 * i).z, 1.0 / TEXGRIDSPERROW*(rooftopcoordinatex + 1), 1.0 / TEXGRIDSPERCOLUMN, 0, 1, 0 });

			//vertex2
			buildings->push_back({ buildings->at(5 * 6 * i+1).x, buildings->at(5 * 6 * i + 1).y, buildings->at(5 * 6 * i + 1).z + (buildingStore->at(i)->width*UNITLENGHT) - 2 * SPACE, 1.0 / TEXGRIDSPERROW*(rooftopcoordinatex + 1), 0, 0, 1, 0 });

			//vertex0
			buildings->push_back ({ (buildingStore->at(i)->gridCoordinate.y*UNITLENGHT) + SPACE, buildingStore->at(i)->height*UNITLENGHT, (buildingStore->at(i)->gridCoordinate.x*UNITLENGHT) + SPACE, 1.0 / TEXGRIDSPERROW*rooftopcoordinatex, 1.0 / TEXGRIDSPERCOLUMN, 0, 1, 0 });

			//vertex2
			buildings->push_back ({ buildings->at(5 * 6 * i + 1).x, buildings->at(5 * 6 * i + 1).y, buildings->at(5 * 6 * i + 1).z + (buildingStore->at(i)->width*UNITLENGHT) - 2 * SPACE, 1.0 / TEXGRIDSPERROW*(rooftopcoordinatex + 1), 0, 0, 1, 0 });

			//vertex3
			buildings->push_back ({ buildings->at(5 * 6 * i).x, buildings->at(5 * 6 * i).y, buildings->at(5 * 6 * i + 2).z, 1.0 / TEXGRIDSPERROW*rooftopcoordinatex, 0, 0, 1, 0 });


			//*************************************************************************************************************************************************
			//   data for front
			//*************************************************************************************************************************************************

			//vertex3
			buildings->push_back({ buildings->at(5 * 6 * i).x, buildings->at(5 * 6 * i).y, buildings->at(5 * 6 * i + 2).z, 1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex, 1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2, 0, 0, 1 });
			//vertex 2
			buildings->push_back({ buildings->at(5 * 6 * i + 1).x, buildings->at(5 * 6 * i + 1).y, buildings->at(5 * 6 * i + 1).z + (buildingStore->at(i)->width*UNITLENGHT) - 2 * SPACE, 1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1), 1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2, 0, 0, 1 });
			//vertex7
			buildings->push_back({ buildings->at(5 * 6 * i + 2).x, 0, buildings->at(5 * 6 * i + 2).z, 1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1), 1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2, 0, 0, 1 });
			//vertex3
			buildings->push_back({ buildings->at(5 * 6 * i).x, buildings->at(5 * 6 * i).y, buildings->at(5 * 6 * i + 2).z, 1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex, 1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2, 0, 0, 1 });
			//vertex7
			buildings->push_back({ buildings->at(5 * 6 * i + 2).x, 0, buildings->at(5 * 6 * i + 2).z, 1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1), 1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2, 0, 0, 1 });
			//vertex 8
			buildings->push_back({ buildings->at(5 * 6 * i).x, 0, buildings->at(5 * 6 * i + 10).z, 1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex, 1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2, 0, 0, 1 });

			//*************************************************************************************************************************************************
			//data for left side
			//*************************************************************************************************************************************************

			//vertex0
			buildings->push_back({ buildingStore->at(i)->gridCoordinate.y*UNITLENGHT + SPACE, buildingStore->at(i)->height*UNITLENGHT, buildingStore->at(i)->gridCoordinate.x*UNITLENGHT + SPACE, 1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex, 1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2, -1, 0, 0 });

			//vertex3
			buildings->push_back({ buildings->at(5 * 6 * i).x, buildings->at(5 * 6 * i).y, buildings->at(5 * 6 * i + 2).z, 1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1), 1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2, -1, 0, 0 });

			//vertex5
			buildings->push_back({ buildings->at(5 * 6 * i).x, 0, buildings->at(5 * 6 * i).z, 1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex, 1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2, -1, 0, 0 });

			//vertex3
			buildings->push_back({ buildings->at(5 * 6 * i).x, buildings->at(5 * 6 * i).y, buildings->at(5 * 6 * i + 2).z, 1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1), 1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2, -1, 0, 0 });

			//vertex5		
			buildings->push_back({ buildings->at(5 * 6 * i).x, 0, buildings->at(5 * 6 * i).z, 1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex, 1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2, -1, 0, 0 });

			//vertex8
			buildings->push_back({ buildings->at(5 * 6 * i).x, 0, buildings->at(5 * 6 * i + 10).z, 1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1), 1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2, -1, 0, 0 });

			//*************************************************************************************************************************************************
			//data for right side
			//*************************************************************************************************************************************************

			//vertex1
			buildings->push_back({ buildings->at(5 * 6 * i).x + buildingStore->at(i)->length*UNITLENGHT - 2 * SPACE, buildings->at(5 * 6 * i).y, buildings->at(5 * 6 * i).z, 1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1), 1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2, 1, 0, 0 });

			//vertex2
			buildings->push_back({ buildings->at(5 * 6 * i + 1).x, buildings->at(5 * 6 * i + 1).y, buildings->at(5 * 6 * i + 1).z + (buildingStore->at(i)->width*UNITLENGHT) - 2 * SPACE, 1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex, 1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2, 1, 0, 0 });

			//vertex6
			buildings->push_back({ buildings->at(5 * 6 * i + 1).x, 0, buildings->at(5 * 6 * i + 1).z, 1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1), 1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2, 1, 0, 0 });

			//vertex2
			buildings->push_back({ buildings->at(5 * 6 * i + 1).x, buildings->at(5 * 6 * i + 1).y, buildings->at(5 * 6 * i + 1).z + (buildingStore->at(i)->width*UNITLENGHT) - 2 * SPACE, 1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex, 1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2, 1, 0, 0 });

			//vertex6
			buildings->push_back({ buildings->at(5 * 6 * i + 1).x, 0, buildings->at(5 * 6 * i + 1).z, 1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1), 1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2, 1, 0, 0 });

			//vertex7
			buildings->push_back({ buildings->at(5 * 6 * i + 1).x, 0, buildings->at(5 * 6 * i + 2).z, 1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex, 1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2, 1, 0, 0 });


			//*************************************************************************************************************************************************
			//data for back
			//*************************************************************************************************************************************************
			//vertex0
			buildings->push_back({ buildingStore->at(i)->gridCoordinate.y*UNITLENGHT + SPACE, buildingStore->at(i)->height*UNITLENGHT, buildingStore->at(i)->gridCoordinate.x*UNITLENGHT + SPACE, 1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex, 1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2, 0, 0, -1 });

			//vertex1
			buildings->push_back({ buildings->at(5 * 6 * i).x + buildingStore->at(i)->length*UNITLENGHT - 2 * SPACE, buildings->at(5 * 6 * i).y, buildings->at(5 * 6 * i).z, 1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1), 1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2, 0, 0, -1 });

			//vertex6
			buildings->push_back({ buildings->at(5 * 6 * i + 1).x, 0, buildings->at(5 * 6 * i + 1).z, 1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1), 1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2, 0, 0, -1 });

			//vertex0
			buildings->push_back({ buildingStore->at(i)->gridCoordinate.y*UNITLENGHT + SPACE, buildingStore->at(i)->height*UNITLENGHT, buildingStore->at(i)->gridCoordinate.x*UNITLENGHT + SPACE, 1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex, 1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2, 0, 0, -1 });

			//vertex6
			buildings->push_back({ buildings->at(5 * 6 * i + 1).x, 0, buildings->at(5 * 6 * i + 1).z, 1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1), 1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2, 0, 0, -1 });

			//vertex5
			buildings->push_back({ buildings->at(5 * 6 * i).x, 0, buildings->at(5 * 6 * i).z, 1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex, 1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2, 0, 0, -1 });

		}

		//push road vertexs into vector
		//the 1st for loop load the road that is on row,the 2nd for loop load the road on column,because the texture coordinate for them 
		//is different(90 degree rotated) so we need to use two for loops
		for (int j = 0; j < roadStore->size() / 2; j++)
		{
			//vertex 0
			buildings->push_back({ roadStore->at(j)->beginGridColumn*UNITLENGHT, ROADHEIGHT, roadStore->at(j)->beginGridRow*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 6, 1.0 / TEXGRIDSPERCOLUMN * 3, 0, 1, 0 });
			//vertex 2
			buildings->push_back({ (roadStore->at(j)->endGridColumn + 1)*UNITLENGHT, ROADHEIGHT, (roadStore->at(j)->endGridRow + 1)*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 4, 1.0 / TEXGRIDSPERCOLUMN * 1, 0, 1, 0 });
			//vertex 1
			buildings->push_back({ (roadStore->at(j)->endGridColumn + 1)*UNITLENGHT, ROADHEIGHT, roadStore->at(j)->beginGridRow*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 6, 1.0 / TEXGRIDSPERCOLUMN * 1, 0, 1, 0 });
			//vertex 0
			buildings->push_back({ roadStore->at(j)->beginGridColumn*UNITLENGHT, ROADHEIGHT, roadStore->at(j)->beginGridRow*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 6, 1.0 / TEXGRIDSPERCOLUMN * 3, 0, 1, 0 });
			//vertex 2
			buildings->push_back({ (roadStore->at(j)->endGridColumn + 1)*UNITLENGHT, ROADHEIGHT, (roadStore->at(j)->endGridRow + 1)*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 4, 1.0 / TEXGRIDSPERCOLUMN * 1, 0, 1, 0 });
			//vertex 3
			buildings->push_back({ roadStore->at(j)->beginGridColumn*UNITLENGHT, ROADHEIGHT, (roadStore->at(j)->endGridRow + 1)*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 4, 1.0 / TEXGRIDSPERCOLUMN * 3, 0, 1, 0 });
		}

		for (int j = 0; j < roadStore->size() / 2; j++)
		{
			//vertex 0
			buildings->push_back({ roadStore->at(j + roadStore->size() / 2)->beginGridColumn*UNITLENGHT, ROADHEIGHT, roadStore->at(j + roadStore->size() / 2)->beginGridRow*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 4, 1.0 / TEXGRIDSPERROW * 2, 0, 1, 0 });
			//vertex 2
			buildings->push_back({ (roadStore->at(j + roadStore->size() / 2)->endGridColumn + 1)*UNITLENGHT, ROADHEIGHT, (roadStore->at(j + roadStore->size() / 2)->endGridRow + 1)*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 6, 1.0 / TEXGRIDSPERROW * 4, 0, 1, 0 });
			//vertex 1
			buildings->push_back({ (roadStore->at(j + roadStore->size() / 2)->endGridColumn + 1)*UNITLENGHT, ROADHEIGHT, roadStore->at(j + roadStore->size() / 2)->beginGridRow*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 6, 1.0 / TEXGRIDSPERROW * 2, 0, 1, 0 });
			//vertex 0
			buildings->push_back({ roadStore->at(j + roadStore->size() / 2)->beginGridColumn*UNITLENGHT, ROADHEIGHT, roadStore->at(j + roadStore->size() / 2)->beginGridRow*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 4, 1.0 / TEXGRIDSPERROW * 2, 0, 1, 0 });
			//vertex 2
			buildings->push_back({ (roadStore->at(j + roadStore->size() / 2)->endGridColumn + 1)*UNITLENGHT, ROADHEIGHT, (roadStore->at(j + roadStore->size() / 2)->endGridRow + 1)*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 6, 1.0 / TEXGRIDSPERROW * 4, 0, 1, 0 });
			//vertex 3
			buildings->push_back({ roadStore->at(j + roadStore->size() / 2)->beginGridColumn*UNITLENGHT, ROADHEIGHT, (roadStore->at(j + roadStore->size() / 2)->endGridRow + 1)*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 4, 1.0 / TEXGRIDSPERROW * 4, 0, 1, 0 });
		}


		// space area
		for (int j = 0; j < space->size(); j++)
		{
			//vertex0
			buildings->push_back({ space->at(j)->column*UNITLENGHT, ROADHEIGHT, space->at(j)->row*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 5 + TEXSAMPLEGAP, 1.0 / TEXGRIDSPERCOLUMN - TEXSAMPLEGAP, 0, 1, 0 });
			//vertex1
			buildings->push_back({ (space->at(j)->column + 1)*UNITLENGHT, ROADHEIGHT, space->at(j)->row*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 6 - TEXSAMPLEGAP, 1.0 / TEXGRIDSPERCOLUMN - TEXSAMPLEGAP, 0, 1, 0 });
			//vertex2
			buildings->push_back({ (space->at(j)->column + 1)*UNITLENGHT, ROADHEIGHT, (space->at(j)->row + 1)*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 6 - TEXSAMPLEGAP, TEXSAMPLEGAP, 0, 1, 0 });
			//vertex0
			buildings->push_back({ space->at(j)->column*UNITLENGHT, ROADHEIGHT, space->at(j)->row*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 5 + TEXSAMPLEGAP, 1.0 / TEXGRIDSPERCOLUMN - TEXSAMPLEGAP, 0, 1, 0 });
			//vertex2
			buildings->push_back({ (space->at(j)->column + 1)*UNITLENGHT, ROADHEIGHT, (space->at(j)->row + 1)*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 6 - TEXSAMPLEGAP, TEXSAMPLEGAP, 0, 1, 0 });
			//vertex3
			buildings->push_back({ space->at(j)->column *UNITLENGHT, ROADHEIGHT, (space->at(j)->row + 1)*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 5 + TEXSAMPLEGAP, TEXSAMPLEGAP, 0, 1, 0 });
		}

		// zebra crossing

		for (int j = 0; j < cross->size(); j++)
		{
			//vertex0
			buildings->push_back({ cross->at(j)->column*UNITLENGHT, ROADHEIGHT, cross->at(j)->row*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 6, 1.0 / TEXGRIDSPERCOLUMN, 0, 1, 0 });
			//vertex1
			buildings->push_back({ (cross->at(j)->column + 1)*UNITLENGHT, ROADHEIGHT, cross->at(j)->row*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 7, 1.0 / TEXGRIDSPERCOLUMN, 0, 1, 0 });
			//vertex2
			buildings->push_back({ (cross->at(j)->column + 1)*UNITLENGHT, ROADHEIGHT, (cross->at(j)->row + 1)*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 7, 0, 0, 1, 0 });
			//vertex0
			buildings->push_back({ cross->at(j)->column*UNITLENGHT, ROADHEIGHT, cross->at(j)->row*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 6, 1.0 / TEXGRIDSPERCOLUMN, 0, 1, 0 });
			//vertex2
			buildings->push_back({ (cross->at(j)->column + 1)*UNITLENGHT, ROADHEIGHT, (cross->at(j)->row + 1)*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 7, 0, 0, 1, 0 });
			//vertex3
			buildings->push_back({ cross->at(j)->column *UNITLENGHT, ROADHEIGHT, (cross->at(j)->row + 1)*UNITLENGHT, 1.0 / TEXGRIDSPERROW * 6, 0, 0, 1, 0 });
		}

		//grass
		for (int j = 0; j < 6; j++)
		{
			buildings->push_back(plane[j]);
		}

		printf("buildings: %d\n", buildings->size());

		printf("buildingstore: %d\n", buildingStore->size());
}

void CityModeller::clearBuffer()
{
	printf("clear buffer\n");
	/*
	for (int i = buildingStore->size()-1; i >0; i--)
	{
		building* temp = buildingStore->at(i);
		delete temp;
	}
	for (int i = roadStore->size()-1; i >0; i--)
	{
		road* temp = roadStore->at(i);
		delete temp;
	}
	
	for (int i = cross->size()-1; i >0; i--)
	{
		delete cross->at(i);
	}
	for (int i = space->size()-1; i >0; i--)
	{
		delete space->at(i);
	}
	for (int i = buildingBase->size()-1; i > 0; i--)
	{
		delete buildingBase->at(i);
	}
	*/
	buildingStore->clear();
	roadStore->clear();
	buildings->clear();
	cross->clear();
	space->clear();
	buildingBase->clear();
}

std::vector<Vertex2>* CityModeller::getBuffer()
{
	return buildings;
}

