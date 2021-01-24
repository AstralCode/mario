#pragma once

#include <vector>
#include <memory>

#include "GameObject.hpp"
#include "GameObjectCreator.hpp"

class GameResourceManager;

class GameObjectManager final : public GameObjectCreator
{
public:
	GameObjectManager(GraphicsItem& graphicsScene, GameResourceManager& gameResourceManager);

	GameObject* addObject(const TextureIdentifiers textureIdentifier, const sf::IntRect& textureArea) override;

	void clean();
	void update(const sf::Time& frameTime);

private:
	GraphicsItem& mGraphicsScene;
	GameResourceManager& mGameResourceContainer;

	std::vector<std::unique_ptr<GameObject>> mGameObjects;
};
