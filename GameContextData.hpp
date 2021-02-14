#pragma once

class TiledMap;
class GraphicsItem;
class ResourceContainer;
class SpritesetContainer;
class GameObjectCreator;

class GameContextData final
{
public:
	GameContextData(TiledMap& tiledMap, GraphicsItem& graphicsScene, ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator);

	TiledMap& getTiledMap();
	GraphicsItem& getGraphicsScene();
	ResourceContainer& getResourceContainer();
	SpritesetContainer& getSpritesetContainer();
	GameObjectCreator& getGameObjectCreator();

private:
	TiledMap& mTiledMap;
	GraphicsItem& mGraphicsScene;
	ResourceContainer& mResourceContainer;
	SpritesetContainer& mSpritesetContainer;
	GameObjectCreator& mGameObjectCreator;
};
