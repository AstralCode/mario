#include "InitialGameState.hpp"

#include "GameStateChanger.hpp"

InitialGameState::InitialGameState(GameContextData& gameContextData, GameStateChanger& gameStateChanger) :
	GameState{gameContextData, gameStateChanger}
{

}

void InitialGameState::onEnter()
{

}

void InitialGameState::onLeave()
{

}

void InitialGameState::processLogic(const sf::Time& frameTime)
{

}

void InitialGameState::onEscapePressed()
{
	mGameStateChanger.clearStatesRequest();
}
