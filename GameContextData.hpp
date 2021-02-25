#pragma once

class Tilemap;
class GraphicsItem;
class ResourceContainer;
class SpritesetContainer;
class GameObjectCreator;

class GameContextData final
{
public:
	GameContextData(Tilemap& tilemap, ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator) noexcept;

	Tilemap& getTilemap() noexcept;
	ResourceContainer& getResourceContainer() noexcept;
	SpritesetContainer& getSpritesetContainer() noexcept;
	GameObjectCreator& getGameObjectCreator() noexcept;

private:
	Tilemap& mTilemap;
	ResourceContainer& mResourceContainer;
	SpritesetContainer& mSpritesetContainer;
	GameObjectCreator& mGameObjectCreator;
};
