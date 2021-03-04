#pragma once

class ResourceContainer;
class SpritesetContainer;
class GameObjectCreator;
class TilemapView;

class GameContextData final
{
public:
	GameContextData(ResourceContainer& resources, SpritesetContainer& spritesets, GameObjectCreator& gameObjectCreator, TilemapView& tilemapView) noexcept;

	ResourceContainer& getResources() noexcept;
	SpritesetContainer& getSpritesets() noexcept;
	GameObjectCreator& getGameObjectCreator() noexcept;
	TilemapView& getTilemapView() noexcept;

private:
	ResourceContainer& mResources;
	SpritesetContainer& mSpritesets;
	GameObjectCreator& mGameObjectCreator;
	TilemapView& mTilemapView;
};
