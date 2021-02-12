#pragma once

#include <vector>
#include <memory>

#include "GameObject.hpp"
#include "GameObjectCreator.hpp"

class GamePhysics;

class GameObjectManager final : public GameObjectCreator
{
public:
	GameObjectManager(GamePhysics& physics);

	GameObject* create(GraphicsSpriteItem* sprite) override;

	void receiveEvents(const sf::Event& event);

	void clean();
	void update(const sf::Time& frameTime);

private:
	void disposeObjects();
	void cleanObjects();

	GamePhysics& mGamePhysics;

	std::vector<std::unique_ptr<GameObject>> mGameObjects;
};
