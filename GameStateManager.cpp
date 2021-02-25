#include "GameStateManager.hpp"

#include <stdexcept>

GameStateManager::GameStateManager(GameContextData& gameContextData) noexcept :
	mGameContextData{gameContextData}
{

}

void GameStateManager::pushState(const GameStateIdentifiers identifier) noexcept
{
	if (hasActiveStates())
	{
		getActiveState()->onLeave();
	}

	auto state = findState(identifier);
	state->onEnter();

	mGameStateStack.emplace_front(state);
}

void GameStateManager::popState() noexcept
{
	if (hasActiveStates())
	{
		getActiveState()->onLeave();
		mGameStateStack.pop_front();
	}
}

void GameStateManager::clearStates() noexcept
{
	while (hasActiveStates())
	{
		popState();
	}
}

void GameStateManager::pushStateRequest(const GameStateIdentifiers identifier) noexcept
{
	mGameStateStackRequests.emplace(std::make_unique<PushGameStateRequest>(identifier));
}

void GameStateManager::popStateRequest() noexcept
{
	mGameStateStackRequests.emplace(std::make_unique<PopGameStateRequest>());
}

void GameStateManager::clearStatesRequest() noexcept
{
	mGameStateStackRequests.emplace(std::make_unique<ClearGameStatesRequest>());
}

void GameStateManager::executeRequests() noexcept
{
	while (!mGameStateStackRequests.empty())
	{
		mGameStateStackRequests.front()->execute(*this);
		mGameStateStackRequests.pop();
	}
}

void GameStateManager::processEvents(const sf::Event& event) noexcept
{
	auto state = getActiveState();

	switch (event.type)
	{
	case sf::Event::KeyPressed:
		state->onKeyPressed(event.key);

		if (event.key.code == sf::Keyboard::Escape)
		{
			state->onEscapePressed();
		}
		break;

	case sf::Event::KeyReleased:
		state->onKeyReleased(event.key);
		break;

	case sf::Event::MouseButtonPressed:
		state->onMouseButtonPressed(event.mouseButton);
		break;

	case sf::Event::MouseButtonReleased:
		state->onMouseButtonReleased(event.mouseButton);
		break;

	case sf::Event::MouseMoved:
		state->onMouseMoved(event.mouseMove);
		break;

	case sf::Event::Closed:
		state->onClosed();
		break;

	default:
		break;
	}
}

void GameStateManager::processLogic(const sf::Time& frameTime) noexcept
{
	getActiveState()->processLogic(frameTime);
}

std::size_t GameStateManager::getActiveStateCount() const noexcept
{
	return mGameStateStack.size();
}

bool GameStateManager::hasActiveStates() const noexcept
{
	return !mGameStateStack.empty();
}

GameState* GameStateManager::findState(const GameStateIdentifiers identifier) const
{
	auto gameStatesIterator = mGameStates.find(identifier);
	if (gameStatesIterator == mGameStates.cend())
	{
		throw std::logic_error("GameEngine state not found!");
	}

	return gameStatesIterator->second.get();
}

GameState* GameStateManager::getActiveState() const noexcept
{
	return mGameStateStack.front();
}
