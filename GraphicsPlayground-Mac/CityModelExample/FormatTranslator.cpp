
#include "FormatTranslator.h"


glm::vec2 FormatTranslator::turnStrToVector_2D(const std::string& value)
{
	int x, y;
	std::string delimiter = ",";
	std::string vec = value;
	int pos = 0;

	pos = vec.find(delimiter);
	x = atoi(vec.substr(0, pos).c_str());
	vec.erase(0, pos + delimiter.length());
	pos = vec.find(delimiter);
	y = atoi(vec.substr(0, pos).c_str());

    return glm::vec2(x, y);
}

