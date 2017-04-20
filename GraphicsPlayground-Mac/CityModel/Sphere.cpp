
#include "Sphere.h"


Sphere::Sphere()
{
	
}

void Sphere::setProgram(const string& vShader, const string& fShader )
{
	mat->SetProgram(vShader,fShader);
}

Sphere::~Sphere()
{
}
