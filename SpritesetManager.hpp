#pragma once

#include <memory>

#include "SpritesetContainer.hpp"
#include "Spriteset.hpp"

class SpritesetManager final : public SpritesetContainer
{
public:
	Spriteset& create(const std::string& identifier) noexcept;
	const Spriteset& getSpriteset(const std::string& identifier) const noexcept override;

private:
	std::unordered_map<std::string, std::unique_ptr<Spriteset>> mSpritesets;
};
