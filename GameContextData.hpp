#pragma once

class ResourceContainer;
class SpritesetContainer;
class GameObjectCreator;
class TilemapView;

class GameContextData final
{
public:
	GameContextData(ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator, TilemapView& tilemapView) noexcept;

	ResourceContainer& getResourceContainer() noexcept;
	SpritesetContainer& getSpritesetContainer() noexcept;
	GameObjectCreator& getGameObjectCreator() noexcept;
	TilemapView& getTilemapView() noexcept;

private:
	ResourceContainer& mResourceContainer;
	SpritesetContainer& mSpritesetContainer;
	GameObjectCreator& mGameObjectCreator;
	TilemapView& mTilemapView;
};
