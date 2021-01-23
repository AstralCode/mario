#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Statistics.hpp"
#include "GameResourceManager.hpp"
#include "GameContextData.hpp"
#include "GameStateManager.hpp"

class Game final : private sf::NonCopyable
{
public:
	Game();

	void run();

	void processEvents();
	void processLogic();
	void processRender();

	GameContextData& getContextData();

	bool isRunning() const;

private:
	void executeMainLoop();

	void initializeStatistics();
	void renderStatistics();

	void loadResources();
	void loadFonts();
	void loadTextures();

	std::string makeFontPath(const std::string& filename) const;
	std::string makeTexturePath(const std::string& filename) const;

	std::string getResourcesPath() const;
	std::string getFontPath() const;
	std::string getTexturePath() const;

	sf::RenderWindow mRenderWindow;
	sf::Time mFrameTime;

	FPSCounter mFPSCounter;
	Statistics mStatistics;
	GameResourceManager mGameResourceManager;
	GameContextData mGameContextData;
	GameStateManager mGameStateManager;
};
