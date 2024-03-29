#include "../stdafx.h"
#include "Scene.h"

Scene::Scene(int ID) : _ID { ID } {}

Scene::~Scene()
{
	std::cout << "ROOM DESTRUCTOR CALLED : " << (int) _actors.size() << std::endl;

	for (auto& actor : _actors)
	{
		if (actor)
			delete actor;
	}
	_actors.clear();
}

// Add an actor among all actors of the scene
void Scene::AddActor(Actor* actor)
{
	_actors.emplace_back(actor);
}

// Get a specific actor among all actors of the scene
Actor* Scene::GetActor(int index)
{
	return _actors[index];
}

// Get the scene ID
int Scene::GetID() const
{
	return _ID;
}

// Get all actors of the scene
std::vector<Actor*>& Scene::GetActors()
{
	return _actors;
}

void Scene::Init()
{
	initialized = true;
}

// If we want to setup a background
void Scene::Update(float deltaTime)
{
	// Updating the sprites of all the actors present in the scene
	for (const auto& actor : _actors)
	{
		if (!actor)
			continue;

		if (!actor->GetSprite())
			continue;

		actor->GetSprite()->Update(deltaTime);

		if (dynamic_cast<Trigger*>(actor))
		{
			dynamic_cast<Trigger*>(actor)->OnOverlap();
			continue;
		}

		auto character{ dynamic_cast<Character*>(actor) };

		if (!character)
			continue;

		if (character && dynamic_cast<ObjectController*>(character->GetController()))
		{
			character->MoveHorizontally();
			character->MoveVertically();
			continue;
		}
	}
}

void Scene::Render()
{
	for (const auto& actor : _actors)
	{
		if (!actor)
			continue;
		if (dynamic_cast<Collectable*>(actor) && dynamic_cast<Collectable*>(actor)->isItemized())
			continue;
		// Updating the sprites
		if (!actor->GetSprite())
			return;
		actor->GetSprite()->Draw();
		// Updating the colliders
		if (!actor->GetCollider())
			return;
		actor->GetCollider()->DrawCollision(actor, 50, 50, 50);
	}
}

// Remove an actor from the scene
bool Scene::RemoveActor(Actor* actor)
{
	if (!actor)
		return false;

	// Looking for the actor to delete
	auto it{ std::find(_actors.begin(), _actors.end(), actor) };

	if (it == _actors.end())
		return false;

	// Deleting the actor
	_actors.erase(it);
	std::cout << actor->GetName() << " removed" << std::endl;
	delete actor;
	return true;
}

// Remove a collectable from the scene
bool Scene::RemoveActor(Collectable* collectable)
{
	if (!collectable)
		return false;

	// Looking for the actor to delete
	auto it{ std::find(_actors.begin(), _actors.end(), collectable) };

	if (it == _actors.end())
		return false;
	
	// Deleting the actor
	_actors.erase(it);
	/*std::cout << collectable->GetName() << " removed" << std::endl;*/
	return true;
}