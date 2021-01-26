#pragma once

#include <vector>
#include <memory>

#include "GameObject.hpp"
#include "GameObjectCreator.hpp"

class GameObjectManager final : public GameObjectCreator
{
public:
	GameObject* create(GraphicsSpriteItem* sprite) override;

	void clean();
	void update(const sf::Time& frameTime);

private:
	std::vector<std::unique_ptr<GameObject>> mGameObjects;
};
