#pragma once

#include <string>
#include <memory>

#include "ResourceIdentifiers.hpp"
#include "GameObjectIdentifiers.hpp"
#include "SpritesetContainer.hpp"

class ResourceContainer;
class GraphicsScene;
class GameObject;
class GameObjectState;
class Animation;

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
	std::unique_ptr<Animation> createAnimation(const std::string& spritesetIdetntifier, const std::string& spritesetRegionIdentifier) const noexcept;

	template <typename TGameObjectState>
	std::unique_ptr<TGameObjectState> createObjectState(const std::string& spritesetIdetntifier) const noexcept;

	GameObject* createObject(const GameObjectIdentifiers identifier, const TextureIdentifiers textureIdentifier) const noexcept;

	ResourceContainer& mResources;
	SpritesetContainer& mSpritesets;
	GraphicsScene& mScene;
};

template <typename TGameObjectState>
inline std::unique_ptr<TGameObjectState> GameObjectFactory::createObjectState(const std::string& spritesetIdetntifier) const noexcept
{
	static_assert(std::is_base_of_v<GameObjectState, TGameObjectState>, "TGameObjectState must derived from GameObjectState");

	return std::make_unique<TGameObjectState>(mSpritesets.getSpriteset(spritesetIdetntifier));
}
