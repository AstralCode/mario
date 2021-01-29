#pragma once

#include <unordered_map>

#include "SpriteAtlasRegion.hpp"

template<typename TIdentifiers>
class SpriteAtlas final
{
public:
	void addRegion(const TIdentifiers identifier, const SpriteAtlasRegion& region);
	const SpriteAtlasRegion& getRegion(const TIdentifiers identifier) const;

private:
	std::unordered_map<TIdentifier, SpriteAtlasRegion> mRegions;
};

template<typename TIdentifiers>
inline void SpriteAtlas<TIdentifiers>::addRegion(const TIdentifiers identifier, const SpriteAtlasRegion& region)
{
	mRegions.emplace(identifier, region);
}

template<typename TIdentifiers>
inline const SpriteAtlasRegion& SpriteAtlas<TIdentifiers>::getRegion(const TIdentifiers identifier) const
{
	return mRegions.at(identifier);
}
