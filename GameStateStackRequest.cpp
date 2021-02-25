#include "GameStateStackRequest.hpp"

#include "GameStateManager.hpp"

PushGameStateRequest::PushGameStateRequest(const GameStateIdentifiers identifier) noexcept :
	mGameStateIdentifier{identifier}
{

}

void PushGameStateRequest::execute(GameStateManager& gameStateManager) noexcept
{
	gameStateManager.pushState(mGameStateIdentifier);
}

void PopGameStateRequest::execute(GameStateManager& gameStateManager) noexcept
{
	gameStateManager.popState();
}

void ClearGameStatesRequest::execute(GameStateManager& gameStateManager) noexcept
{
	gameStateManager.clearStates();
}
