#include "CityModeller.h"
#include <time.h>
#include <algorithm>
#include <stdlib.h> 
#include "stdafx.h"


#define BEGININGGRID	 0
#define ROADLENGTH		 70
#define UNITLENGHT 50
#define ZERO     0
#define ONETIME  0.33333333
#define TWICE    0.66666666
#define TRIPLE   1
#define SPACE    5
#define ROADHEIGHT 0
#define TEXGRIDSPERROW 8
#define TEXGRIDSPERCOLUMN 5
#define TEXSAMPLEGAP   0.05
//city_vertices_data' max length, height and width in the unit of "Grid"
#define MAX_LENGTH_IN_GRID 6
#define MAX_WIDTH_IN_GRID 6
#define MAX_HEIGHT_IN_GRID 10
#define MIN_HEIGHT_IN_GRID 3
#define MIN_LENGTH_IN_GRID 3
#define MIN_WIDTH_IN_GRID 3

CityModeller::CityModeller()
{
	//Create storage vector
	buildingStore = new vector < building* >();
	roadStore = new vector<road*>();
	city_vertices_data = new vector<Vertex2>();
	cross = new vector<singlegrid*>();
	buildingBase = new vector<singlegrid*>();
	space = new vector<singlegrid*>();
	aabbCollidersCollection = new vector<Colliders::AABBCollider*>();

	//random seed
	srand((unsigned)time(NULL));

    mat = wolf::MaterialManager::Inst()->CreateMaterial("city_model_material");
	mat->SetDepthTest(true);
	mat->SetBlend(false);
	//Initialize material surface property
	g_maskSurface = new SurfaceMaterial();
	g_maskSurface->setDiffuse(wolf::Color4(1, 1, 0.8, 1));
	g_maskSurface->setAmbient(wolf::Color4(1, 1, 1, 1));
	g_maskSurface->setSpecular(wolf::Color4(1, 1, 1, 200));

	// Initialize the light parameters
	g_light = new DirectionalLight();
	g_light->setDiffuse(wolf::Color4(1.0, 1.0, 0.6, 1));
	g_light->setAmbient(wolf::Color4(1, 1, 1, 1));
	g_light->setSpecular(wolf::Color4(0.2, 0.2, 0.1, 1));

	last_time_key_l_pressed = glfwGetTime();
	lightAngle = 0;
}

CityModeller::~CityModeller()
{
	clearBuffer();
}

///<summary>
///This function create city data in grids model
///</summary>
void CityModeller::generateCityLayoutData()
{
#pragma region Initialization
    //clear store buffer
    clearBuffer();
	
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			grids[i][j] = true;
		}
	}
#pragma endregion

#pragma region Generate Road Data
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//gengerate roads'data
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	row1 = rand() % SIZE;
	row2 = rand() % SIZE;
	while (row1 == row2)
	{
		row2 = rand() % SIZE;
	}
	column1 = rand() % SIZE;
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

	//Set the grids occupied by roads to be false
	for (int i = 0; i < SIZE; i++)
	{
		grids[row1][i] = false;
		grids[row2][i] = false;
		grids[i][column1] = false;
		grids[i][column2] = false;
	}
	
#pragma endregion

#pragma region "space region data"
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
#pragma endregion

#pragma region "generate buildings'data"
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//generate city_vertices_data'data
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	for (int x = 0; x < SIZE; x++)
	{
		for (int y = 0; y < SIZE; y++)
		{
			if (grids[x][y])
			{
				{	//city_vertices_data'length and width are counted from the selected grid to right(column+1) and to down(row+1)
					/***********************************************
					Diagram of city grid model:
				  £¨0£¬0£©->->->x++		  |<--width-->|_____
					 ¡ý   [][][][][][][][][][][][][][][]¡ü
					 ¡ý   [][][][][][][][][][][][][][][]length
					 ¡ý   [][][][][][][][][][][][][][][]¡ý
					y++	 [][][][][][][][][][][][][][][]-----

					*****************************************************/


					//get the largest extension scope(limited by the road)
					if (column1 < y)
					{
						lMax = MAX_LENGTH_IN_GRID;
					}
					else
					{
						lMax = std::min(MAX_LENGTH_IN_GRID, column1 - y);
					}
					if (column2 > y)
					{
						lMax = std::min(lMax, (column2 - y));
					}

					if (row1 < x)
					{
						wMax = MAX_WIDTH_IN_GRID;
					}
					else
					{
						wMax = std::min(MAX_WIDTH_IN_GRID, row1 - x);
					}
					if (row2 > x)
					{
						wMax = std::min(wMax, (row2 - x));
					}

					//If there is enough space bettween the current grid and the edge of the city
					//Calculate the max width and height that the building could extends
					//otherwise set them to be 0 and the building would not be store in the next 
					//for loop.
					//WARNNING:BE CAREFUL OF READ OR WRITE OUT OF THE RANGE OF ARRAY "grid"
					if ((SIZE - x) > MIN_WIDTH_IN_GRID && (SIZE - y) > MIN_LENGTH_IN_GRID)
					{
						//if the max width and height is over the size of the city set the largest 
						//extension to be the edge of the city
						wMax = std::min((SIZE - x), wMax);
						lMax = std::min((SIZE - y), lMax);

						//get the largest extension scope(limited by other city_vertices_data)
						for (int yoffset = 0; yoffset < lMax; yoffset++)
						{
							if (grids[x][y + yoffset])
							{
								for (int xoffset = 0; xoffset < wMax; xoffset++)
								{
									if (!grids[x + xoffset][y + yoffset])
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
					}
					else
					{
						wMax = 0;
						lMax = 0;
					}

#pragma region "maybenoneed"
					/*for (int xoffset = 0; xoffset < wMax; xoffset++)
					{
						for (int yoffset = 0; yoffset < lMax; yoffset++)
						{
							if (!grids[x + xoffset][y + yoffset])
							{
								lMax = yoffset;
								break;
							}
						}
					}*/
#pragma endregion

					//If the calculated max width and height is larger than the specified min value,store the building data
					if (wMax>=MIN_WIDTH_IN_GRID&&lMax>=MIN_LENGTH_IN_GRID)
					{
						w = rand() % (wMax-MIN_WIDTH_IN_GRID+1)+MIN_WIDTH_IN_GRID;
						l = rand() % (lMax -MIN_LENGTH_IN_GRID+1)+MIN_LENGTH_IN_GRID;
						h = rand() % (MAX_HEIGHT_IN_GRID - MIN_HEIGHT_IN_GRID + 1) + MIN_HEIGHT_IN_GRID;

						buildingStore->push_back(new building({ static_cast<GLfloat>(l), static_cast<GLfloat>(w), static_cast<GLfloat>(h), glm::vec2(x, y) }));

						for (int m = 0; m < l; m++)
						{
							for (int n = 0; n < w; n++)
							{
								
								grids[x + n][y + m] = false;
								buildingBase->push_back(new singlegrid({ x + n, y + m }));
							}
						}
					}
				}
			}
		}
	}
#pragma endregion
	
	//Generate the data which would be used for rendering from grid model
	loadBuffer();
}

void CityModeller::SetCamera(Camera* mainCamera)
{
	this->mainCamera = mainCamera;
}

void CityModeller::loadBuffer()
{
		
#pragma region "Load Buffer Data For Buildings"
		//building vertex and road vertex,using interleaved buffer
		for (int i = 0; i < buildingStore->size(); i++)
		{
			//choose texture for window side of the city_vertices_data
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
 			city_vertices_data->push_back({ buildingStore->at(i)->gridCoordinate.y*UNITLENGHT + SPACE, buildingStore->at(i)->height*UNITLENGHT, buildingStore->at(i)->gridCoordinate.x*UNITLENGHT + SPACE, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW*rooftopcoordinatex), 1.0 / TEXGRIDSPERCOLUMN, 0, 1, 0 });
			//vertex1
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i).x + (buildingStore->at(i)->length*UNITLENGHT) - 2 * SPACE, city_vertices_data->at(5 * 6 * i).y, city_vertices_data->at(5 * 6 * i).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW*(rooftopcoordinatex + 1)), 1.0 / TEXGRIDSPERCOLUMN, 0, 1, 0 });
			//vertex2
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i+1).x, city_vertices_data->at(5 * 6 * i + 1).y, city_vertices_data->at(5 * 6 * i + 1).z + (buildingStore->at(i)->width*UNITLENGHT) - 2 * SPACE, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW*(rooftopcoordinatex + 1)), 0, 0, 1, 0 });
			//vertex0
			city_vertices_data->push_back ({ (buildingStore->at(i)->gridCoordinate.y*UNITLENGHT) + SPACE, buildingStore->at(i)->height*UNITLENGHT, (buildingStore->at(i)->gridCoordinate.x*UNITLENGHT) + SPACE, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW*rooftopcoordinatex), 1.0 / TEXGRIDSPERCOLUMN, 0, 1, 0 });
			//vertex2
			city_vertices_data->push_back ({ city_vertices_data->at(5 * 6 * i + 1).x, city_vertices_data->at(5 * 6 * i + 1).y, city_vertices_data->at(5 * 6 * i + 1).z + (buildingStore->at(i)->width*UNITLENGHT) - 2 * SPACE, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW*(rooftopcoordinatex + 1)), 0, 0, 1, 0 });
			//vertex3
			city_vertices_data->push_back ({ city_vertices_data->at(5 * 6 * i).x, city_vertices_data->at(5 * 6 * i).y, city_vertices_data->at(5 * 6 * i + 2).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW*rooftopcoordinatex), 0, 0, 1, 0 });

			//*************************************************************************************************************************************************
			//   data for front
			//*************************************************************************************************************************************************

			//vertex3
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i).x, city_vertices_data->at(5 * 6 * i).y, city_vertices_data->at(5 * 6 * i + 2).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2), 0, 0, 1 });
			//vertex 2
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i + 1).x, city_vertices_data->at(5 * 6 * i + 1).y, city_vertices_data->at(5 * 6 * i + 1).z + (buildingStore->at(i)->width*UNITLENGHT) - 2 * SPACE, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1)), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2), 0, 0, 1 });
			//vertex7
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i + 2).x, 0, city_vertices_data->at(5 * 6 * i + 2).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1)), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2), 0, 0, 1 });
			//vertex3
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i).x, city_vertices_data->at(5 * 6 * i).y, city_vertices_data->at(5 * 6 * i + 2).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2), 0, 0, 1 });
			//vertex7
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i + 2).x, 0, city_vertices_data->at(5 * 6 * i + 2).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1)), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2), 0, 0, 1 });
			//vertex 8
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i).x, 0, city_vertices_data->at(5 * 6 * i + 10).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2), 0, 0, 1 });

			//*************************************************************************************************************************************************
			//data for left side
			//*************************************************************************************************************************************************
			//vertex0
			city_vertices_data->push_back({ buildingStore->at(i)->gridCoordinate.y*UNITLENGHT + SPACE, buildingStore->at(i)->height*UNITLENGHT, buildingStore->at(i)->gridCoordinate.x*UNITLENGHT + SPACE, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2), -1, 0, 0 });
			//vertex3
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i).x, city_vertices_data->at(5 * 6 * i).y, city_vertices_data->at(5 * 6 * i + 2).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1)), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2), -1, 0, 0 });
			//vertex5
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i).x, 0, city_vertices_data->at(5 * 6 * i).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2), -1, 0, 0 });
			//vertex3
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i).x, city_vertices_data->at(5 * 6 * i).y, city_vertices_data->at(5 * 6 * i + 2).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1)), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2), -1, 0, 0 });
			//vertex5		
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i).x, 0, city_vertices_data->at(5 * 6 * i).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2), -1, 0, 0 });
			//vertex8
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i).x, 0, city_vertices_data->at(5 * 6 * i + 10).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1)), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2), -1, 0, 0 });

			//*************************************************************************************************************************************************
			//data for right side
			//*************************************************************************************************************************************************
			//vertex1
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i).x + buildingStore->at(i)->length*UNITLENGHT - 2 * SPACE, city_vertices_data->at(5 * 6 * i).y, city_vertices_data->at(5 * 6 * i).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1)), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2), 1, 0, 0 });
			//vertex2
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i + 1).x, city_vertices_data->at(5 * 6 * i + 1).y, city_vertices_data->at(5 * 6 * i + 1).z + (buildingStore->at(i)->width*UNITLENGHT) - 2 * SPACE, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2), 1, 0, 0 });
			//vertex6
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i + 1).x, 0, city_vertices_data->at(5 * 6 * i + 1).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1)), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2), 1, 0, 0 });
			//vertex2
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i + 1).x, city_vertices_data->at(5 * 6 * i + 1).y, city_vertices_data->at(5 * 6 * i + 1).z + (buildingStore->at(i)->width*UNITLENGHT) - 2 * SPACE, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2), 1, 0, 0 });
			//vertex6
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i + 1).x, 0, city_vertices_data->at(5 * 6 * i + 1).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1)), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2), 1, 0, 0 });
			//vertex7
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i + 1).x, 0, city_vertices_data->at(5 * 6 * i + 2).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2), 1, 0, 0 });


			//*************************************************************************************************************************************************
			//data for back
			//*************************************************************************************************************************************************
			//vertex0
			city_vertices_data->push_back({ buildingStore->at(i)->gridCoordinate.y*UNITLENGHT + SPACE, buildingStore->at(i)->height*UNITLENGHT, buildingStore->at(i)->gridCoordinate.x*UNITLENGHT + SPACE, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2), 0, 0, -1 });
			//vertex1
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i).x + buildingStore->at(i)->length*UNITLENGHT - 2 * SPACE, city_vertices_data->at(5 * 6 * i).y, city_vertices_data->at(5 * 6 * i).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1)), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2), 0, 0, -1 });
			//vertex6
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i + 1).x, 0, city_vertices_data->at(5 * 6 * i + 1).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1)), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2), 0, 0, -1 });
			//vertex0
			city_vertices_data->push_back({ buildingStore->at(i)->gridCoordinate.y*UNITLENGHT + SPACE, buildingStore->at(i)->height*UNITLENGHT, buildingStore->at(i)->gridCoordinate.x*UNITLENGHT + SPACE, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*windowcoordinatey * 2), 0, 0, -1 });
			//vertex6
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i + 1).x, 0, city_vertices_data->at(5 * 6 * i + 1).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * (windowcoordinatex + 1)), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2), 0, 0, -1 });
			//vertex5
			city_vertices_data->push_back({ city_vertices_data->at(5 * 6 * i).x, 0, city_vertices_data->at(5 * 6 * i).z, static_cast<GLfloat>(1.0 / TEXGRIDSPERROW * 2 * windowcoordinatex), static_cast<GLfloat>(1 - 1.0 / TEXGRIDSPERCOLUMN*(windowcoordinatey + 1) * 2), 0, 0, -1 });
		}

#pragma endregion

#pragma region "Load Vertex Data for Roads"
		//push road vertexs into vector
		//the 1st for loop load the road that is on row,the 2nd for loop load the road on column,because the texture coordinate for them 
		//is different(90 degree rotated) so we need to use two for loops
		for (int j = 0; j < roadStore->size() / 2; j++)
		{
			//vertex 0
			city_vertices_data->push_back({ static_cast<GLfloat>(roadStore->at(j)->beginGridColumn*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>(roadStore->at(j)->beginGridRow*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 6, 1.0 / TEXGRIDSPERCOLUMN * 3, 0, 1, 0 });
			//vertex 2
			city_vertices_data->push_back({ static_cast<GLfloat>((roadStore->at(j)->endGridColumn + 1)*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>((roadStore->at(j)->endGridRow + 1)*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 4, 1.0 / TEXGRIDSPERCOLUMN * 1, 0, 1, 0 });
			//vertex 1
			city_vertices_data->push_back({ static_cast<GLfloat>((roadStore->at(j)->endGridColumn + 1)*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>(roadStore->at(j)->beginGridRow*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 6, 1.0 / TEXGRIDSPERCOLUMN * 1, 0, 1, 0 });
			//vertex 0
			city_vertices_data->push_back({ static_cast<GLfloat>(roadStore->at(j)->beginGridColumn*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>(roadStore->at(j)->beginGridRow*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 6, 1.0 / TEXGRIDSPERCOLUMN * 3, 0, 1, 0 });
			//vertex 2
			city_vertices_data->push_back({ static_cast<GLfloat>((roadStore->at(j)->endGridColumn + 1)*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>((roadStore->at(j)->endGridRow + 1)*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 4, 1.0 / TEXGRIDSPERCOLUMN * 1, 0, 1, 0 });
			//vertex 3
			city_vertices_data->push_back({ static_cast<GLfloat>(roadStore->at(j)->beginGridColumn*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>((roadStore->at(j)->endGridRow + 1)*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 4, 1.0 / TEXGRIDSPERCOLUMN * 3, 0, 1, 0 });
		}

		for (int j = 0; j < roadStore->size() / 2; j++)
		{
			//vertex 0
			city_vertices_data->push_back({ static_cast<GLfloat>(roadStore->at(j + roadStore->size() / 2)->beginGridColumn*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>(roadStore->at(j + roadStore->size() / 2)->beginGridRow*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 4, 1.0 / TEXGRIDSPERROW * 2, 0, 1, 0 });
			//vertex 2
			city_vertices_data->push_back({ static_cast<GLfloat>((roadStore->at(j + roadStore->size() / 2)->endGridColumn + 1)*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>((roadStore->at(j + roadStore->size() / 2)->endGridRow + 1)*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 6, 1.0 / TEXGRIDSPERROW * 4, 0, 1, 0 });
			//vertex 1
			city_vertices_data->push_back({ static_cast<GLfloat>((roadStore->at(j + roadStore->size() / 2)->endGridColumn + 1)*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>(roadStore->at(j + roadStore->size() / 2)->beginGridRow*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 6, 1.0 / TEXGRIDSPERROW * 2, 0, 1, 0 });
			//vertex 0
			city_vertices_data->push_back({ static_cast<GLfloat>(roadStore->at(j + roadStore->size() / 2)->beginGridColumn*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>(roadStore->at(j + roadStore->size() / 2)->beginGridRow*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 4, 1.0 / TEXGRIDSPERROW * 2, 0, 1, 0 });
			//vertex 2
			city_vertices_data->push_back({ static_cast<GLfloat>((roadStore->at(j + roadStore->size() / 2)->endGridColumn + 1)*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>((roadStore->at(j + roadStore->size() / 2)->endGridRow + 1)*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 6, 1.0 / TEXGRIDSPERROW * 4, 0, 1, 0 });
			//vertex 3
			city_vertices_data->push_back({ static_cast<GLfloat>(roadStore->at(j + roadStore->size() / 2)->beginGridColumn*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>((roadStore->at(j + roadStore->size() / 2)->endGridRow + 1)*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 4, 1.0 / TEXGRIDSPERROW * 4, 0, 1, 0 });
		}

#pragma endregion

#pragma region "Load Vertex Data For Space Area, Zebra Crossing and Grass"
		// space area
		for (int j = 0; j < space->size(); j++)
		{
			//vertex0
			city_vertices_data->push_back({ static_cast<GLfloat>(space->at(j)->column*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>(space->at(j)->row*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 5 + TEXSAMPLEGAP, 1.0 / TEXGRIDSPERCOLUMN - TEXSAMPLEGAP, 0, 1, 0 });
			//vertex1
			city_vertices_data->push_back({ static_cast<GLfloat>((space->at(j)->column + 1)*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>(space->at(j)->row*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 6 - TEXSAMPLEGAP, 1.0 / TEXGRIDSPERCOLUMN - TEXSAMPLEGAP, 0, 1, 0 });
			//vertex2
			city_vertices_data->push_back({ static_cast<GLfloat>((space->at(j)->column + 1)*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>((space->at(j)->row + 1)*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 6 - TEXSAMPLEGAP, TEXSAMPLEGAP, 0, 1, 0 });
			//vertex0
			city_vertices_data->push_back({ static_cast<GLfloat>(space->at(j)->column*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>(space->at(j)->row*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 5 + TEXSAMPLEGAP, 1.0 / TEXGRIDSPERCOLUMN - TEXSAMPLEGAP, 0, 1, 0 });
			//vertex2
			city_vertices_data->push_back({ static_cast<GLfloat>((space->at(j)->column + 1)*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>((space->at(j)->row + 1)*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 6 - TEXSAMPLEGAP, TEXSAMPLEGAP, 0, 1, 0 });
			//vertex3
			city_vertices_data->push_back({ static_cast<GLfloat>(space->at(j)->column *UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>((space->at(j)->row + 1)*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 5 + TEXSAMPLEGAP, TEXSAMPLEGAP, 0, 1, 0 });
		}

		// zebra crossing

		for (int j = 0; j < cross->size(); j++)
		{
			//vertex0
			city_vertices_data->push_back({ static_cast<GLfloat>(cross->at(j)->column*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>(cross->at(j)->row*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 6, 1.0 / TEXGRIDSPERCOLUMN, 0, 1, 0 });
			//vertex1
			city_vertices_data->push_back({ static_cast<GLfloat>((cross->at(j)->column + 1)*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>(cross->at(j)->row*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 7, 1.0 / TEXGRIDSPERCOLUMN, 0, 1, 0 });
			//vertex2
			city_vertices_data->push_back({ static_cast<GLfloat>((cross->at(j)->column + 1)*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>((cross->at(j)->row + 1)*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 7, 0, 0, 1, 0 });
			//vertex0
			city_vertices_data->push_back({ static_cast<GLfloat>(cross->at(j)->column*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>(cross->at(j)->row*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 6, 1.0 / TEXGRIDSPERCOLUMN, 0, 1, 0 });
			//vertex2
			city_vertices_data->push_back({ static_cast<GLfloat>((cross->at(j)->column + 1)*UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>((cross->at(j)->row + 1)*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 7, 0, 0, 1, 0 });
			//vertex3
			city_vertices_data->push_back({ static_cast<GLfloat>(cross->at(j)->column *UNITLENGHT), ROADHEIGHT, static_cast<GLfloat>((cross->at(j)->row + 1)*UNITLENGHT), 1.0 / TEXGRIDSPERROW * 6, 0, 0, 1, 0 });
		}

		//grass
		for (int j = 0; j < 6; j++)
		{
			city_vertices_data->push_back(plane[j]);
		}

#pragma endregion

#pragma region "Create Collider for buildings and ground(AABB Colliders)"

		//buildings' colliders
		for (int i = 0; i < buildingStore->size(); i++)
		{
			building* temp_building = buildingStore->at(i);
			vec3 pos;
			pos.x = (temp_building->gridCoordinate.y + temp_building->length / 2.0)*UNITLENGHT;
			pos.y = (temp_building->height/2.0)*UNITLENGHT;
			pos.z = (temp_building->gridCoordinate.x + temp_building->width / 2.0)*UNITLENGHT;
			//The width and length in grid model is different from the one in AABBCollider Model;
			double width = temp_building->width*UNITLENGHT -2 * SPACE;
			double length = temp_building->length*UNITLENGHT -2 * SPACE;
			double height = temp_building->height*UNITLENGHT;
			aabbCollidersCollection->push_back(new Colliders::AABBCollider(pos, width, length, height));
		}
		//ground's collider
		aabbCollidersCollection->push_back(new Colliders::AABBCollider(vec3(0,0,0),10000,10000,10));

#pragma endregion

#pragma region Load Attributes
		g_pVB1 = wolf::BufferManager::Inst()->CreateVertexBuffer(&city_vertices_data->at(0), sizeof(Vertex2) *(city_vertices_data->size()));
		g_pDecl = new wolf::VertexDeclaration();
		g_pDecl->Begin();
		g_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
		g_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
		g_pDecl->AppendAttribute(wolf::AT_Normal, 3, wolf::CT_Float);
		g_pDecl->SetVertexBuffer(g_pVB1);
		g_pDecl->End();
#pragma endregion 

		printf("city_vertices_data: %d\n", city_vertices_data->size());
		printf("buildingstore: %d\n", buildingStore->size());
}

void CityModeller::clearBuffer()
{
	printf("clear buffer\n");

    if (buildingStore->size()>0) {
        vector<building*>::iterator buildingIt = buildingStore->begin();
        for (; buildingIt != buildingStore->end(); ++buildingIt)
        {
            if (*buildingIt != NULL)
            {
                delete *buildingIt;
                *buildingIt = NULL;
            }
        }
        buildingStore->clear();
    }
    if (roadStore->size()>0) {
        vector<road*>::iterator roadIt = roadStore->begin();
        for (; roadIt != roadStore->end(); ++roadIt)
        {
            if (*roadIt != NULL)
            {
                delete *roadIt;
                *roadIt = NULL;
            }
        }
        roadStore->clear();
    }
    
    if (cross->size()>0) {
        vector<singlegrid*>::iterator crossIt = cross->begin();
        for (; crossIt != cross->end(); ++crossIt)
        {
            if (*crossIt != NULL)
            {
                delete *crossIt;
                *crossIt = NULL;
            }
        }
        cross->clear();
    }
    
    if (space->size()>0) {
        vector<singlegrid*>::iterator spaceIt = space->begin();
        for (; spaceIt != space->end(); ++spaceIt)
        {
            if (*spaceIt != NULL)
            {
                delete *spaceIt;
                *spaceIt = NULL;
            }
        }
        space->clear();
    }
    
    if (buildingBase->size()>0) {
        vector<singlegrid*>::iterator buildingBaseIt = buildingBase->begin();
        for (; buildingBaseIt != buildingBase->end(); ++buildingBaseIt)
        {
            if (*buildingBaseIt != NULL)
            {
                delete *buildingBaseIt;
                *buildingBaseIt = NULL;
            }
        }
        buildingBase->clear();
    }
    
    if (aabbCollidersCollection->size()>0) {
        vector<Colliders::AABBCollider*>::iterator aabbColliderIt = aabbCollidersCollection->begin();
        for (; aabbColliderIt != aabbCollidersCollection->end(); ++aabbColliderIt)
        {
            if (*aabbColliderIt != NULL)
            {
                delete *aabbColliderIt;
                *aabbColliderIt = NULL;
            }
        }
        aabbCollidersCollection->clear();
    }
    

	city_vertices_data->clear();
}

std::vector<Vertex2>* CityModeller::getBuffer()
{
	return city_vertices_data;
}

std::vector<Colliders::AABBCollider*>* CityModeller::GetAABBColliders()
{
	return aabbCollidersCollection;
}

void CityModeller::SetTexture(const string& tex)
{
	tex_map = wolf::TextureManager::Inst()->CreateTexture(tex);
	tex_map->SetFilterMode(wolf::Texture::FM_Nearest, wolf::Texture::FM_Nearest);
	tex_map->SetWrapMode(wolf::Texture::WM_Clamp, wolf::Texture::WM_Clamp);
	mat->SetTexture("tex", tex_map);
}

void CityModeller::SetProgram(const string& vsh, const string& fsh)
{
	mat->SetProgram(vsh,fsh);
}
void CityModeller::HandleKeyInput(GLFWwindow *window, int key, int scancode, int action, int mods){
    
}
void CityModeller::SetWindow(GLFWwindow *window){
    this->window=window;
}
void CityModeller::Render(RenderTarget *target){
    target->Bind();
    Render();
}
void CityModeller::Render()
{
	//press 'L' to turn light effect on and off
	if (glfwGetKey(window,GLFW_KEY_L) == GLFW_PRESS&&glfwGetKey(window,GLFW_KEY_LEFT_CONTROL) != GLFW_PRESS&&glfwGetKey(window,GLFW_KEY_RIGHT_CONTROL) != GLFW_PRESS&&(glfwGetTime() - last_time_key_l_pressed)> 0.5)
	{
		last_time_key_l_pressed = glfwGetTime();
		key_l_pressed = !key_l_pressed;

		if (!key_l_pressed)
		{
			g_maskSurface->setAmbient(wolf::Color4(1, 1, 1, 1));
			g_light->setAmbient(wolf::Color4(1, 1, 1, 1));
		}
		else
		{
			g_maskSurface->setAmbient(wolf::Color4(0.5, 0.5, 0.5, 1));
			g_light->setAmbient(wolf::Color4(0.5, 0.5, 0.5, 1));
		}
	}
	//Press Ctrl+L to change rotate the light or not
	if (glfwGetKey(window,GLFW_KEY_RIGHT_CONTROL)==GLFW_PRESS||glfwGetKey(window,GLFW_KEY_LEFT_CONTROL)==GLFW_PRESS)
	{
		if (glfwGetKey(window,GLFW_KEY_L)==GLFW_PRESS && (glfwGetTime() - last_time_key_l_pressed) > 0.5)
		{
			last_time_key_l_pressed = glfwGetTime();
			rotate_light = !rotate_light;
		}
	}

	if (key_l_pressed)
	{
		if (rotate_light)
		{
			lightAngle += (double)TIME_ELAPSE_SPEED / 1000.0f;
		}
		g_light->rotate(lightAngle);

		//make the light's intensity decrease gradually
		float dir_light_vertical_direction = g_light->getDirection().y;
		float dir_light_decrease_factor = dir_light_vertical_direction;
		if (dir_light_vertical_direction < 0)
		{
			g_light->setDiffuse(wolf::Color4(-1.0*dir_light_decrease_factor, -1.0*dir_light_decrease_factor, -0.8*dir_light_decrease_factor, 1));
			g_light->setSpecular(wolf::Color4(-0.2*dir_light_decrease_factor, -0.2*dir_light_decrease_factor, -0.1*dir_light_decrease_factor, 1));
		}
		else
		{
			g_light->setDiffuse(wolf::Color4(0.0, 0.0, 0.0, 1));
			g_light->setSpecular(wolf::Color4(0.0, 0.0, 0.0, 1));
		}

		g_light->setDirection(glm::vec3(0.0f, sinf(lightAngle), cosf(lightAngle)));
	}
	glm::mat4 mProj = mainCamera->getProjectionMatrix();
	glm::mat4 mView = mainCamera->getViewMatrix();
	glm::mat4 mWorld = mProj*mView;

	// Bind Uniforms
	mat->SetUniform("WorldViewProj", mWorld);
	mat->SetUniform("ViewDir", glm::vec3(mainCamera->getViewDirection()));

	// Set the light parameters
	mat->SetUniform("LightAmbient", g_light->getAmbient());
	mat->SetUniform("LightDiffuse", g_light->getDiffuse());
	mat->SetUniform("LightSpecular", g_light->getSpecular());
	mat->SetUniform("LightDir", g_light->getDirection());

	// Set the surface parameters
	mat->SetUniform("MatAmbient", g_maskSurface->getAmbient());
	mat->SetUniform("MatDiffuse", g_maskSurface->getDiffuse());
	mat->SetUniform("MatSpecular", g_maskSurface->getSpecular());

	g_pDecl->Bind();
	mat->Apply();
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    glEnable(GL_DEPTH_TEST);

	glDrawArrays(GL_TRIANGLES, 0, city_vertices_data->size());
}



