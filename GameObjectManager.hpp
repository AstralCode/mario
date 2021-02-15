#pragma once

#include <vector>
#include <memory>

#include "SFML/Window/Event.hpp"

#include "GameObjectCreator.hpp"

class GraphicsItem;
class GamePhysics;

class GameObjectManager final : public GameObjectCreator
{
public:
	GameObjectManager(GraphicsItem& graphicsScene, GamePhysics& physics);

	GameObject* create() override;

	void receiveEvents(const sf::Event& event);

	void clean();
	void update(const sf::Time& frameTime);

private:
	GraphicsItem& mGraphicsScene;
	GamePhysics& mGamePhysics;

	std::vector<GameObject*> mGameObjects;
};
