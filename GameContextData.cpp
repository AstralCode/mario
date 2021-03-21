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

const ResourceContainer& GameContextData::getResources() const noexcept
{
	return mResources;
}

SpritesetContainer& GameContextData::getSpritesets() noexcept
{
	return mSpritesets;
}

const SpritesetContainer& GameContextData::getSpritesets() const noexcept
{
	return mSpritesets;
}

World& GameContextData::getWorld() noexcept
{
	return mWorld;
}

const World& GameContextData::getWorld() const noexcept
{
	return mWorld;
}
