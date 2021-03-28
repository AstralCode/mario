#pragma once

#include <memory>

#include "Spriteset.hpp"
#include "SpritesetRegionIdentifiers.hpp"

class SpritesetContainer final
{
public:
	Spriteset<MarioSpritesetRegionType>& getMarioSpriteset() noexcept;
	const Spriteset<MarioSpritesetRegionType>& getMarioSpriteset() const noexcept;

	Spriteset<GoombaSpritesetRegionType>& getGoombaSpriteset() noexcept;
	const Spriteset<GoombaSpritesetRegionType>& getGoombaSpriteset() const noexcept;

	Spriteset<ItemSpritesetRegionType>& getItemSpriteset() noexcept;
	const Spriteset<ItemSpritesetRegionType>& getItemSpriteset() const noexcept;

private:
	Spriteset<MarioSpritesetRegionType> mMarioSpriteset;
	Spriteset<GoombaSpritesetRegionType> mGoombaSpriteset;
	Spriteset<ItemSpritesetRegionType> mItemSpriteset;
};
