#include "GameContextData.hpp"

GameContextData::GameContextData(ResourceContainer& resources, SpritesetContainer& spritesets, GameObjectCreator& gameObjectCreator) noexcept :
	mResources{resources},
	mSpritesets{spritesets},
	mGameObjectCreator{gameObjectCreator}
{

}

ResourceContainer& GameContextData::getResources() noexcept
{
	return mResources;
}

SpritesetContainer& GameContextData::getSpritesets() noexcept
{
	return mSpritesets;
}

GameObjectCreator& GameContextData::getGameObjectCreator() noexcept
{
	return mGameObjectCreator;
}
