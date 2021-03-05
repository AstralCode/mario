#include "GameContextData.hpp"

GameContextData::GameContextData(ResourceContainer& resources, SpritesetContainer& spritesets, GraphicsScene& scene) noexcept :
	mResources{resources},
	mSpritesets{spritesets},
	mScene{scene}
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
