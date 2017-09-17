#include "Affector.h"

class FadeAffector :public Affector
{
private:
	float fade_speed;
public:
	FadeAffector();
	virtual ~FadeAffector();
	void apply(float delta, particle* p);
	void setFadeSpeed(int speed);
};
