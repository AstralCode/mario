#include "GameContextData.hpp"

GameContextData::GameContextData(ResourceContainer& resources, SpritesetContainer& spritesets, World& world) noexcept :
	mResources{resources},
	mSpritesets{spritesets},
	mWorld{world}
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

World& GameContextData::getWorld() noexcept
{
	return mWorld;
}
