#include "GameContextData.hpp"

GameContextData::GameContextData(Tilemap& tilemap, ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator) :
	mTilemap{tilemap},
	mResourceContainer{resourceContainer},
	mSpritesetContainer{spritesetContainer},
	mGameObjectCreator{gameObjectCreator}
{

}

Tilemap& GameContextData::getTilemap()
{
	return mTilemap;
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
