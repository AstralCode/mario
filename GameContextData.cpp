#include "GameContextData.hpp"

GameContextData::GameContextData(TiledMap& tiledMap, GraphicsItem& graphicsScene, GameResourceContainer& gameResourceContainer, GameSpriteAtlasManager& gameSpriteAtlasManager, GameObjectCreator& gameObjectCreator) :
	mTiledMap{tiledMap},
	mGraphicsScene{graphicsScene},
	mGameResourceContainer{gameResourceContainer},
	mGameSpriteAtlasManager{gameSpriteAtlasManager},
	mGameObjectCreator{gameObjectCreator}
{

}

TiledMap& GameContextData::getTiledMap()
{
	return mTiledMap;
}

GraphicsItem& GameContextData::getGraphicsScene()
{
	return mGraphicsScene;
}

GameResourceContainer& GameContextData::getGameResourceContainer()
{
	return mGameResourceContainer;
}

GameSpriteAtlasManager& GameContextData::getGameSpriteAtlasManager()
{
	return mGameSpriteAtlasManager;
}

GameObjectCreator& GameContextData::getGameObjectCreator()
{
	return mGameObjectCreator;
}
