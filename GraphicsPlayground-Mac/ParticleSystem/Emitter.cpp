#include "Emitter.h"
#include "Affector.h"
#include <string.h>
#include <time.h>
#include "HelperFunction.h"
#include "W_BufferManager.h"
#include "W_ProgramManager.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "HelperFunction.h"
#include "AddVelAffector.h"
#include "ScaleAffector.h"
#include "ColorAffector.h"
#include "FadeAffector.h"
#include "ColorBlendingAffector.h"
#include "SOIL.h"

#define BIRTH_MULTI_FACTOR 100
#define SIZE_MULTI_FACTOR 0.1
#define VEL_MULTI_FACTOR 0.05f
#define LIFETIME_SCALE_FACTOR 0.1


class Effect;
using namespace helper;

Emitter::Emitter()
{
	freelist = new particle();
	active_head = new particle();
	active_tail = new particle();
	freelist->prev = NULL;
	freelist->next = NULL;
	active_head->prev = NULL;
	active_head->next = active_tail;
	active_tail->next = NULL;
	active_tail->prev = active_head;
	spawn_state = stopped;
	m_emitter_age = 0;
}

Emitter::~Emitter()
{
	while (freelist->next != NULL)
	{
		particle* temp = freelist->next;
		freelist->next = temp->next;
		temp->next->prev = freelist;
		delete temp;
	}
	while (active_head->next != active_tail)
	{
		particle* temp = active_head->next;
		active_head->next = temp->next;
		temp->next->prev = active_head;
		delete temp;
	}
	for (int i = 0; i < sp_Properties.size(); i++)
	{
		delete &sp_Properties.at(i);
	}
	for (int i = 0; i < m_affectorList.size(); i++)
	{
		delete &m_affectorList.at(i);
	}
	
	sp_Properties.clear();
	m_affectorList.clear();

}

void Emitter::addToFree(particle*p)
{
	p->next = freelist->next;
	p->prev = freelist;
	if (freelist->next!=NULL)
	{
		freelist->next->prev = p;
	}
	freelist->next = p;
}

void Emitter::addToActive(particle*p)
{
	p->next = active_head->next;
	p->prev = active_head;
	active_head->next->prev = p;
	active_head->next = p;
}

particle* Emitter::getParticleFromFree()
{
	if (freelist->next!=0)
	{
		particle* temp = freelist->next;
		if (temp->next!=NULL)
		{
			temp->next->prev = freelist;
		}
		freelist->next = temp->next;
		return temp;
	}
	else
	{
		particle* temp = getParticleFromActive();
		return temp;
	}
}

particle* Emitter::getParticleFromActive()
{
	if (active_tail->prev!=active_head)
	{
		particle* temp = active_tail->prev;
		temp->prev->next = active_tail;
		active_tail->prev = temp->prev;
		return temp;
	}
	else
	{
		printf("no elements in free nor active list");
        return NULL;
	}
}

void Emitter::spawnParticle()
{
	particle* p = getParticleFromFree();
	addToActive(p);
	p->age = 0;
	p->m_pAffector.clear();
	p->m_emitter = this;
	p->position = vec3(0, 0, 0);

	for (int i = 0; i < sp_Properties.size(); i++)
	{
		spawn_property prpty = sp_Properties.at(i);
		switch (prpty.name)
		{
		case velocity:
			switch (prpty.type)
			{
			case randomType:
			{
				vec3 vecMin = turnStrToVector_3D(prpty.min);
				vec3 vecMax = turnStrToVector_3D(prpty.max);
				p->velocity = getRandomVector_3D(vecMin, vecMax);
				break;
			}
			case constantType:
			{
				p->velocity = turnStrToVector_3D(prpty.value);
			}
			}
			break;
		case size:
			switch (prpty.type)
			{
			case randomType:
				p->size = getRandomNumber(prpty.min, prpty.max);
				break;
			case constantType:
				p->size = turnStrToNum(prpty.value);
			}
			break;
		case color:
			switch (prpty.type)
			{
			case randomType:
			{
				vec4 vecMin = turnStrToVector_4D(prpty.min);
				vec4 vecMax = turnStrToVector_4D(prpty.max);
				p->color = getRandomVector_4D(vecMin, vecMax);
				break;
			}
			case constantType:
			{
				p->color = turnStrToVector_4D(prpty.value);
			}
			}
			break;
		case fade:
			switch (prpty.type)
			{
			case randomType:
				p->fade = getRandomNumber(prpty.min, prpty.max);
				break;
			case constantType:
				p->fade = turnStrToNum(prpty.value);
			}
			break;
		case lifetime:
			switch (prpty.type)
			{
			case randomType:
				p->lifetime = getRandomNumber(prpty.min, prpty.max)*LIFETIME_SCALE_FACTOR;
				break;
			case constantType:
				p->lifetime = turnStrToNum(prpty.value)*LIFETIME_SCALE_FACTOR;
			}
			break;
		case box_max:
			switch (prpty.type)
			{
			case randomType:
				m_emitterBoxMax = getRandomVector_3D(turnStrToVector_3D(prpty.min), turnStrToVector_3D(prpty.max));
				break;
			case constantType:
				m_emitterBoxMax = turnStrToVector_3D(prpty.value);
			}
			break;
		case box_min:
			switch (prpty.type)
			{
			case randomType:
				m_emitterBoxMin = getRandomVector_3D(turnStrToVector_3D(prpty.min), turnStrToVector_3D(prpty.max));
				break;
			case constantType:
				m_emitterBoxMin = turnStrToVector_3D(prpty.value);
			}
			break;
		}
	}

	if (emitter_type == point_emitter)
	{
		p->position = this->position;
	}
	else if (emitter_type == box_emitter)
	{
		p->position = this->position+getRandomVector_3D(m_emitterBoxMin, m_emitterBoxMax);
	}

	for (int i = 0; i < m_affectorList.size(); i++)
	{
		p->m_pAffector.push_back(m_affectorList.at(i));
	}
}

void Emitter::update(float delta)
{
	m_emitter_age += delta;
	if (m_emitter_age > duration+start_time)
	{
		spawn_state = stopped;
	}

	if (spawn_state == spawning&&m_emitter_age > start_time)
	{
		if (spawn_type == continuous)
		{
			for (int i = 0; i < (int)(birthrate*delta*BIRTH_MULTI_FACTOR); i++)
			{
				spawnParticle();
			}
		}
	}
	particle* p = active_head->next;
	int count = 0;
	while (p != active_tail)
	{
		
		p->age += delta;
		float age1 = p->age;
		p->position += p->velocity*VEL_MULTI_FACTOR;
		

		if (p->age > p->lifetime)
		{
			particle* temp = p->next;
			killParticle(p);
			p = temp;
		}
		else
		{
			for (int j = 0; j < p->m_pAffector.size(); j++)
			{
				p->m_pAffector.at(j)->apply(delta, p);
			}
			p = p->next;
		}
		
	}

}

void Emitter::start()
{
	spawn_state = spawning;
}

void Emitter::pause()
{
	spawn_state = paused;
}

void Emitter::stop()
{
	spawn_state = stopped;
}

void Emitter::setPosition(vec3 pos)
{
	this->position = pos;
}

void Emitter::render()
{
	vec4 standard_particle_vertex[4];
	vec4 rotated_particle_vertex[4];

	mat4 cam_rot = camera->getRotationMatrix();

	int index = 0;
	particle* p = active_head->next;

	while (p!=active_tail)
	{
		Vertex vertex1, vertex2, vertex3, vertex4;
		double size = p->size*SIZE_MULTI_FACTOR;

		standard_particle_vertex[0] = vec4(-size / 2, +size / 2, 0, 1);
		standard_particle_vertex[1] = vec4(+size / 2, +size / 2, 0, 1);
		standard_particle_vertex[2] = vec4(-size / 2, -size / 2, 0, 1);
		standard_particle_vertex[3] = vec4(+size / 2, -size / 2, 0, 1);

		rotated_particle_vertex[0] = cam_rot * standard_particle_vertex[0];
		rotated_particle_vertex[1] = cam_rot * standard_particle_vertex[1];
		rotated_particle_vertex[2] = cam_rot * standard_particle_vertex[2];
		rotated_particle_vertex[3] = cam_rot * standard_particle_vertex[3];

		vertex1.x = p->position.x + rotated_particle_vertex[0].x;
		vertex1.y = p->position.y + rotated_particle_vertex[0].y;
		vertex1.z = p->position.z + rotated_particle_vertex[0].z;
		vertex1.r = p->color.r;
		vertex1.g = p->color.g;
		vertex1.b = p->color.b;
		vertex1.a = p->color.a;
		vertex1.u = 0.0;
		vertex1.v = 0.0;

		vertex2.x = p->position.x + rotated_particle_vertex[1].x;
		vertex2.y = p->position.y + rotated_particle_vertex[1].y;
		vertex2.z = p->position.z + rotated_particle_vertex[1].z;
		vertex2.r = p->color.r;
		vertex2.g = p->color.g;
		vertex2.b = p->color.b;
		vertex2.a = p->color.a;
		vertex2.u = 1.0;
		vertex2.v = 0.0;

		vertex3.x = p->position.x + rotated_particle_vertex[2].x;
		vertex3.y = p->position.y + rotated_particle_vertex[2].y;
		vertex3.z = p->position.z + rotated_particle_vertex[2].z;
		vertex3.r = p->color.r;
		vertex3.g = p->color.g;
		vertex3.b = p->color.b;
		vertex3.a = p->color.a;
		vertex3.u = 0.0;
		vertex3.v = 1.0;

		vertex4.x = p->position.x + rotated_particle_vertex[3].x;
		vertex4.y = p->position.y + rotated_particle_vertex[3].y;
		vertex4.z = p->position.z + rotated_particle_vertex[3].z;
		vertex4.r = p->color.r;
		vertex4.g = p->color.g;
		vertex4.b = p->color.b;
		vertex4.a = p->color.a;
		vertex4.u = 1.0;
		vertex4.v = 1.0;

		vertices_buffer[index * 6 + 0] = vertex1;
		vertices_buffer[index * 6 + 1] = vertex2;
		vertices_buffer[index * 6 + 2] = vertex3;
		vertices_buffer[index * 6 + 3] = vertex2;
		vertices_buffer[index * 6 + 4] = vertex3;
		vertices_buffer[index * 6 + 5] = vertex4;

		index++;

		p = p->next;
	}
	
	if (active_head->next!=active_tail)
	{
		VertexBuffer->Write(&vertices_buffer[0]);
		glm::mat4 mProj = camera->getProjectionMatrix();
		glm::mat4 mView = camera->getViewMatrix();
		glm::mat4 mWorld = mProj*mView;
		glBlendFunc(sfactor, dfactor);

		g_pProgram->Bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);

		g_pProgram->SetUniform("world", mWorld);
		g_pProgram->SetUniform("texture1", 0);

		Decl->Bind();

		glDrawArrays(GL_TRIANGLES, 0, index*6);
	}

}

void Emitter::setShaderProgram(const string& vertex_shader, const string& pixel_shader)
{
	g_pProgram = wolf::ProgramManager::Inst()->CreateProgram(vertex_shader, pixel_shader);
}

void Emitter::loadFile(const string& filename)
{
	TiXmlDocument doc(&filename[0]);
	bool loadOkay = doc.LoadFile();
	if (!loadOkay)
	{
		printf("Could not load test file %s. Error='%s'. Exiting.\n", filename.c_str(), doc.ErrorDesc());
		exit(1);
	}
	TiXmlElement* root = doc.RootElement();
	this->name = root->Attribute("name");
	this->particleAmount = (int)turnStrToNum(root->Attribute("num_particles"));
	this->duration = turnStrToNum(root->Attribute("duration"));
	this->spawn_type = turnStringToSpawnType(root->Attribute("spawn_type"));
	this->emitter_type = turnStringToEmitterType(root->Attribute("emitter_type"));
	this->birthrate = (int)turnStrToNum(root->Attribute("birthrate"));
	this->start_time = turnStrToNum(root->Attribute("start_time"));

	pool = new particle[particleAmount];
	vertices_buffer = new Vertex[particleAmount * 6];

	VertexBuffer = wolf::BufferManager::Inst()->CreateVertexBuffer(particleAmount*sizeof(Vertex) * 6);

	Decl = new wolf::VertexDeclaration();
	Decl->Begin();
	Decl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
	Decl->AppendAttribute(wolf::AT_Color, 4, wolf::CT_Float);
	Decl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
	Decl->SetVertexBuffer(VertexBuffer);
	Decl->End();

	for (int i = 0; i < particleAmount; i++)
	{
		addToFree(&pool[i]);
	}
	for (TiXmlNode* spwn_property = root->FirstChild("spawn_property"); spwn_property; spwn_property = spwn_property->NextSibling("spawn_property"))
	{
		spawn_property_name sp_prpt_name = turnStringToSpwnPrptyName(spwn_property->ToElement()->Attribute("name"));
		spawn_property_type sp_prpt_type = turnStringToSpwnPrptyType(spwn_property->ToElement()->Attribute("type"));
		string min = "", max = "", value = "";
		if (sp_prpt_type == randomType)
		{
			min = spwn_property->ToElement()->Attribute("min");
			max = spwn_property->ToElement()->Attribute("max");
		}
		else
		{
			value = spwn_property->ToElement()->Attribute("value");
		}

		this->sp_Properties.push_back({ sp_prpt_name, sp_prpt_type, value, max, min });
	}

	//set up texture
	
		if(TiXmlNode* texture = root->FirstChild("texture"))
		{
			string imgPath = texture->ToElement()->Attribute("file");

			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);

            int width, height,channels;
            unsigned char* image =
            SOIL_load_image(imgPath.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);
            
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1) ;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);


			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

	//set up shader
		TiXmlNode* shader = root->FirstChild("shader");
		string vsh = shader->ToElement()->Attribute("vertex_shader");
		string fsh = shader->ToElement()->Attribute("fragment_shader");
		this->setShaderProgram(vsh, fsh);

	//	set up blending
		TiXmlNode* blending = root->FirstChild("blending");
		string blend_bool = blending->ToElement()->Attribute("value");
		if (blend_bool=="true")
		{
			glEnable(GL_BLEND);
			string src = blending->ToElement()->Attribute("src");
			string dst = blending->ToElement()->Attribute("dst");
			sfactor = turnStringToBlendingMode(src);
			dfactor = turnStringToBlendingMode(dst);
		}

	//set up affector
	for (TiXmlNode* affector = root->FirstChild("affector"); affector; affector = affector->NextSibling("affector"))
	{
		string mode, start, end, start_time, end_time;
		string affector_type = affector->ToElement()->Attribute("type");

		for (TiXmlNode* prpt = affector->FirstChild("property"); prpt; prpt = prpt->NextSibling("property"))
		{
			string prpt_name = prpt->ToElement()->Attribute("name");

			if (prpt_name == "mode")
			{
				mode = prpt->ToElement()->Attribute("value");
				continue;
			}
			if (prpt_name == "start")
			{
				start = prpt->ToElement()->Attribute("value");
				continue;

			}
			if (prpt_name == "end")
			{
				end = prpt->ToElement()->Attribute("value");
				continue;

			}
			if (prpt_name == "start_time")
			{
				start_time = prpt->ToElement()->Attribute("value");
				continue;
			}
			if (prpt_name == "end_time")
			{
				end_time = prpt->ToElement()->Attribute("value");
				continue;
			}
		}

		if (affector_type == "add_vel")
		{
			AddVelAffector* temp_aff = new AddVelAffector();

			temp_aff->setMode(mode);
			temp_aff->setStart(start);
			temp_aff->setEnd(end);
			temp_aff->setSpeedDifference((turnStrToVector_3D(end) - turnStrToVector_3D(start)));
			if (mode != "over_life")
			{
				temp_aff->setStartTime(turnStrToNum(start_time));
				temp_aff->setEndTime(turnStrToNum(end_time));
			}
			this->m_affectorList.push_back(temp_aff);
			continue;
		}

		if (affector_type == "fade")
		{
			FadeAffector* temp_aff = new FadeAffector();

			temp_aff->setMode(mode);
			temp_aff->setStart(start);
			temp_aff->setEnd(end);
			if (mode != "over_life")
			{
				temp_aff->setStartTime(turnStrToNum(start_time));
				temp_aff->setEndTime(turnStrToNum(end_time));
			}
			this->m_affectorList.push_back(temp_aff);
			continue;
		}

		if (affector_type == "scale")
		{
			ScaleAffector* temp_aff = new ScaleAffector();

			temp_aff->setMode(mode);
			temp_aff->setStart(start);
			temp_aff->setEnd(end);
			if (mode != "over_life")
			{
				temp_aff->setStartTime(turnStrToNum(start_time));
				temp_aff->setEndTime(turnStrToNum(end_time));
			}

			this->m_affectorList.push_back(temp_aff);
			continue;
		}

		if (affector_type == "color")
		{
			ColorAffector* temp_aff = new ColorAffector();


			temp_aff->setMode(mode);
			temp_aff->setStart(start);
			temp_aff->setEnd(end);
			if (mode != "over_life")
			{
				temp_aff->setStartTime(turnStrToNum(start_time));
				temp_aff->setEndTime(turnStrToNum(end_time));
			}

			this->m_affectorList.push_back(temp_aff);
			continue;
		}

		if (affector_type == "blending")
		{
			ColorBlendingAffector *temp_aff = new ColorBlendingAffector();

			temp_aff->setMode(mode);
			temp_aff->setStart(start);
			temp_aff->setEnd(end);
			if (mode != "over_life")
			{
				temp_aff->setStartTime(turnStrToNum(start_time));
				temp_aff->setEndTime(turnStrToNum(end_time));
			}

			this->m_affectorList.push_back(temp_aff);
			continue;
		}
	}


}

void Emitter::setOff_set(vec3 offset)
{
	this->offset = offset;
}

vec3 Emitter::getOff_set()
{
	return offset;
}

void Emitter::setEffect(Effect* e)
{
	this->effect = e;
}

void Emitter::setCamera(Camera* camera)
{
	this->camera = camera;
}

void Emitter::killParticle(particle* p)
{
	p->next->prev=p->prev;
	p->prev->next = p->next;
	p->prev = freelist;
	p->next = freelist->next;
	freelist->next = p;
	if (p->next!=NULL)
	{
		p->next->prev = p;
	}
}
