
#include "FormatTranslator.h"


vec2 FormatTranslator::turnStrToVector_2D(const string& value)
{
	int x, y;
	string delimiter = ",";
	string vec = value;
	int pos = 0;

	pos = vec.find(delimiter);
	x = atoi(vec.substr(0, pos).c_str());
	vec.erase(0, pos + delimiter.length());
	pos = vec.find(delimiter);
	y = atoi(vec.substr(0, pos).c_str());

	return vec2(x, y);
}

