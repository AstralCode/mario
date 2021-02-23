#pragma once

#include <map>
#include <vector>
#include <memory>

#include "SFML/Window/Event.hpp"

#include "GameObjectCreator.hpp"
#include "CollisionHandler.hpp"

class Tilemap;
class GraphicsItem;
class GamePhysics;
class SpritesetContainer;

class GameObjectManager final : public GameObjectCreator
{
public:
	GameObjectManager(Tilemap& tilemap, GraphicsItem& graphicsScene, GamePhysics& physics, SpritesetContainer& spritesetContainer);

	GameObject* create(const GameObjectIdentifiers identifier) override;

	template <typename TCollisionHandler>
	void addCollisionHandler();

	void receiveEvents(const sf::Event& event);

	void clean();
	void update(const sf::Time& frameTime);

private:
	void checkTilemapCollisions() const;
	void checkObjectCollisions() const;

	Tilemap& mTilemap;
	GraphicsItem& mGraphicsScene;
	GamePhysics& mGamePhysics;
	SpritesetContainer& mSpritesetContainer;

	std::map<GameObjectIdentifiers, std::unique_ptr<CollisionHandler>> mCollisionHandlers;

	std::vector<GameObject*> mGameObjects;
};

template <typename TCollisionHandler>
inline void GameObjectManager::addCollisionHandler()
{
	static_assert(std::is_base_of_v<CollisionHandler, TCollisionHandler>, "TCollisionHandler must derived from CollisionHandler");
	
	auto handler = std::make_unique<TCollisionHandler>(mTilemap, mSpritesetContainer);
	mCollisionHandlers.emplace(handler->getTarget(), std::move(handler));
}
