#include <EnvMappedTransparentSphere.hpp>




Geometry::EnvMappedTransparentSphere::~EnvMappedTransparentSphere() {
	this->sphereVertices->clear();
	delete this->sphereVertices;
}
Geometry::EnvMappedTransparentSphere::EnvMappedTransparentSphere(string name,float accurity, const string* textures) :EnvMappedSphere(name,accurity, textures) {}




