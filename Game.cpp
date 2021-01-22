#include "Game.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>

#include "InitialGameState.hpp"

Game::Game() :
	mRenderWindow{{640u, 480u}, "Mario"},
	mFrameTime{sf::seconds(1.0f / 60u)},
	mGameContextData{mGameResourceManager},
	mGameStateManager{mGameContextData}
{

}

void Game::run()
{
	sf::Clock clock{};
	sf::Time frameUpdateTime{};

	mGameStateManager.registerState<InitialGameState>(GameStateIdentifiers::Initial);
	mGameStateManager.pushState(GameStateIdentifiers::Initial);

	while (isRunning())
	{
		bool renderFrame{false};

		frameUpdateTime += clock.restart();

		while (frameUpdateTime > mFrameTime)
		{
			processEvents();

			if (!mGameStateManager.hasActiveStates())
			{
				break;
			}

			processLogic();

			if (!mGameStateManager.hasActiveStates())
			{
				break;
			}

			renderFrame = true;

			frameUpdateTime -= mFrameTime;
		}

		if (renderFrame)
		{
			processRender();
		}
		else
		{
			sf::sleep(sf::milliseconds(10));
		}
	}

	mRenderWindow.close();
}

void Game::processEvents()
{
	sf::Event event;

	while (mRenderWindow.pollEvent(event))
	{
		mGameStateManager.processEvents(event);
	}

	mGameStateManager.executeRequests();
}

void Game::processLogic()
{
	mGameStateManager.processLogic(mFrameTime);
	mGameStateManager.executeRequests();
}

void Game::processRender()
{
	mRenderWindow.clear();
	mGameStateManager.processRender(mRenderWindow);
	mRenderWindow.display();
}

GameContextData& Game::getContextData()
{
	return mGameContextData;
}

bool Game::isRunning() const
{
	return mGameStateManager.hasActiveStates();
}
