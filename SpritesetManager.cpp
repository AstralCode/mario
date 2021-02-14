#include "SpritesetManager.hpp"

Spriteset& SpritesetManager::create(const std::string& identifier) noexcept
{
	auto spriteset = std::make_unique<Spriteset>();
	auto spritesetPointer = spriteset.get();

	mSpritesets.emplace(identifier, std::move(spriteset));

	return *spritesetPointer;
}

const Spriteset& SpritesetManager::getSpriteset(const std::string& identifier) const noexcept
{
	return *mSpritesets.at(identifier);
}
