#ifndef EFFECT
#define EFFECT
#include "Emitter.h"
#include "Node.h"
#include <vector>
#include "Camera.h"

using namespace std;

class Effect 
{
private:
	vector<Emitter>* emitters;
	mat4 transform;
	vector<vec3> emitter_offsets;
	vector<string>emitter_filename;
	vec3 position;
	Camera* camera;
	string effect_folder;
	void loadFile(string filename);

public:
	Effect(string filename);
	~Effect();

	void start();
	void pause();
	void stop();
	void render();
	void update(float delta);
	void setTransform(const mat4& t_m);
	mat4 getTransform();
	void addEmitter(Emitter emitter);
	void setPosition(vec3 pos);
	vec3 getPosition();
	void setCamera(Camera* camera);
	
};

#endif
