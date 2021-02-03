#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Statistics.hpp"
#include "TiledMap.hpp"
#include "GamePhysics.hpp"
#include "GraphicsItem.hpp"
#include "GameResourceManager.hpp"
#include "GameSpriteAtlasManager.hpp"
#include "GameObjectManager.hpp"
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
	void initializeGameSpriteAtlases();
	void initializeGameState();

	void loadResources();
	void loadFonts();
	void loadTextures();

	std::string makeFontPath(const std::string& filename) const;
	std::string makeTexturePath(const std::string& filename) const;

	std::string getResourcesPath() const;
	std::string getFontPath() const;
	std::string getTexturePath() const;

	sf::RenderWindow mRenderWindow;

	FPSCounter mFPSCounter;
	Statistics mStatistics;
	TiledMap mTiledMap;
	GamePhysics mGamePhysics;
	GraphicsItem mGraphicsScene;
	GameResourceManager mGameResourceContainer;
	GameSpriteAtlasManager mGameSpriteAtlasManager;
	GameObjectManager mGameObjectManager;
	GameContextData mGameContextData;
	GameStateManager mGameStateManager;
};
