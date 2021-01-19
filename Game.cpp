#include "Game.hpp"

Game::Game() :
	mRenderWindow{{640u, 480u}, "Mario"},
	mGameContextData{mGameResourceManager},
	mGameStateManager{mGameContextData}
{

}

void Game::Run()
{
	mGameStateManager.AddPushStateRequest(GameStateIdentifiers::Initial);
	mGameStateManager.ProcessRequests();

	while (IsGameRunning())
	{
		ProcessEvents();
		ProcessLogic();
		ProcessRender();
	}

	mRenderWindow.close();
}

void Game::ProcessEvents()
{
	sf::Event event;

	while (mRenderWindow.pollEvent(event))
	{
		mGameStateManager.ProcessEvents(event);
	}

	mGameStateManager.ProcessEvents();
	mGameStateManager.ProcessRequests();
}

void Game::ProcessLogic()
{
	mGameStateManager.ProcessLogic();
	mGameStateManager.ProcessRequests();
}

void Game::ProcessRender()
{
	mRenderWindow.clear();
	mGameStateManager.ProcessRender(mRenderWindow);
	mRenderWindow.display();
}

GameContextData& Game::GetGameContextData()
{
	return mGameContextData;
}

bool Game::IsGameRunning() const
{
	return mGameStateManager.GetActiveStateCount() > 0u;
}
