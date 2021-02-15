#include "GameContextData.hpp"

GameContextData::GameContextData(TiledMap& tiledMap, ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator) :
	mTiledMap{tiledMap},
	mResourceContainer{resourceContainer},
	mSpritesetContainer{spritesetContainer},
	mGameObjectCreator{gameObjectCreator}
{

}

TiledMap& GameContextData::getTiledMap()
{
	return mTiledMap;
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
