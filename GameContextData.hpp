#pragma once

class TilemapView;
class GraphicsItem;
class ResourceContainer;
class SpritesetContainer;
class GameObjectCreator;

class GameContextData final
{
public:
	GameContextData(TilemapView& tilemapView, ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator) noexcept;

	TilemapView& getTilemapView() noexcept;
	ResourceContainer& getResourceContainer() noexcept;
	SpritesetContainer& getSpritesetContainer() noexcept;
	GameObjectCreator& getGameObjectCreator() noexcept;

private:
	TilemapView& mTilemapView;
	ResourceContainer& mResourceContainer;
	SpritesetContainer& mSpritesetContainer;
	GameObjectCreator& mGameObjectCreator;
};
