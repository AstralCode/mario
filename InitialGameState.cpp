#include "InitialGameState.hpp"

#include "GameStateChanger.hpp"

void InitialGameState::onEnter()
{

}

void InitialGameState::onLeave()
{

}

void InitialGameState::processLogic(const sf::Time& frameTime)
{

}

void InitialGameState::onKeyPressed(const sf::Event::KeyEvent& keyEvent)
{
	mGameStateChanger.clearStatesRequest();
}

void InitialGameState::onClosed()
{
	mGameStateChanger.clearStatesRequest();
}
