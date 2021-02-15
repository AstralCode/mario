#pragma once

#include <string>

#include "ResourceIdentifiers.hpp"

class ResourceContainer;
class SpritesetContainer;
class SpritesetRegion;
class GameObjectCreator;
class GameObject;

class GameObjectFactory final
{
public:
	GameObjectFactory(ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator);

	GameObject* createMario();
	GameObject* createGoomba();

	GameObject* createCoin();
	GameObject* createScoreCoin();
	GameObject* createQuestionMarkBox();

private:
	GameObject* create(const TextureIdentifiers textureIdentifier) const;

	const SpritesetRegion& getSpritesetRegion(const std::string& spritesetIdetntifier, const std::string& spritesetRegionIdentifier) const noexcept;

	ResourceContainer& mResourceContainer;
	SpritesetContainer& mSpritesetContainer;
	GameObjectCreator& mGameObjectCreator;
};
