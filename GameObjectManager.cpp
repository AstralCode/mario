#include "GameObjectManager.hpp"

#include <algorithm>
#include <functional>

#include "GamePhysics.hpp"
#include "GameSpriteAtlasManager.hpp"

GameObjectManager::GameObjectManager(GamePhysics& physics, GameSpriteAtlasManager& spriteAtlasManager) :
	mGamePhysics{physics},
	mSpriteAtlasManager{spriteAtlasManager}
{

}

GameObject* GameObjectManager::create(const GameSpriteAtlas& spriteAtlas, GraphicsSpriteItem* sprite)
{
	auto object = std::make_unique<GameObject>(spriteAtlas, sprite);
	auto objectPointer = object.get();

	mGameObjects.push_back(std::move(object));

    return objectPointer;
}

void GameObjectManager::receiveEvents(const sf::Event& event)
{
	for (auto& object : mGameObjects)
	{
		object->receiveEvents(event);
	}
}

void GameObjectManager::clean()
{
	disposeObjects();
	cleanObjects();
}

void GameObjectManager::update(const sf::Time& frameTime)
{
	for (auto& object : mGameObjects)
	{
		if (!object->isDestroyed())
		{
			object->update(frameTime);

			mGamePhysics.update(*object, frameTime);
		}
	}
}

void GameObjectManager::disposeObjects()
{
	for (auto& object : mGameObjects)
	{
		if (object->isDestroyed())
		{
			object->dispose();
		}
	}
}

void GameObjectManager::cleanObjects()
{
	auto gameObjectsIterator = std::remove_if(mGameObjects.begin(), mGameObjects.end(), std::mem_fn(&GameObject::isDestroyed));
	mGameObjects.erase(gameObjectsIterator, mGameObjects.end());
}
