#pragma once

#include <map>

#include "SpritesetRegion.hpp"

class Spriteset final
{
public:
	void addRegion(const std::string& identifier, const SpritesetRegion& region) noexcept;
	const SpritesetRegion& getRegion(const std::string& identifier) const noexcept;

private:
	std::map<std::string, SpritesetRegion> mRegions;
};
