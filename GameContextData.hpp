#pragma once

class ResourceContainer;
class SpritesetContainer;
class World;

class GameContextData final
{
public:
	GameContextData(ResourceContainer& resources, SpritesetContainer& spritesets, World& world) noexcept;

	ResourceContainer& getResources() noexcept;
	SpritesetContainer& getSpritesets() noexcept;
	World& getWorld() noexcept;

private:
	ResourceContainer& mResources;
	SpritesetContainer& mSpritesets;
	World& mWorld;
};
