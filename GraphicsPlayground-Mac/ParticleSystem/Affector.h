#ifndef AFFECTOR
#define AFFECTOR
#include "ParticleStruct.h"
#include "stdafx.h"

class Affector
{
protected:
	std::string mode;
	std::string start;
	std::string end;
	float duration;
	float end_time;
	float start_time;

public:
    Affector(){};
    virtual ~Affector(){};
    virtual void apply(float delta,particle* p){};
	void setStart(const std::string& start){ this->start = start; }
	void setEnd(const std::string& end){ this->end = end; }
	void setDuration(float duration){ this->duration = duration; }
	void setMode(const std::string& mode){ this->mode = mode; }
	void setStartTime(float start_t){ start_time = start_t; }
	void setEndTime(float end_t){ end_time = end_t; }
};

#endif
