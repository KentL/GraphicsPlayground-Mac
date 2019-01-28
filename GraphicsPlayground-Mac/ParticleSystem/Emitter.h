#ifndef EMITTER
#define EMITTER
#include <struct.h>
#include "W_VertexDeclaration.h"
#include "W_Program.h"
#include "Camera.h"
#include "Affector.h"

class Effect;

enum emitter_type
{
	point_emitter,
	box_emitter,
	sphere_emitter
	
};

enum spawn_type
{
	continuous,
	burst
};

enum spawning_state
{
	spawning,stopped,paused
};

class Emitter
{
public:
	Emitter();
	~Emitter();

	void start();
	void pause();
	void stop();
	void update(float delta);
	void setEffect(Effect* e);
	void spawnParticle();
	void loadFile(const string& filename);
	void render();
	void setOff_set(vec3 offset);
	vec3 getOff_set();
	void setCamera(Camera* camera);
	void setShaderProgram(const string& vertex_shader, const string& pixel_shader);
	void setPosition(vec3 pos);

private:
	Effect* effect;
	particle* freelist;
	particle* active_head;
	particle* active_tail;
	vector<spawn_property> sp_Properties;
	vector<Affector*> m_affectorList;
	Vertex* vertices_buffer;
	int particleAmount;
	float duration;
	float m_emitter_age;
	int birthrate;
	float start_time;
	string name;
	spawning_state spawn_state;
	particle* pool;
	emitter_type m_emitter_type;
	spawn_type m_spawn_type;
	vec3 position;
	vec3 m_emitterBoxMin, m_emitterBoxMax;
	
	wolf::VertexBuffer* VertexBuffer;
	wolf::VertexDeclaration* Decl;
	wolf::Program* g_pProgram ;
	GLuint tex;
	GLenum sfactor, dfactor;

	vec3 offset;
	Camera* camera;

private:
	void addToFree(particle* p);
	void addToActive(particle* p);
	particle* getParticleFromFree();
	particle* getParticleFromActive();
	void killParticle(particle* p );
	
	
	
};

#endif
