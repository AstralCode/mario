#pragma once

class ResourceContainer;
class SpritesetContainer;
class GameObjectCreator;

class GameContextData final
{
public:
	GameContextData(ResourceContainer& resources, SpritesetContainer& spritesets, GameObjectCreator& gameObjectCreator) noexcept;

	ResourceContainer& getResources() noexcept;
	SpritesetContainer& getSpritesets() noexcept;
	GameObjectCreator& getGameObjectCreator() noexcept;

private:
	ResourceContainer& mResources;
	SpritesetContainer& mSpritesets;
	GameObjectCreator& mGameObjectCreator;
};
