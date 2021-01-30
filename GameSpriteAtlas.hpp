#pragma once

#include <unordered_map>

#include "SpriteAtlasRegion.hpp"

class GameSpriteAtlas final
{
public:
	void addRegion(const std::string& identifier, const SpriteAtlasRegion& region);
	const SpriteAtlasRegion& getRegion(const std::string& identifier) const;

private:
	std::unordered_map<std::string, SpriteAtlasRegion> mRegions;
};
