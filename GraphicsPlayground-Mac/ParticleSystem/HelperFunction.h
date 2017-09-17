#ifndef HELPERFUNCTION
#define HELPERFUNCTION

#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "W_Common.h"
#include <struct.h>
#include "Effect.h"

class Emitter;
using namespace std;
using namespace glm;

namespace helper
{
	vec3 turnStrToVector_3D(const string& value);
	vec4 turnStrToVector_4D(const string& value);
	vec3 getRandomVector_3D(vec3 min, vec3 max);
	vec4 getRandomVector_4D(vec4 min, vec4 max);
	float getRandomNumber(const string& min, const string& max);
	float turnStrToNum(const string& value);
	vec4 vectorTo4D(vec3 vec);
	spawn_type turnStringToSpawnType(const string& spawntype);
	emitter_type turnStringToEmitterType(const string& emittertype);
	spawn_property_name turnStringToSpwnPrptyName(const string& name);
	spawn_property_type turnStringToSpwnPrptyType(const string& type);
	GLenum turnStringToBlendingMode(string mode_string);
}

#endif // !HELPERFUNCTION
