#include "Spriteset.hpp"

void Spriteset::addRegion(const std::string& identifier, const SpritesetRegion& region) noexcept
{
	mRegions.emplace(identifier, region);
}

const SpritesetRegion& Spriteset::getRegion(const std::string& identifier) const noexcept
{
	return mRegions.at(identifier);
}
