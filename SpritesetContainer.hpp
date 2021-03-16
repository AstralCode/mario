#pragma once

#include <memory>

#include "Spriteset.hpp"
#include "SpritesetRegions.hpp"

class SpritesetContainer final
{
public:
	Spriteset<MarioSpritesetRegions>& getMarioSpriteset() noexcept;
	const Spriteset<MarioSpritesetRegions>& getMarioSpriteset() const noexcept;

	Spriteset<GoombaSpritesetRegions>& getGoombaSpriteset() noexcept;
	const Spriteset<GoombaSpritesetRegions>& getGoombaSpriteset() const noexcept;

	Spriteset<ItemSpritesetRegions>& getItemSpriteset() noexcept;
	const Spriteset<ItemSpritesetRegions>& getItemSpriteset() const noexcept;

	Spriteset<BlockSpritesetRegions>& getBlockSpriteset() noexcept;
	const Spriteset<BlockSpritesetRegions>& getBlockSpriteset() const noexcept;

private:
	Spriteset<MarioSpritesetRegions> mMarioSpriteset;
	Spriteset<GoombaSpritesetRegions> mGoombaSpriteset;
	Spriteset<ItemSpritesetRegions> mItemSpriteset;
	Spriteset<BlockSpritesetRegions> mBlockSpriteset;
};
