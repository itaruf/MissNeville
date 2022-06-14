#include "../stdafx.h"
#include "Scene.h"
#include "Collectable.h"
#include "TriggerScene.h"

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
const int& Scene::GetID() const
{
	return _ID;
}

// Get all actors of the scene
std::vector<Actor*>& Scene::GetActors()
{
	return _actors;
}

bool Scene::Init()
{
	if (!initialized)
	{
		AddActor(GameState::_player);
		
		auto wallLeft{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(WALL_OFFSET, APP_VIRTUAL_HEIGHT), new Collision(APP_VIRTUAL_HEIGHT, 2)) };
		wallLeft->SetTag("wall");
		AddActor(wallLeft);

		auto wallBot{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(APP_VIRTUAL_WIDTH, WALL_OFFSET), new Collision(2, APP_VIRTUAL_WIDTH)) };
		wallBot->SetTag("wall");
		AddActor(wallBot);

		auto wallTop{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(APP_VIRTUAL_WIDTH, APP_VIRTUAL_HEIGHT - WALL_OFFSET), new Collision(2, APP_VIRTUAL_WIDTH)) };
		wallTop->SetTag("wall");
		AddActor(wallTop);

		auto wallRight{ new Actor(MWall.name, App::CreateSprite(MWall.model, 1, 1, MWall.frame, MWall.scale), new Vector2D(APP_VIRTUAL_WIDTH - WALL_OFFSET, APP_VIRTUAL_HEIGHT - WALL_OFFSET), new Collision(APP_VIRTUAL_HEIGHT, 2)) };
		wallRight->SetTag("wall");
		AddActor(wallRight);

		initialized = !initialized;
		/*App::PlaySoundW(sfx, true);*/

		return false;
	}
	return true;
}

// If we want to setup a background
void Scene::Update(float deltaTime)
{
	if (_background)
		_background->Draw();

	// Updating the sprites of all the actors present in the scene
	for (const auto& item : _actors)
	{
		if (!item)
			continue;

		item->GetSprite()->Update(deltaTime);

		if (dynamic_cast<Trigger*>(item))
		{
			dynamic_cast<Trigger*>(item)->OnOverlap();
			continue;
		}

		auto c{ dynamic_cast<Character*>(item) };

		if (!c)
			continue;

		if (c && dynamic_cast<ObjectController*>(c->GetController()))
		{
			c->MoveHorizontally();
			c->MoveVertically();
			continue;
		}
	}
}

void Scene::Render()
{
	for (const auto& item : _actors)
	{
		if (!item)
			continue;
		if (dynamic_cast<Collectable*>(item) && dynamic_cast<Collectable*>(item)->itemized)
			continue;
		// Updating the sprites
		item->GetSprite()->Draw();
		// Updating the colliders
		item->GetCollider()->DrawCollision(item, 50, 50, 50);
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