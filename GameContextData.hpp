#pragma once

class Tilemap;
class GraphicsItem;
class ResourceContainer;
class SpritesetContainer;
class GameObjectCreator;

class GameContextData final
{
public:
	GameContextData(Tilemap& tilemap, ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator);

	Tilemap& getTilemap();
	ResourceContainer& getResourceContainer();
	SpritesetContainer& getSpritesetContainer();
	GameObjectCreator& getGameObjectCreator();

private:
	Tilemap& mTilemap;
	ResourceContainer& mResourceContainer;
	SpritesetContainer& mSpritesetContainer;
	GameObjectCreator& mGameObjectCreator;
};
