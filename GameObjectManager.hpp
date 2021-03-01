#pragma once

#include "SFML/Window/Event.hpp"

#include "GameObjectCreator.hpp"
#include "PhysicsModule.hpp"
#include "CollisionModule.hpp"

class GameObjectManager final : public GameObjectCreator
{
public:
	GameObjectManager() noexcept;

	GameObject* create(const GameObjectIdentifiers identifier) noexcept override;

	void receiveEvents(const sf::Event& event) noexcept;

	void clean() noexcept;

	void update(const sf::Time& frameTime) noexcept;

private:
	PhysicsModule mPhysicsModule;
	CollisionModule mCollisionModule;

	std::vector<GameObject*> mGameObjects;
};
