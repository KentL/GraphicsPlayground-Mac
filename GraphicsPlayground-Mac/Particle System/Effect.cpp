#include "Effect.h"
#include "Emitter.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "HelperFunction.h"
#include <string.h>



Effect::Effect(string filename)
{
	//store the folder path
	effect_folder = "";
	string file_name = filename;
	string path[50];
	string delimiter = "\\";
	int count = 0;
	int pos = 0;
	string token;
	while ((pos = file_name.find(delimiter)) != string::npos) {
		path[count] = file_name.substr(0, pos);
		count++;
		file_name.erase(0, pos + delimiter.length());
	}
	for (int i = 0; i < count; i++)
	{
		effect_folder += path[i] + "//";
	}

	//load file for effect and its emitters
	emitters = new vector<Emitter>();
	transform = mat4(1.0);
	loadFile(filename);
	
}

Effect::~Effect()
{
	for (int i = 0; i < emitters->size(); i++)
	{
		delete &emitters->at(i);
	}

	delete &transform;
}

void Effect::pause()
{
	for (int i = 0; i < emitters->size(); i++)
	{
		emitters->at(i).pause();
	}
}

void Effect::setTransform(const mat4& t_m)
{
	this->transform = t_m;
}

void Effect::start()
{
	for (int i = 0; i < emitters->size(); i++)
	{
		emitters->at(i).start();
	}
}

void Effect::stop()
{
	for (int i = 0; i < emitters->size(); i++)
	{
		emitters->at(i).stop();
	}
}

void Effect::update(float delta)
{
	for (int i = 0; i < emitters->size(); i++)
	{
		emitters->at(i).update(delta);
	}
}

void Effect::addEmitter(Emitter emitter)
{
	emitter.setEffect(this);
	this->emitters->push_back(emitter);
}

mat4 Effect::getTransform()
{
	return transform;
}

void Effect::loadFile(string file)
{


	TiXmlDocument doc(&file[0]);
	bool loadOkay = doc.LoadFile();
	if (!loadOkay) {
		printf("Could not load xml file %s. Error='%s'. Exiting.\n", file.c_str(), doc.ErrorDesc());
		exit(1);
	}
	TiXmlElement* root = doc.RootElement();
	this->position = helper::turnStrToVector_3D( root->ToElement()->Attribute("pos") );

	for (TiXmlNode* item = root->FirstChild("emitter"); item; item = item->NextSibling("emitter"))
	{
		emitter_filename.push_back(item->ToElement()->Attribute("file"));
		emitter_offsets.push_back(helper::turnStrToVector_3D(item->ToElement()->Attribute("offset")));
		emitters->push_back(Emitter());
	}
	for (int i = 0; i < emitters->size(); i++)
	{
		emitters->at(i).loadFile(effect_folder + emitter_filename.at(i) + ".xml");
		emitters->at(i).setPosition(this->position+emitter_offsets.at(i));
		emitters->at(i).setEffect(this);
	}
}

void Effect::setPosition(vec3 pos)
{
	this->position = pos;
}

vec3 Effect::getPosition()
{
	return position;
}

void Effect::setCamera(Camera* camera)
{
	this->camera = camera;
	for (int i = 0; i < emitters->size(); i++)
	{
		emitters->at(i).setCamera(camera);
	}
}

void Effect::render()
{
	for (int i = 0; i < emitters->size(); i++)
	{
		emitters->at(i).render();
	}
}

