#pragma once

#include <vector>
#include <memory>

#include "GameObject.hpp"
#include "GameObjectCreator.hpp"

class GameObjectManager final : public GameObjectCreator
{
public:
	GameObjectManager(GraphicsItem& graphicsScene);

	GameObject* create() override;

	void clean();
	void update(const sf::Time& frameTime);

private:
	GraphicsItem& mGraphicsScene;

	std::vector<std::unique_ptr<GameObject>> mGameObjects;
};
