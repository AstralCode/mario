#include "SpritesetContainer.hpp"

Spriteset& SpritesetContainer::create(const std::string& identifier) noexcept
{
	auto spriteset = std::make_unique<Spriteset>();
	auto spritesetPointer = spriteset.get();

	mSpritesets.emplace(identifier, std::move(spriteset));

	return *spritesetPointer;
}

const Spriteset& SpritesetContainer::getSpriteset(const std::string& identifier) const
{
	return *mSpritesets.at(identifier);
}
