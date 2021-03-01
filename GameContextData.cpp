#include "GameContextData.hpp"

GameContextData::GameContextData(ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator, TilemapView& tilemapView) noexcept :
	mResourceContainer{resourceContainer},
	mSpritesetContainer{spritesetContainer},
	mGameObjectCreator{gameObjectCreator},
	mTilemapView{tilemapView}
{

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

TilemapView& GameContextData::getTilemapView() noexcept
{
	return mTilemapView;
}
