#include "GameContextData.hpp"

GameContextData::GameContextData(ResourceContainer& resources, SpritesetContainer& spritesets, GraphicsScene& scene, GameStateChanger& stateChanger) noexcept :
	mResources{resources},
	mSpritesets{spritesets},
	mScene{scene},
	mStateChanger{stateChanger}
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

GraphicsScene& GameContextData::getScene() noexcept
{
	return mScene;
}

GameStateChanger& GameContextData::getStateChanger() noexcept
{
	return mStateChanger;
}
