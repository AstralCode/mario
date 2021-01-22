#include "GameStateStackRequest.hpp"

#include "GameStateManager.hpp"

PushGameStateRequest::PushGameStateRequest(const GameStateIdentifiers identifier) :
	mGameStateIdentifier{identifier}
{

}

void PushGameStateRequest::execute(GameStateManager& gameStateManager)
{
	gameStateManager.pushState(mGameStateIdentifier);
}

void PopGameStateRequest::execute(GameStateManager& gameStateManager)
{
	gameStateManager.popState();
}

void ClearGameStatesRequest::execute(GameStateManager& gameStateManager)
{
	gameStateManager.clearStates();
}
