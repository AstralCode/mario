#include "GameContextData.hpp"

GameContextData::GameContextData(Tilemap& tilemap, ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator) noexcept :
	mTilemap{tilemap},
	mResourceContainer{resourceContainer},
	mSpritesetContainer{spritesetContainer},
	mGameObjectCreator{gameObjectCreator}
{

}

Tilemap& GameContextData::getTilemap() noexcept
{
	return mTilemap;
}

ResourceContainer& GameContextData::getResourceContainer() noexcept
{
	return mResourceContainer;
}

SpritesetContainer& GameContextData::getSpritesetContainer() noexcept
{
	return mSpritesetContainer;
}

GameObjectCreator& GameContextData::getGameObjectCreator() noexcept
{
	return mGameObjectCreator;
}
