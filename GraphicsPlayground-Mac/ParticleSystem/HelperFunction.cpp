#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"
#include <time.h>
#include "W_Common.h"
#include "HelperFunction.h"
#include "Emitter.h"


using namespace std;
using namespace glm;


vec3 helper::turnStrToVector_3D(const string& value)
	{
		int x, y, z;
		string delimiter = ",";
		string vec = value;
		int pos = 0;

		pos = vec.find(delimiter);
		x = atoi(vec.substr(0, pos).c_str());
		vec.erase(0, pos + delimiter.length());
		pos = vec.find(delimiter);
		y = atoi(vec.substr(0, pos).c_str());
		vec.erase(0, pos + delimiter.length());
		pos = vec.find(delimiter);
		z = atoi(vec.substr(0, pos).c_str());
		vec.erase(0, pos + delimiter.length());

		return vec3(x, y, z);
	}

vec4 helper::turnStrToVector_4D(const string& value)
	{
		int x, y, z, w;
		string delimiter = ",";
		string vec = value;
		int pos = 0;

		pos = vec.find(delimiter);
		x = atoi(vec.substr(0, pos).c_str());
		vec.erase(0, pos + delimiter.length());
		pos = vec.find(delimiter);
		y = atoi(vec.substr(0, pos).c_str());
		vec.erase(0, pos + delimiter.length());
		pos = vec.find(delimiter);
		z = atoi(vec.substr(0, pos).c_str());
		vec.erase(0, pos + delimiter.length());
		pos = vec.find(delimiter);
		w = atoi(vec.substr(0, pos).c_str());
		vec.erase(0, pos + delimiter.length());

		return vec4(x, y, z, w);
	}

vec3 helper::getRandomVector_3D(vec3 min, vec3 max)
	{
		vec3 vec;
		if (min.x == max.x)
		{
			vec.x = min.x;
		}
		else
		{
			vec.x = rand() % (int((max.x - min.x) * 100)) / 100.0f + min.x;
		}
		if (min.y == max.y)
		{
			vec.y = min.y;
		}
		else
		{
			vec.y = rand() % (int((max.y - min.y) * 100)) / 100.0f + min.y;
		}
		if (min.z == max.z)
		{
			vec.z = min.z;
		}
		else
		{
			vec.z = rand() % (int((max.z - min.z) * 100)) / 100.0f + min.z;
		}
		
		
		return vec;
	}
vec4 helper::getRandomVector_4D(vec4 min, vec4 max)
	{
		vec4 vec;

		if (min.x == max.x)
		{
			vec.x = min.x;
		}
		else
		{
			vec.x = rand() % (int((max.x - min.x) * 100))/100.0f + min.x;
		}
		if (min.y == max.y)
		{
			vec.y = min.y;
		}
		else
		{
			vec.y = rand() % (int((max.y - min.y) * 100)) / 100.0f + min.y;
		}
		if (min.z == max.z)
		{
			vec.z = min.z;
		}
		else
		{
			vec.z = rand() % (int((max.z - min.z) * 100)) / 100.0f + min.z;
		}
		if (vec.w == vec.w)
		{
			vec.w = min.w;
		}
		else
		{
			vec.w = rand() % (int((max.w - min.w) * 100)) / 100.0f + min.w;
		}

		return vec;
	}
float helper::getRandomNumber(const string& min, const string& max)
	{
		int _min, _max;
		_min = atoi(min.c_str());
		_max = atoi(max.c_str());

		return rand() % (_max - _min) + _min;
	}
float helper::turnStrToNum(const string& value)
	{
		return stof(value);
	}

vec4 helper::vectorTo4D(vec3 vec)
	{
		int x, y, z;
		x = vec.x;
		y = vec.y;
		z = vec.z;
		
		return vec4(x, y, z, 1);
	}

spawn_type helper::turnStringToSpawnType(const string& spawntype)
	{
		if (spawntype == "continuous")
		{
			return continuous;
		}
		if (spawntype == "burst")
		{
			return burst;
		}
        return burst;
	}

emitter_type helper::turnStringToEmitterType(const string& emittertype)
	{
		if (emittertype == "point_emitter")
		{
			return point_emitter;
		}

		if (emittertype == "box_emitter")
		{
			return box_emitter;
		}

		if (emittertype == "sphere_emitter")
		{
			return sphere_emitter;
		}
        return sphere_emitter;
	}

spawn_property_name helper::turnStringToSpwnPrptyName(const string& name)
	{
		if (name == "velocity")
		{
			return velocity;
		}
		if (name == "color")
		{
			return color;
		}
		if (name == "size")
		{
			return size;
		}
		if (name == "fade")
		{
			return fade;
		}
		if (name == "lifetime")
		{
			return lifetime;
		}
		if (name == "box_min")
		{
			return box_min;
		}
		if (name == "box_max")
		{
			return box_max;
		}
        return box_max;
	}

spawn_property_type helper::turnStringToSpwnPrptyType(const string& type)
	{
		if (type == "random")
		{
			return randomType;
		}

		if (type == "constant")
		{
			return constantType;
		}
        
        return constantType;
	}

GLenum helper::turnStringToBlendingMode(string mode_string)
{
	if (mode_string == "GL_SRC_ALPHA")
	{
		return GL_SRC_ALPHA;
	}
	if (mode_string == "GL_ONE")
	{
		return GL_ONE;
	}
	if (mode_string == "GL_SRC_COLOR")
	{
		return GL_SRC_COLOR;
	}
	if (mode_string == "GL_ONE_MINUS_SRC_COLOR")
	{
		return GL_ONE_MINUS_SRC_COLOR;
	}
	if (mode_string == "GL_ONE_MINUS_SRC_ALPHA")
	{
		return GL_ONE_MINUS_SRC_ALPHA;
	}
	if (mode_string == "GL_DST_ALPHA")
	{
		return GL_DST_ALPHA;
	}
	if (mode_string == "GL_ONE_MINUS_DST_ALPHA")
	{
		return GL_ONE_MINUS_DST_ALPHA;
	}
	if (mode_string == "GL_DST_COLOR")
	{
		return GL_DST_COLOR;
	}
	if (mode_string == "GL_ONE_MINUS_DST_COLOR")
	{
		return GL_ONE_MINUS_DST_COLOR;
	}
	if (mode_string == "GL_ZERO")
	{
		return GL_ZERO;
	}
    return GL_ZERO;
}
