#include "stdafx.h"
#include "AABBCollider.h"

namespace Colliders
{
	/*
	AABB MODLE:		  				 ??y+
	___________ _____				 |
	|\         \   ??                 |
	| \         \ Width      ?Iz+    |
	|  \_________\_??___        ?I    |
	|  | <length>|----           ?I  |
	|  |         |hei-             ?I|---------------->x+
	 \ |         |ght
	  \|_________|----
	*/
	#pragma region "Public Methods"
	AABBCollider::AABBCollider()
	{
	}
	AABBCollider::AABBCollider(vec3 pos){ position = pos; dirty = true; }
	AABBCollider::AABBCollider(double width, double length, double height){ this->length = length; this->width = width; this->height = height; dirty = true; }
	AABBCollider::AABBCollider(vec3 pos, double width, double length, double height){ position = pos; this->width = width; this->length = length; this->height = height; dirty = true; }
	AABBCollider::~AABBCollider()
	{
		if (planeConstructed)
		{
			delete front;
			delete back;
			delete left;
			delete right;
			delete top;
			delete bottom;
		}
	}

	//Setters
	void AABBCollider::SetLength(double length){ this->length = length; dirty = true; }
	void AABBCollider::SetWidth(double width){ this->width = width; dirty = true; }
	void AABBCollider::SetHeight(double height){ this->height = height; dirty = true; }
	
	//Getters
	double* AABBCollider::GetSize() const { double size[] = { width, length, height }; return size; }
	double  AABBCollider::GetWidth() const { return width; }
	double  AABBCollider::GetLength() const { return length; }
	double  AABBCollider::GetHeight() const { return height; }
	void  AABBCollider::GetPlanes(Plane** p_array)
	{ 
		if (dirty)
		{
			CalculatePlanes();
		}
		p_array[0] = front;
		p_array[1] = back;
		p_array[2] = left;
		p_array[3] = right;
		p_array[4] = top;
		p_array[5] = bottom;
	}
	Plane* AABBCollider::GetFrontPlane()
	{
		if (dirty)
		{
			CalculatePlanes();
		}
		return front;
	}
	Plane* AABBCollider::GetBackPlane()
	{
		if (dirty)
		{
			CalculatePlanes();
		}
		return back;
	}
	Plane* AABBCollider::GetLeftPlane()
	{
		if (dirty)
		{
			CalculatePlanes();
		}
		return left;
	}
	Plane* AABBCollider::GetRightPlane()
	{
		if (dirty)
		{
			CalculatePlanes();
		}
		return right;
	}
	Plane* AABBCollider::GetTopPlane()
	{
		if (dirty)
		{
			CalculatePlanes();
		}
		return top;
	}
	Plane* AABBCollider::GetBottomPlane()
	{
		if (dirty)
		{
			CalculatePlanes();
		}
		return bottom;
	}
	#pragma endregion
	
#pragma region "Private Methods"
	void AABBCollider::CalculatePlanes()
	{
		 front = new Plane(vec3(0,0,-1),position.z-width/2);
		 back = new Plane(vec3(0, 0, 1), position.z + width / 2);
		 left = new Plane(vec3(-1, 0, 0), position.x - length / 2);
		 right = new Plane(vec3(1, 0, 0), position.x + length / 2);
		 top = new Plane(vec3(0, 1, 0), position.y + height / 2);
		 bottom = new Plane(vec3(0, -1, 0), position.y - height / 2);

		 planeConstructed = true;
	}
}
