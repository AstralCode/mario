#pragma once

#include "SFML/Window/Event.hpp"

#include "GameObjectCreator.hpp"
#include "CollisionModule.hpp"

class GamePhysics;
class SpritesetContainer;

class GameObjectManager final : public GameObjectCreator
{
public:
	GameObjectManager(GraphicsItem& graphicsScene, GamePhysics& physics, CollisionModule& collisionModule) noexcept;

	GameObject* create(const GameObjectIdentifiers identifier) noexcept override;

	void receiveEvents(const sf::Event& event) noexcept;

	void clean() noexcept;

	void update(const sf::Time& frameTime) noexcept;

private:
	GraphicsItem& mGraphicsScene;
	GamePhysics& mGamePhysics;
	CollisionModule& mCollisionModule;

	std::vector<GameObject*> mGameObjects;
};
