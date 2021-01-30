#include "GameSpriteAtlas.hpp"

void GameSpriteAtlas::addRegion(const std::string& identifier, const SpriteAtlasRegion& region)
{
	mRegions.emplace(identifier, region);
}

const SpriteAtlasRegion& GameSpriteAtlas::getRegion(const std::string& identifier) const
{
	return mRegions.at(identifier);
}
