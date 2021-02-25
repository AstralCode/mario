#pragma once

#include <vector>
#include <memory>
#include <tuple>

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
	GameObjectManager(Tilemap& tilemap, GraphicsItem& graphicsScene, GamePhysics& physics, SpritesetContainer& spritesetContainer) noexcept;

	GameObject* create(const GameObjectIdentifiers identifier) noexcept override;

	template <typename TCollisionHandler>
	void addCollisionHandler() noexcept;

	void receiveEvents(const sf::Event& event) noexcept;

	void clean() noexcept;
	void update(const sf::Time& frameTime) noexcept;

private:
	void executeTilemapCollisionHandlers(const std::vector<std::tuple<GameObject*, sf::Vector2u>>& colliders) const noexcept;
	void executeObjectCollisionHandlers(const std::vector<std::tuple<GameObject*, GameObject*>>& colliders) const noexcept;

	std::vector<std::tuple<GameObject*, sf::Vector2u>> checkTilemapCollisions() const noexcept;
	std::vector<std::tuple<GameObject*, GameObject*>> checkObjectCollisions() const noexcept;

	Tilemap& mTilemap;
	GraphicsItem& mGraphicsScene;
	GamePhysics& mGamePhysics;
	SpritesetContainer& mSpritesetContainer;

	std::vector<std::unique_ptr<CollisionHandler>> mCollisionHandlers;

	std::vector<GameObject*> mGameObjects;
};

template <typename TCollisionHandler>
inline void GameObjectManager::addCollisionHandler() noexcept
{
	static_assert(std::is_base_of_v<CollisionHandler, TCollisionHandler>, "TCollisionHandler must derived from CollisionHandler");

	mCollisionHandlers.push_back(std::make_unique<TCollisionHandler>(mTilemap, mSpritesetContainer));
}
