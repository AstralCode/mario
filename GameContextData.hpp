#pragma once

class ResourceContainer;
class SpritesetContainer;
class GraphicsScene;
class GameStateChanger;

class GameContextData final
{
public:
	GameContextData(ResourceContainer& resources, SpritesetContainer& spritesets, GraphicsScene& scene, GameStateChanger& stateChanger) noexcept;

	ResourceContainer& getResources() noexcept;
	SpritesetContainer& getSpritesets() noexcept;
	GraphicsScene& getScene() noexcept;
	GameStateChanger& getStateChanger() noexcept;

private:
	ResourceContainer& mResources;
	SpritesetContainer& mSpritesets;
	GraphicsScene& mScene;
	GameStateChanger& mStateChanger;
};
