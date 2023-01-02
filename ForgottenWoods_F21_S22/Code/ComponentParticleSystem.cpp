//------------------------------------------------------------------------------
/*!
\file	ComponentParticleSystem.cpp
\author	Zak (zak.s)
\par	Copyright © 2021 DigiPen (USA) Corporation.
\brief  Implementation for particle system
*/
//------------------------------------------------------------------------------
#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------
#include "ComponentParticleSystem.h"
#include "ComponentGraphics.h"
#include "GameObject.h"
#include "Trace.h"
#include <time.h>
#include <math.h>
#include "Transformation.h"
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
#define MAX_PARTICLES 100
#define MIN_PARTICLES 25
#define MAX_VELOCITY_X 5
#define MIN_VELOCITY_X 1
#define MAX_VELOCITY_Y 2
#define MIN_VELOCITY_Y 1
#define MAX_LIFETIME 100
#define MIN_LIFETIME 50
//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
//patterns
ParticlePattern PLAYER_WALK = {};
ParticlePattern ENEMY_WALK = {};
ParticlePattern TEST_PATTERN = {};
Stream particleStream;
ComponentGraphicPtr particleGraphic = 0;
ComponentSpritePtr particleMesh = 0;
//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
RandomGenerator random;
static char pathname[FILENAME_MAX] = "";
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
/***********************************************
 \brief     Particle System ctor
 \
 \@param shader - particle's shader
 ***********************************************/
ComponentParticleSystem::ComponentParticleSystem(Shader* shader)
{
	//arbitrary list size
	this->particle_list.resize(1000);
	random.SeedInit();
	this->is_alive = true;
	this->parent = NULL;
	mesh = new ComponentGraphic(0, 0, 0);
	sprite = new ComponentSprite();
	//basic color for now
	sprintf_s(pathname, _countof(pathname), "./TextFiles/particle.txt");
	particleStream = StreamOpen(pathname);
	sprite->ReadSprite(particleStream);
	mesh->SetSprite(sprite);
	mesh->SetIndices(sprite->GetIndecies());
	mesh->SetVertices(sprite->GetVertices());
	mesh->CreateSquare(0, 0, 0, particleStream, *shader);
	mesh->setPosFromFile(particleStream);
	//assign the system's mesh to each particle
	for (auto& particle : this->particle_list)
	{
		particle.mesh = this->mesh;
		particle.sprite = this->sprite;
	}
}

/***********************************************
 \brief     Particle System ctor with data from file
 \
 \@param shader - particle's shader
 \@param filename - data file
 ***********************************************/
ComponentParticleSystem::ComponentParticleSystem(Shader* shader, const char* filename)
{
	//arbitrary list size
	this->particle_list.resize(1000);
	random.SeedInit();
	this->is_alive = true;
	this->parent = NULL;
	mesh = new ComponentGraphic(0, 0, 0);
	sprite = new ComponentSprite();
	//basic color for now
	sprintf_s(pathname, _countof(pathname), filename);
	particleStream = StreamOpen(pathname);
	sprite->ReadSprite(particleStream);
	mesh->SetSprite(sprite);
	mesh->SetIndices(sprite->GetIndecies());
	mesh->SetVertices(sprite->GetVertices());
	mesh->CreateSquare(0, 0, 0, particleStream, *shader);
	mesh->setPosFromFile(particleStream);
	//assign the system's mesh to each particle
	for (auto& particle : this->particle_list)
	{
		particle.mesh = this->mesh;
		particle.sprite = this->sprite;
	}
}
/***********************************************
 \brief     Particle System ctor with data from parent GameObject
 \
 \@param shader - particle's shader
 \@param parent - parent game object
 ***********************************************/
ComponentParticleSystem::ComponentParticleSystem(GameObjectPtr parent, Shader* shader)
{
	//same as above, but ties position to the game object
	this->particle_list.resize(101);
	random.SeedInit();
	this->is_alive = true;
	this->parent = parent;
	this->parent = NULL;
	mesh = new ComponentGraphic(0, 0, 0);
	sprite = new ComponentSprite();
	sprintf_s(pathname, _countof(pathname), "./TextFiles/particle.txt");
	particleStream = StreamOpen(pathname);
	sprite->ReadSprite(particleStream);
	mesh->SetSprite(sprite);
	mesh->SetIndices(sprite->GetIndecies());
	mesh->SetVertices(sprite->GetVertices());
	mesh->CreateSquare(0, 0, 0, particleStream, *shader);
	mesh->setPosition(parent->GetTransform()->GetPosition()->x, parent->GetTransform()->GetPosition()->y);
	for (auto &particle : this->particle_list)
	{
		particle.mesh = this->mesh;
		particle.sprite = this->sprite;
	}
}
/***********************************************
 \brief     Particle System dtor
 ***********************************************/
ComponentParticleSystem::~ComponentParticleSystem()
{
	particle_list.clear();
	delete(mesh);
	delete(sprite);

}
/***********************************************
 \brief     tie particle system to a game object
 \
 \@param gameObject - the object to be tied to the system
 ***********************************************/
void ComponentParticleSystem::SetParent(GameObjectPtr gameObject)
{
	this->parent = gameObject;
	this->is_alive = false;
}
/***********************************************
 \brief     get parent game object for system
 \
 \@return - parent game object
 ***********************************************/
GameObjectPtr ComponentParticleSystem::GetParent(void)
{
	return this->parent;
}
/***********************************************
 \brief     check if the system is still alive
 \
 \@return - the system's is_alive bool 
 ***********************************************/
bool ComponentParticleSystem::IsAlive(void)
{
	return this->is_alive;
}
/***********************************************
 \brief     get the system's graphics component
 \
 \@return - graphics component
 ***********************************************/
ComponentGraphicPtr ComponentParticleSystem::GetParticleGraphic(void)
{
	return this->parent->GetParticleGraphic();
}
/***********************************************
 \brief     update the particle system
 \
 \@param dt - game's delta time value
 ***********************************************/
void ComponentParticleSystem::Update(float dt)
{
	//running through particle list
	for (auto& particle : particle_list)
	{
		//if the particle is dead or should be dead (no lifetime left)
		if (!particle.alive)
		{
			continue;
		}
		if (particle.life_remaining <= 0.0f)
		{
			particle.alive = false;
			continue;
		}
		//move particle and mesh
		particle.life_remaining -= dt;
		particle.position += particle.velocity * dt;
		particle.mesh->setPosition((particle.position.x + particle.velocity.x * dt), (particle.position.y + particle.velocity.y * dt));
	}
}
/***********************************************
 \brief     render the particles in the system
 \
 \@param dt - game's delta time value
 \@param window - game's window
 \@param shader - current window's shader
 \@param camera = current window's camera
 ***********************************************/
void ComponentParticleSystem::Render(float dt, GLFWwindow* window, Shader shader, ComponentCamera* camera, glm::vec2 scaleVec)
{
	//draw every active particle in the list
	for (auto& particle : particle_list)
	{
		if (particle.alive)
		{
			particle.mesh->UpdateGraphics(dt, window, shader, camera, ConvertTo4x4Affine(AffineScaleMatrix(scaleVec.x, scaleVec.y) * 
					AffineTranslationMatrix(particle.position.x, particle.position.y)), "Transform");
		}
	}
}
/***********************************************
 \brief     emit the particle's in the particle system
 \
 \@param pattern - pattern each particle follows as well as data for system's location on screen
 ***********************************************/
void ComponentParticleSystem::Emit(const ParticlePattern& pattern)
{
	//looping for each particle emitted in the pattern
	for (int i = 0; i < pattern.num_per; i++)
	{
		Particle& currentParticle = this->particle_list[num_particles];
		currentParticle.alive = true;
		//if the system is tied to a parent game object
		if (this->parent)
		{
			currentParticle.position.x += (parent->GetTransform()->GetPosition()->x + pattern.velocity.x);
			currentParticle.position.y += (parent->GetTransform()->GetPosition()->y + pattern.velocity.y);
		}
		//otherwise system is stationary
		else
		{
			currentParticle.position = pattern.position;
		}
		currentParticle.rotation = random.RandomFloat() * 2.0f * glm::pi<float>();
		currentParticle.velocity = pattern.velocity;
		currentParticle.velocity.x = pattern.velocityRange.x * (random.RandomFloat() - 0.5f);
		currentParticle.velocity.y = pattern.velocityRange.y * (random.RandomFloat() - 0.5f);
		currentParticle.lifetime = pattern.lifetime;
		currentParticle.life_remaining = pattern.lifetime;
		//replace dead particles with newly generated particles if the list fills up
		num_particles = --num_particles % this->particle_list.size();
	}
}
/***********************************************
 \brief     Emit an explosion moving in a linear direction
 \
 \@param pattern - pattern each particle follows as well as data for system's location on screen
 \@param factor - scale factor for vector
 ***********************************************/
void ComponentParticleSystem::EmitLinear(const ParticlePattern& pattern, float factor)
{
	//looping for each particle emitted in the pattern
	for (int i = 0; i < pattern.num_per; i++)
	{
		Particle& currentParticle = this->particle_list[num_particles];
		currentParticle.alive = true;
		//if the system is tied to a parent game object
		if (this->parent)
		{
			currentParticle.position.x += (parent->GetTransform()->GetPosition()->x + pattern.velocity.x);
			currentParticle.position.y += (parent->GetTransform()->GetPosition()->y + pattern.velocity.y);
		}
		//otherwise beginning position is from a stationary point
		else
		{
			currentParticle.position = pattern.position;
		}
		currentParticle.rotation = random.RandomFloat() * 2.0f * glm::pi<float>();
		currentParticle.velocity = pattern.velocity * factor;
		currentParticle.velocity.x = pattern.velocityRange.x + (random.RandomFloat() - 0.5f) * factor;
		currentParticle.velocity.y = pattern.velocityRange.y + (random.RandomFloat() - 0.5f) * factor;
		currentParticle.lifetime = pattern.lifetime;
		currentParticle.life_remaining = pattern.lifetime;
		//replace dead particles with newly generated particles if the list fills up
		num_particles = --num_particles % this->particle_list.size();
	}
}
/***********************************************
 \brief Attempting to emit in an arc
 \
 \@param pattern - pattern each particle follows as well as data for system's location on screen
 \@param factor - scale factor for vector
 \@param degrees - arc degree
 ***********************************************/
void ComponentParticleSystem::EmitCircular(const ParticlePattern& pattern, float factor, float degrees)
{
	//looping for each particle emitted in the pattern
	for (int i = 0; i < pattern.num_per; i++)
	{
		Particle& currentParticle = this->particle_list[num_particles];
		currentParticle.alive = true;
		//if the system is tied to a parent game object
		if (this->parent)
		{
			currentParticle.position.x += (parent->GetTransform()->GetPosition()->x + pattern.velocity.x);
			currentParticle.position.y += (parent->GetTransform()->GetPosition()->y + pattern.velocity.y);
		}
		//otherwise beginning position is from a stationary point
		else
		{
			currentParticle.position = pattern.position;
		}
		currentParticle.rotation = random.RandomFloat() * 2.0f * glm::pi<float>();
		currentParticle.velocity = pattern.velocity * factor;
		currentParticle.position.x = (pattern.position.y * pattern.velocityRange.x)+ cos(degrees) * factor;
		currentParticle.position.y = (pattern.position.y * pattern.velocityRange.y) + sin(degrees) * factor;
		currentParticle.lifetime = pattern.lifetime;
		currentParticle.life_remaining = pattern.lifetime;
		//replace dead particles with newly generated particles if the list fills up
		num_particles = --num_particles % this->particle_list.size();
	}
}
/***********************************************
 \brief     raining pattern
 \
 \@param dt - game's delta time value
 ***********************************************/
void ComponentParticleSystem::Rain(float dt)
{
	//running through particle list
	for (auto& particle : particle_list)
	{
		//if the particle is dead or should be dead (no lifetime left)
		if (!particle.alive)
		{
			continue;
		}
		if (particle.life_remaining <= 0.0f)
		{
			particle.alive = false;
			continue;
		}
		//move particle and mesh
		particle.life_remaining -= dt;
		particle.position += particle.velocity * dt;
		particle.mesh->setPosition((particle.position.x), (particle.position.y + particle.velocity.y * dt));
	}
}
/***********************************************
 \brief     update the particle system along an arc
 \
 \@param dt - game's delta time value
 \@param angle - angle for arc to follow
 ***********************************************/
void ComponentParticleSystem::UpdateCircular(float dt, float angle)
{
	//running through particle list
	for (auto& particle : particle_list)
	{
		//if the particle is dead or should be dead (no lifetime left)
		if (!particle.alive)
		{
			continue;
		}
		if (particle.life_remaining <= 0.0f)
		{
			particle.alive = false;
			continue;
		}
		//move particle and mesh
		particle.life_remaining -= dt;
		particle.position += particle.velocity * dt;
		particle.mesh->setPosition((particle.position.x + particle.velocity.x * dt), (particle.position.y + sin(angle)));
	}
}
/***********************************************
 \brief     initialize random number generator seed 
 ***********************************************/
void RandomGenerator::SeedInit(void)
{
	random_engine.seed(std::random_device()());
}
/***********************************************
 \brief     creates a random number between 0.0f and 1.0f
 \
 \@return - random float value
 ***********************************************/
//multiply by whatever number to set max (ex RandomGenerator::RandomFloat() * 1000 - 0-1000)
float RandomGenerator::RandomFloat(void)
{
	return (float)this->random_distribution(this->random_engine) / (float)std::numeric_limits<uint32_t>::max();
}
/***********************************************
 \brief     creates a random number between 0 and 1
 \
 \@return - random int value
 ***********************************************/
int RandomGenerator::RandomInt(void)
{
	return (int)this->random_distribution(this->random_engine) / (int)std::numeric_limits<uint32_t>::max();
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------