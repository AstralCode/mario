#pragma once

#include <memory>

#include "Spriteset.hpp"
#include "SpritesetIdentifiers.hpp"

class SpritesetContainer final
{
public:
	Spriteset& create(const std::string& identifier) noexcept;
	const Spriteset& getSpriteset(const std::string& identifier) const;

private:
	std::map<std::string, std::unique_ptr<Spriteset>> mSpritesets;
};
