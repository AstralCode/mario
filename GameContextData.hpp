#pragma once

class ResourceContainer;
class SpritesetContainer;
class GraphicsScene;

class GameContextData final
{
public:
	GameContextData(ResourceContainer& resources, SpritesetContainer& spritesets, GraphicsScene& scene) noexcept;

	ResourceContainer& getResources() noexcept;
	SpritesetContainer& getSpritesets() noexcept;
	GraphicsScene& getScene() noexcept;

private:
	ResourceContainer& mResources;
	SpritesetContainer& mSpritesets;
	GraphicsScene& mScene;
};
