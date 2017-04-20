//collide test 
#ifdef COMPILE
#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <stdio.h>
#include <stdlib.h>
#ifndef __APPLE__
#include <GL/glew.h>
#endif
#include <GL/glfw.h>
#include "W_Common.h"
#include "W_BufferManager.h"
#include "W_VertexDeclaration.h"
#include "W_ProgramManager.h"
#include "assignment2\week5\examples.h"
#include "loadtobuffer.h"
#include "Vector3D.h"



extern float xi,yi,zi;
extern float lookatx, lookaty, lookatz;
extern float markx, marky, markz;
extern float total_increasment, xincreasment, yincreasment, zincreasment;
extern  std::vector<Vertex2> buildings;
extern  std::vector<Vertex2> roads;
extern  std::vector<building> buildingStore;

float productnew=0, productold=0;
float productnew1[] = { 0, 0, 0, 0, 0 };
float productold1[] = { 0, 0, 0, 0, 0 };
float productnew2 = 0, productold2 = 0;
float  height, rate, projincreament;
bool  firstcall=true;
std::vector<double> anglenew;
std::vector<double> angleold;

struct vector
{
	float vecx, vecy, vecz;
};

//collide test for ground
void collidetest()
{
	Vector3D edge1, edge2, norm, tstvec, unit, proj,sightvector,motionvector;
	// get two vectors from the ground
	edge1.x = plane[0].x - plane[1].x;
	edge1.y = plane[0].y - plane[1].y;
	edge1.z = plane[0].z - plane[1].z;

	edge2.x = plane[1].x - plane[2].x;
	edge2.y = plane[1].y - plane[2].y;
	edge2.z = plane[1].z - plane[2].z;

	// cross them to get a normal
	norm = edge1.cross(edge2);

	sightvector = { lookatx, lookaty, lookatz };
	motionvector = { xincreasment, yincreasment, zincreasment };

	// this test vector points from current position to one point on the ground
	tstvec.x = 10;
	tstvec.y = -yi ;
	tstvec.z = 10;

	norm.normalize();
	
	productold = productnew;//store the previous product to compare with the new one
	productnew = fabs(tstvec*norm)/100;// test vector dot normal to get new product
	
	if (productnew<1.0 && (productnew - productold<0.05))//if new product is too small and product new< previous one showing that it's approaching the face
	{
		//printf("productnew:%f\nproductold:%f\nnew-old:%f\n", productnew,productold,productnew-productold);
		double  height;
		
		unit = norm.normal();// make its size to 1
		height = unit*motionvector;
		unit = unit*height;

	
		//project motion vector to the surface
		proj = motionvector - unit;
		xincreasment = proj.x;
		yincreasment = proj.y;
		zincreasment = proj.z;

		xi = markx + xincreasment;
		yi = marky + yincreasment;
		zi = markz + zincreasment;
		
	}

	
	






}

void collidetest2()
{
	Vector3D edge1, edge2, norm, tstvec, unit, proj, sightvector, motionvector;
	// get two vectors from the building surface
	edge1.x = buildings[0].x - buildings[1].x;
	edge1.y = buildings[0].y - buildings[1].y;
	edge1.z = buildings[0].z - buildings[1].z;

	edge2.x = buildings[1].x - buildings[2].x;
	edge2.y = buildings[1].y - buildings[2].y;
	edge2.z = buildings[1].z - buildings[2].z;

	// cross them to get a normal
	norm = Vector3D(buildings[0].normalx, buildings[0].normaly, buildings[0].normalz);

	motionvector = { xincreasment, yincreasment, zincreasment };

	// this test vector points from current position to one point on the surface
	tstvec.x = xi - buildings[0].x;
	tstvec.y = yi-  buildings[0].y;
	tstvec.z = zi - buildings[0].z;

	tstvec.normalize();
	

	productold = productnew;//store the previous product to compare with the new one
	productnew = fabs(tstvec*norm);// test vector dot normal to get new product

	if (productnew<0.5 && (productnew - productold<0.05))//if new product is too small and product new< previous one showing that it's approaching the face
	{
		printf("productnew:%f\nproductold:%f\nnew-old:%f\n", productnew,productold,productnew-productold);
		double  height;

		unit = norm.normal();// make its size to 1
		height = unit*motionvector;
		unit = unit*height;


		//project motion vector to the surface
		proj = motionvector - unit;
		xincreasment = proj.x;
		yincreasment = proj.y;
		zincreasment = proj.z;



		xi = markx + xincreasment;
		yi = marky + yincreasment;
		zi = markz + zincreasment;

	}
}




















//collide test for buildings

// Use the principle that when object is closer to the face,the sum of angle it forms with everycorner is closer to 360 degree,when
// it is on the surface, it reach to max:360
/*
void collidetest2()
{
	Vector3D vec_conera, vec_conerb, vec_conerc, vec_conerd;
	Vector3D vector1, vector2, vector3, vector4;
	Vector3D currentpos = Vector3D(xi, yi, zi);
	Vector3D norm,norm2,unit,edge1,edge2,sightvector,proj,motionvector;
	float cos1, cos2, cos3, cos4;

	if (firstcall)
	{
		for (int i = 0; i < 5 * buildingStore.size(); i++)
		{
			anglenew.push_back(0);
			angleold.push_back(0);
		}
		firstcall = false;
	}

	//test face 
	{   for (int i = 0; i < 5 * buildingStore.size(); i++)
	{

		//get every corner's vector
		vec_conera = Vector3D(buildings[i * 5].x, buildings[i * 5].y, buildings[i * 5].z);
		vec_conerb = Vector3D(buildings[i * 5 + 1].x, buildings[i *5 + 1].y, buildings[i * 5 + 1].z);
		vec_conerc = Vector3D(buildings[i * 5 + 2].x, buildings[i * 5 + 2].y, buildings[i * 5 + 2].z);
		vec_conerd = Vector3D(buildings[i * 5 + 5].x, buildings[i * 5 + 5].y, buildings[i * 5 + 5].z);
		// get vectors that point from corner to current position
		vector1 = vec_conera - currentpos;
		vector2 = vec_conerb - currentpos;
		vector3 = vec_conerc - currentpos;
		vector4 = vec_conerd - currentpos;
		//get the cos between each near-by vector 
		cos1 = (vector1*vector2) / (vector1.mag()*vector2.mag());
		cos2 = (vector1*vector4) / (vector1.mag()*vector4.mag());
		cos3 = (vector3*vector2) / (vector3.mag()*vector2.mag());
		cos4 = (vector3*vector4) / (vector3.mag()*vector4.mag());
		//two vectors that are on the surface
		edge1 = vec_conera - vec_conerb;
		edge2 = vec_conera - vec_conerc;

	
		//store the previous angle to compare with the new one
		angleold[i] = anglenew[i];
		anglenew[i] = acos(cos1) + acos(cos2) + acos(cos3) + acos(cos4);
		sightvector = Vector3D(lookatx, lookaty, lookatz);
		motionvector = Vector3D(xincreasment, yincreasment, zincreasment);
		
		if (2 * PI - anglenew[0] < 1.0 && (angleold[0] - anglenew[0] )< 0.0)
		{
			//for (int mm = 0; mm < 5; mm++)
			{
				//printf("%f   %f\n", anglenew[0], angleold[0]);
			}
			//printf("oldxincreasment:%f  oldyincreasment:%f  oldzincreasment:%f\n", xincreasment, yincreasment, zincreasment);
			unit = Vector3D(buildings[i].normalx, buildings[i].normaly, buildings[i].normalz);
			float b = unit.mag();//just test

			height = fabs(unit*motionvector);

			unit = unit*height;
			proj = motionvector + unit;

			xincreasment = proj.x;
			yincreasment = proj.y;
			zincreasment = proj.z;
			
			xi = markx + xincreasment;
			yi = marky + yincreasment;
			zi = markz + zincreasment;
			//printf("xincreasment:%f  yincreasment:%f  zincreasment:%f\n", xincreasment,yincreasment,zincreasment);
			//printf("%f  %f  %f\n", xi, yi, zi);
		}
	}



	}
	}
	
	*/
#endif