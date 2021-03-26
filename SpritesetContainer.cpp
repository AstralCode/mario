#include "SpritesetContainer.hpp"

Spriteset<MarioSpritesetRegionType>& SpritesetContainer::getMarioSpriteset() noexcept
{
	return mMarioSpriteset;
}

const Spriteset<MarioSpritesetRegionType>& SpritesetContainer::getMarioSpriteset() const noexcept
{
	return mMarioSpriteset;
}

Spriteset<GoombaSpritesetRegionType>& SpritesetContainer::getGoombaSpriteset() noexcept
{
	return mGoombaSpriteset;
}

const Spriteset<GoombaSpritesetRegionType>& SpritesetContainer::getGoombaSpriteset() const noexcept
{
	return mGoombaSpriteset;
}

Spriteset<ItemSpritesetRegionType>& SpritesetContainer::getItemSpriteset() noexcept
{
	return mItemSpriteset;
}

const Spriteset<ItemSpritesetRegionType>& SpritesetContainer::getItemSpriteset() const noexcept
{
	return mItemSpriteset;
}
