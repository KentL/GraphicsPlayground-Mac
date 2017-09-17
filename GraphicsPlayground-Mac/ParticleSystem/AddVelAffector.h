#include "Affector.h"

class AddVelAffector :public Affector
{
private:
	glm::vec3 accelerate_speed;
	glm::vec3 speed_difference;
public:
	AddVelAffector();
	virtual ~AddVelAffector();
	void apply(float delta, particle* p);
	void setAccSpeed(glm::vec3 speed);
	void setSpeedDifference(glm::vec3 difference);
};
