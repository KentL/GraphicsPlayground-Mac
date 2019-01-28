#ifndef AABBCOLLIDER
#define AABBCOLLIDER
#include "Collider.h"
#include "Plane.h"

using namespace Geometry;

namespace Colliders
{
	class AABBCollider :public Collider
	{

		/*
		AABB MODEL:		  				 ��y+
		___________ _____				 |
		|\         \   ��                 |
		| \         \ Width      �Iz+    |
		|  \_________\_��___        �I    |
		|  | <length>|----           �I  |
		|  |         |hei-             �I|---------------->x+
		 \ |         |ght
		  \|_________|----
		*/

	protected:
		//size data
		double length;
		double width;
		double height;

		//Planes
		Plane* front;//Front Plane, Whose normal is (0,0,-1)
		Plane* back;//Back Plane, Whose normal is (0,0,1)
		Plane* left;//Left Plane, Whose normal is (-1,0,0)
		Plane* right;//Right Plane, Whose normal is (1,0,0)
		Plane* top;//Top Plane, Whose normal is (0,1,0)
		Plane* bottom;//Bottom Plane, Whose normal is (0,-1,0)

		//Flags
		bool dirty=true;
		bool planeConstructed = false;
		ColliderType collider_type = AABB;

	public:
		AABBCollider();
		AABBCollider(vec3 pos);
		///<summary>
		///Create an AABBCollider object initialized with width(along x axis),length(along z axis),height(along y axis)
		///</summary>
		AABBCollider(double width, double length, double height);
		///<summary>
		///Create an AABBCollider object initialized with position,width(along z axis),length(along x axis),height(along y axis)
		///</summary>
		AABBCollider(vec3 pos, double width, double length, double height);
		~AABBCollider();

		//Setters
		void SetLength(double length);
		void SetWidth(double width);
		void SetHeight(double height);
		
		//Getters
		double* GetSize() const;
		double  GetWidth()  const;
		double  GetLength() const;
		double  GetHeight() const;
		///<summary>
		///This function return an array of the pointers to the Plane objects in the AABB object.
		///Return: {front,back,left,right,top,bottom}
		///</summary>
		void GetPlanes(Plane** p_array) ;

		Plane* GetFrontPlane();
		Plane* GetBackPlane();
		Plane* GetLeftPlane();
		Plane* GetRightPlane();
		Plane* GetTopPlane();
		Plane* GetBottomPlane();

	private:
		void CalculatePlanes();
	};
}
#endif
