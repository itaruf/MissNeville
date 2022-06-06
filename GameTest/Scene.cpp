#include "stdafx.h"
#include "Scene.h"

Scene::Scene(int ID, std::vector<Actor*> actors) : _ID{ ID }, _actors{ actors } {}

Scene::Scene(int ID) : _ID{ ID } {}

Scene::~Scene()
{
	std::cout << "ROOM DESTRUCTOR CALLED : " << (int) _actors.size() << std::endl;

	if (_background)
		delete _background;

	for (auto& actor : _actors)
	{
		if (actor)
		{
			delete actor;
			actor = nullptr;
		}
	}
	_actors.clear();
}

// Add an actor among all actors of the scene
void Scene::AddActor(Actor* actor)
{
	_actors.emplace_back(actor);
	actor = nullptr;
}

// Get a specific actor among all actors of the scene
Actor* Scene::GetActor(int index)
{
	return _actors[index];
}

// Get the scene ID
const int& Scene::GetID() const
{
	return _ID;
}

// Get all actors of the scene
std::vector<Actor*>& Scene::GetActors()
{
	return _actors;
}

// If we want to setup a background
void Scene::Update(float deltaTime)
{
	if (_background)
		_background->Draw();
}

// Remove an actor from the scene
bool Scene::RemoveActor(Actor* actor)
{
	if (!actor)
		return false;

	// Looking for the actor to delete
	auto it = std::find(_actors.begin(), _actors.end(), actor);

	if (it != _actors.end())
	{
		// Deleting the actor
		_actors.erase(it);
		std::cout << actor->GetName() << " removed" << std::endl;
		delete actor;
		return true;
	}
	actor = nullptr;
	return false;
}
