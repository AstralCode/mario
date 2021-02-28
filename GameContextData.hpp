#pragma once

class TilemapView; 
class TilemapEditor;
class GraphicsItem;
class ResourceContainer;
class SpritesetContainer;
class GameObjectCreator;

class GameContextData final
{
public:
	GameContextData(TilemapView& tilemapView, TilemapEditor& tilemapEditor, ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator) noexcept;

	TilemapView& getTilemapView() noexcept;
	TilemapEditor& getTilemapEditor() noexcept;
	ResourceContainer& getResourceContainer() noexcept;
	SpritesetContainer& getSpritesetContainer() noexcept;
	GameObjectCreator& getGameObjectCreator() noexcept;

private:
	TilemapView& mTilemapView;
	TilemapEditor& mTilemapEditor;
	ResourceContainer& mResourceContainer;
	SpritesetContainer& mSpritesetContainer;
	GameObjectCreator& mGameObjectCreator;
};
