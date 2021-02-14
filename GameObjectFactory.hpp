#pragma once

#include <string>

#include "ResourceIdentifiers.hpp"

class GameObject;
class GameObjectState;
class GraphicsItem;
class SpritesetContainer;
class SpritesetRegion;
class GameObjectCreator;
class ResourceContainer;

class GameObjectFactory final
{
public:
	GameObjectFactory(ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator);

	GameObject* createMario(GraphicsItem* sceneLayer);
	GameObject* createGoomba(GraphicsItem* sceneLayer);

	GameObject* createCoin(GraphicsItem* sceneLayer);
	GameObject* createQuestionMarkBox(GraphicsItem* sceneLayer);

private:
	GameObject* create(GraphicsItem* sceneLayer, const TextureIdentifiers textureIdentifier) const;

	const SpritesetRegion& getSpritesetRegion(const std::string& spritesetIdetntifier, const std::string& spritesetRegionIdentifier) const noexcept;

	ResourceContainer& mResourceContainer;
	SpritesetContainer& mSpritesetContainer;
	GameObjectCreator& mGameObjectCreator;
};
