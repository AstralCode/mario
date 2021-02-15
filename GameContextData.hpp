#pragma once

class TiledMap;
class GraphicsItem;
class ResourceContainer;
class SpritesetContainer;
class GameObjectCreator;

class GameContextData final
{
public:
	GameContextData(TiledMap& tiledMap, ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator);

	TiledMap& getTiledMap();
	ResourceContainer& getResourceContainer();
	SpritesetContainer& getSpritesetContainer();
	GameObjectCreator& getGameObjectCreator();

private:
	TiledMap& mTiledMap;
	ResourceContainer& mResourceContainer;
	SpritesetContainer& mSpritesetContainer;
	GameObjectCreator& mGameObjectCreator;
};
