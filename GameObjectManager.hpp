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

	GraphicsGameObject* create() override;

	void receiveEvents(const sf::Event& event);

	void clean();
	void update(const sf::Time& frameTime);

private:
	void checkCollisions() const;

	GraphicsItem& mGraphicsScene;
	GamePhysics& mGamePhysics;

	std::vector<GraphicsGameObject*> mGameObjects;
};
