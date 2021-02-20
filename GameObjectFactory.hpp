#pragma once

#include <string>
#include <memory>

#include "ResourceIdentifiers.hpp"
#include "SpritesetContainer.hpp"
#include "Spriteset.hpp"

class ResourceContainer;
class Animation;
class GraphicsGameObject;
class GameObjectCreator;
class GameObjectState;

class GameObjectFactory final
{
public:
	GameObjectFactory(ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator) noexcept;

	GraphicsGameObject* createMario() noexcept;
	GraphicsGameObject* createGoomba() noexcept;

	GraphicsGameObject* createCoin() noexcept;
	GraphicsGameObject* createScoreCoin() noexcept;
	GraphicsGameObject* createQuestionMarkBox() noexcept;

private:
	std::unique_ptr<Animation> createAnimation(const std::string& spritesetIdetntifier, const std::string& spritesetRegionIdentifier) const noexcept;

	template <typename TGameObjectState>
	std::unique_ptr<TGameObjectState> createObjectState(const std::string& spritesetIdetntifier) const noexcept;

	GraphicsGameObject* createObject(const TextureIdentifiers textureIdentifier) const noexcept;

	ResourceContainer& mResourceContainer;
	SpritesetContainer& mSpritesetContainer;
	GameObjectCreator& mGameObjectCreator;
};

template <typename TGameObjectState>
inline std::unique_ptr<TGameObjectState> GameObjectFactory::createObjectState(const std::string& spritesetIdetntifier) const noexcept
{
	static_assert(std::is_base_of_v<GameObjectState, TGameObjectState>, "TGameObjectState must derived from GameObjectState");

	return std::make_unique<TGameObjectState>(mSpritesetContainer.getSpriteset(spritesetIdetntifier));
}
