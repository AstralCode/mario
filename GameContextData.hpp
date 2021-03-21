#pragma once

class ResourceContainer;
class SpritesetContainer;
class World;

class GameContextData final
{
public:
	GameContextData(ResourceContainer& resources, SpritesetContainer& spritesets, World& world) noexcept;

	ResourceContainer& getResources() noexcept;
	const ResourceContainer& getResources() const noexcept;

	SpritesetContainer& getSpritesets() noexcept;
	const SpritesetContainer& getSpritesets() const noexcept;

	World& getWorld() noexcept;
	const World& getWorld() const noexcept;

private:
	ResourceContainer& mResources;
	SpritesetContainer& mSpritesets;
	World& mWorld;
};
