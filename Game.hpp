#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

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
	sf::RenderWindow mRenderWindow;
	sf::Time mFrameTime;

	GameResourceManager mGameResourceManager;
	GameContextData mGameContextData;
	GameStateManager mGameStateManager;
};

