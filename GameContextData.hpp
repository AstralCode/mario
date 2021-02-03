#pragma once

class TiledMap;
class GraphicsItem;
class GameResourceContainer;
class GameSpriteAtlasManager;
class GameObjectCreator;

class GameContextData final
{
public:
	GameContextData(TiledMap& tiledMap, GraphicsItem& graphicsScene, GameResourceContainer& gameResourceContainer, GameSpriteAtlasManager& gameSpriteAtlasManager, GameObjectCreator& gameObjectCreator);

	TiledMap& getTiledMap();
	GraphicsItem& getGraphicsScene();
	GameResourceContainer& getGameResourceContainer();
	GameSpriteAtlasManager& getGameSpriteAtlasManager();
	GameObjectCreator& getGameObjectCreator();

private:
	TiledMap& mTiledMap;
	GraphicsItem& mGraphicsScene;
	GameResourceContainer& mGameResourceContainer;
	GameSpriteAtlasManager& mGameSpriteAtlasManager;
	GameObjectCreator& mGameObjectCreator;
};
