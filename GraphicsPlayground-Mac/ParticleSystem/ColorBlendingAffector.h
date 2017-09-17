#include "Affector.h"

class ColorBlendingAffector :public Affector
{
private:
	float blend_speed;
public:
	ColorBlendingAffector();
	virtual ~ColorBlendingAffector();
	virtual void apply(float delta, particle* p);
	void setBlendSpeed(float speed);
};
