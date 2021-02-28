#include "GameContextData.hpp"

GameContextData::GameContextData(TilemapView& tilemapView, TilemapEditor& tilemapEditor, ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator) noexcept :
	mTilemapView{tilemapView},
	mTilemapEditor{tilemapEditor},
	mResourceContainer{resourceContainer},
	mSpritesetContainer{spritesetContainer},
	mGameObjectCreator{gameObjectCreator}
{

}

TilemapView& GameContextData::getTilemapView() noexcept
{
	return mTilemapView;
}

TilemapEditor& GameContextData::getTilemapEditor() noexcept
{
	return mTilemapEditor;
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
