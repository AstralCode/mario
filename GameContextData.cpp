#include "GameContextData.hpp"

GameContextData::GameContextData(ResourceContainer& resources, SpritesetContainer& spritesets, GameObjectCreator& gameObjectCreator, TilemapView& tilemapView) noexcept :
	mResources{resources},
	mSpritesets{spritesets},
	mGameObjectCreator{gameObjectCreator},
	mTilemapView{tilemapView}
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

TilemapView& GameContextData::getTilemapView() noexcept
{
	return mTilemapView;
}
