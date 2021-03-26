#include "SpritesetContainer.hpp"

Spriteset<MarioSpritesetRegions>& SpritesetContainer::getMarioSpriteset() noexcept
{
	return mMarioSpriteset;
}

const Spriteset<MarioSpritesetRegions>& SpritesetContainer::getMarioSpriteset() const noexcept
{
	return mMarioSpriteset;
}

Spriteset<GoombaSpritesetRegions>& SpritesetContainer::getGoombaSpriteset() noexcept
{
	return mGoombaSpriteset;
}

const Spriteset<GoombaSpritesetRegions>& SpritesetContainer::getGoombaSpriteset() const noexcept
{
	return mGoombaSpriteset;
}

Spriteset<ItemSpritesetRegions>& SpritesetContainer::getItemSpriteset() noexcept
{
	return mItemSpriteset;
}

const Spriteset<ItemSpritesetRegions>& SpritesetContainer::getItemSpriteset() const noexcept
{
	return mItemSpriteset;
}
