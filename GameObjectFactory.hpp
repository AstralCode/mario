#pragma once

#include <string>
#include <memory>

#include "GameObjectIdentifiers.hpp"
#include "SpritesetContainer.hpp"

class ResourceContainer;
class GraphicsScene;
class GameObject;

class GameObjectFactory final
{
public:
	GameObjectFactory(ResourceContainer& resources, SpritesetContainer& spritesets, GraphicsScene& scene) noexcept;

	GameObject* createMario() noexcept;
	GameObject* createGoomba() noexcept;

	GameObject* createCoin() noexcept;
	GameObject* createScoreCoin() noexcept;
	GameObject* createQuestionMarkBox() noexcept;

private:
	GameObject* createObject(const GameObjectIdentifiers identifier, const Textures textureIdentifier) const noexcept;

	ResourceContainer& mResources;
	SpritesetContainer& mSpritesets;
	GraphicsScene& mScene;
};