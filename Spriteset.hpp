#pragma once

#include <map>

#include "SpritesetRegion.hpp"

template <typename TIdentifier>
class Spriteset final
{
public:
	void addRegion(const TIdentifier identifier, const SpritesetRegion& region) noexcept;
	const SpritesetRegion& getRegion(const TIdentifier identifier) const noexcept;

private:
	std::map<TIdentifier, SpritesetRegion> mRegions;
};

template <typename TIdentifier>
void Spriteset<TIdentifier>::addRegion(const TIdentifier identifier, const SpritesetRegion& region) noexcept
{
	mRegions.emplace(identifier, region);
}

template <typename TIdentifier>
const SpritesetRegion& Spriteset<TIdentifier>::getRegion(const TIdentifier identifier) const noexcept
{
	return mRegions.at(identifier);
}
