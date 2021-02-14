#include "GameContextData.hpp"

GameContextData::GameContextData(TiledMap& tiledMap, GraphicsItem& graphicsScene, ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator) :
	mTiledMap{tiledMap},
	mGraphicsScene{graphicsScene},
	mResourceContainer{resourceContainer},
	mSpritesetContainer{spritesetContainer},
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

ResourceContainer& GameContextData::getResourceContainer()
{
	return mResourceContainer;
}

SpritesetContainer& GameContextData::getSpritesetContainer()
{
	return mSpritesetContainer;
}

GameObjectCreator& GameContextData::getGameObjectCreator()
{
	return mGameObjectCreator;
}
