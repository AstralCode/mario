#pragma once

class TiledMap;
class GraphicsItem;
class GameResourceContainer;
class GameSpriteAtlasContainer;
class GameObjectCreator;

class GameContextData final
{
public:
	GameContextData(TiledMap& tiledMap, GraphicsItem& graphicsScene, GameResourceContainer& gameResourceContainer, GameSpriteAtlasContainer& gameSpriteAtlasContainer, GameObjectCreator& gameObjectCreator);

	TiledMap& getTiledMap();
	GraphicsItem& getGraphicsScene();
	GameResourceContainer& getGameResourceContainer();
	GameSpriteAtlasContainer& getGameSpriteAtlasContainer();
	GameObjectCreator& getGameObjectCreator();

private:
	TiledMap& mTiledMap;
	GraphicsItem& mGraphicsScene;
	GameResourceContainer& mGameResourceContainer;
	GameSpriteAtlasContainer& mGameSpriteAtlasContainer;
	GameObjectCreator& mGameObjectCreator;
};
