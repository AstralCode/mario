#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "GameResourceManager.hpp"
#include "GameContextData.hpp"
#include "GameStateManager.hpp"

class Game : private sf::NonCopyable
{
public:
	Game();

	void Run();

	void ProcessEvents();
	void ProcessLogic();
	void ProcessRender();

	GameContextData& GetGameContextData();

	bool IsGameRunning() const;

private:
	sf::RenderWindow mRenderWindow;

	GameResourceManager mGameResourceManager;
	GameContextData mGameContextData;
	GameStateManager mGameStateManager;
};

