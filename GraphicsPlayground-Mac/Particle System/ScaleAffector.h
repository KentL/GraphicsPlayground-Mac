#include "Affector.h"

class ScaleAffector :public Affector
{
private:
	float scale_speed;
public:
	ScaleAffector();
	virtual ~ScaleAffector();
	virtual void apply(float delta, particle* p);
	void setScaleSpeed(float speed);
};
