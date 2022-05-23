#include "stdafx.h"
#include "Scene.h"

Scene::Scene(int ID, std::vector<Actor*> actors, std::shared_ptr<GameState>& gameState) : ID{ ID }, actors{ actors }, gameState{ gameState } {}

Scene::Scene(int ID, std::shared_ptr<GameState>& gameState) : ID{ ID }, gameState{ gameState } {}

Scene::~Scene()
{
	std::cout << "ROOM DESTRUCTOR CALLED : " << (int) actors.size() << std::endl;

	if (background)
		delete background;

	for (auto& actor : actors)
	{
		if (actor)
		{
			delete actor;
			actor = nullptr;
		}
	}
	actors.clear();
}

// Add an actor among all actors of the scene
void Scene::AddActor(Actor* actor)
{
	actors.emplace_back(actor);
	actor = nullptr;
}

// Get a specific actor among all actors of the scene
Actor* Scene::GetActor(int index)
{
	return actors[index];
}

// Get the scene ID
const int& Scene::GetID() const
{
	return ID;
}

// Get all actors of the scene
std::vector<Actor*>& Scene::GetActors()
{
	return actors;
}

// If we want to setup a background
void Scene::Update(float deltaTime)
{
	if (background)
		background->Draw();
}

// Remove an actor from the scene
bool Scene::RemoveActor(Actor* actor)
{
	if (!actor)
		return false;

	// Looking for the actor to delete
	auto it = std::find(actors.begin(), actors.end(), actor);

	if (it != actors.end())
	{
		// Deleting the actor
		actors.erase(it);
		std::cout << actor->GetName() << " removed" << std::endl;
		delete actor;
		return true;
	}
	actor = nullptr;
	return false;
}
