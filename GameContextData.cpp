#include "GameContextData.hpp"

GameContextData::GameContextData(TilemapView& tilemapView, ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator) noexcept :
	mTilemapView{tilemapView},
	mResourceContainer{resourceContainer},
	mSpritesetContainer{spritesetContainer},
	mGameObjectCreator{gameObjectCreator}
{

}

TilemapView& GameContextData::getTilemapView() noexcept
{
	return mTilemapView;
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
