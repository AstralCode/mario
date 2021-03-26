#include "Tile.hpp"

Tile::Tile() noexcept :
	mIdentifier{0}
{

}

void Tile::setIdentifier(const Identifier identifier) noexcept
{
	mIdentifier = identifier;
}

void Tile::setTrait(const TraitType trait) noexcept
{
	mTraits.set(trait);
}

void Tile::setTraits(const Traits& traits) noexcept
{
	mTraits = traits;
}

void Tile::setIndex(const TileIndex& index) noexcept
{
	mIndex = index;
}

void Tile::setArea(const FloatArea& area) noexcept
{
	mArea = area;
}

Tile::Identifier Tile::getIdentifier() const noexcept
{
	return mIdentifier;
}

const TileIndex& Tile::getIndex() const noexcept
{
	return mIndex;
}

const Tile::Traits& Tile::getTraits() const noexcept
{
	return mTraits;
}

const FloatArea& Tile::getArea() const noexcept
{
	return mArea;
}

bool Tile::hasTrait(const TraitType trait) const noexcept
{
	return mTraits.isSet(trait);
}
