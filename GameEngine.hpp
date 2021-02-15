#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Statistics.hpp"
#include "TiledMap.hpp"
#include "GamePhysics.hpp"
#include "GraphicsItem.hpp"
#include "ResourceManager.hpp"
#include "SpritesetManager.hpp"
#include "GameObjectManager.hpp"
#include "GameObjectFactory.hpp"
#include "GameContextData.hpp"
#include "GameStateManager.hpp"

class GameEngine final
{
public:
	GameEngine();

	void run();

	GameContextData& getContextData();

	bool isRunning() const;

protected:
	void processEvents();
	void processLogic(const sf::Time& frameTime);
	void processRender();

private:
	void executeMainLoop();

	void initializeStatistics();
	void initializeSpritesets();
	void initializeGameState();

	void loadResources();
	void loadFonts();
	void loadTextures();

	sf::RenderWindow mRenderWindow;

	FPSCounter mFPSCounter;
	Statistics mStatistics;
	TiledMap mTiledMap;
	GamePhysics mGamePhysics;
	GraphicsItem mGraphicsScene;
	ResourceManager mResourceManager;
	SpritesetManager mSpritesetManager;
	GameObjectManager mGameObjectManager;
	GameContextData mGameContextData;
	GameStateManager mGameStateManager;
};
