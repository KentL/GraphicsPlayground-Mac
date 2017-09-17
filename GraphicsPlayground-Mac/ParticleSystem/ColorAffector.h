#include "Affector.h"

class ColorAffector :public Affector
{
private:
	float r_speed;
	float g_speed;
	float b_speed;
public:
	ColorAffector();
	virtual ~ColorAffector();
	virtual void apply(float delta, particle* p);
	void setColorChangeSpeed(vec3 speed);
};
