#include "GameContextData.hpp"

GameContextData::GameContextData(TiledMap& tiledMap, GraphicsItem& graphicsScene, GameResourceContainer& gameResourceContainer, GameSpriteAtlasContainer& gameSpriteAtlasContainer, GameObjectCreator& gameObjectCreator) :
	mTiledMap{tiledMap},
	mGraphicsScene{graphicsScene},
	mGameResourceContainer{gameResourceContainer},
	mGameSpriteAtlasContainer{gameSpriteAtlasContainer},
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

GameSpriteAtlasContainer& GameContextData::getGameSpriteAtlasContainer()
{
	return mGameSpriteAtlasContainer;
}

GameObjectCreator& GameContextData::getGameObjectCreator()
{
	return mGameObjectCreator;
}
