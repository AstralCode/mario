#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Statistics.hpp"
#include "tilemap.hpp"
#include "GamePhysics.hpp"
#include "GraphicsItem.hpp"
#include "ResourceManager.hpp"
#include "SpritesetManager.hpp"
#include "CollisionModule.hpp"
#include "GameObjectManager.hpp"
#include "GameObjectFactory.hpp"
#include "GameContextData.hpp"
#include "GameStateManager.hpp"

class GameEngine final
{
public:
	GameEngine() noexcept;

	void run() noexcept;

	GameContextData& getContextData() noexcept;

	bool isRunning() const noexcept;

protected:
	void processEvents() noexcept;
	void processLogic(const sf::Time& frameTime) noexcept;
	void processRender() noexcept;

private:
	void executeMainLoop() noexcept;

	void initializeStatistics() noexcept;
	void initializeSpritesets() noexcept;
	void initializeCollisionHandlers() noexcept;
	void initializeGameState() noexcept;

	void loadResources() noexcept;
	void loadFonts() noexcept;
	void loadTextures() noexcept;

	sf::RenderWindow mRenderWindow;

	FPSCounter mFPSCounter;
	Statistics mStatistics;
	Tilemap mTilemap;
	GamePhysics mGamePhysics;
	GraphicsItem mGraphicsScene;
	ResourceManager mResourceManager;
	SpritesetManager mSpritesetManager;
	CollisionModule mCollisionModule;
	GameObjectManager mGameObjectManager;
	GameContextData mGameContextData;
	GameStateManager mGameStateManager;
};
