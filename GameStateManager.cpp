#include "GameStateManager.hpp"

#include <stdexcept>

GameStateManager::GameStateManager(GameContextData& gameContextData) :
	mGameContextData{gameContextData}
{

}

void GameStateManager::pushState(const GameStateIdentifiers identifier)
{
	if (hasActiveStates())
	{
		getActiveState()->onLeave();
	}

	auto state = findState(identifier);
	state->onEnter();

	mGameStateStack.emplace_front(state);
}

void GameStateManager::popState()
{
	if (hasActiveStates())
	{
		getActiveState()->onLeave();
		mGameStateStack.pop_front();
	}
}

void GameStateManager::clearStates()
{
	while (hasActiveStates())
	{
		popState();
	}
}

void GameStateManager::pushStateRequest(const GameStateIdentifiers identifier)
{
	mGameStateStackRequests.emplace(std::make_unique<PushGameStateRequest>(identifier));
}

void GameStateManager::popStateRequest()
{
	mGameStateStackRequests.emplace(std::make_unique<PopGameStateRequest>());
}

void GameStateManager::clearStatesRequest()
{
	mGameStateStackRequests.emplace(std::make_unique<ClearGameStatesRequest>());
}

void GameStateManager::executeRequests()
{
	while (!mGameStateStackRequests.empty())
	{
		mGameStateStackRequests.front()->execute(*this);
		mGameStateStackRequests.pop();
	}
}

void GameStateManager::processEvents(const sf::Event& event)
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

void GameStateManager::processLogic(const sf::Time& frameTime)
{
	getActiveState()->processLogic(frameTime);
}

void GameStateManager::processRender(sf::RenderTarget& renderTarget)
{
	for (auto state = mGameStateStack.crbegin(); state != mGameStateStack.crend(); state++)
	{
		renderTarget.draw((*state)->getGraphicsScene());
	}
}

std::size_t GameStateManager::getActiveStateCount() const
{
	return mGameStateStack.size();
}

bool GameStateManager::hasActiveStates() const
{
	return !mGameStateStack.empty();
}

GameState* GameStateManager::findState(const GameStateIdentifiers identifier) const
{
	auto gameStatesIterator = mGameStates.find(identifier);
	if (gameStatesIterator == mGameStates.cend())
	{
		throw std::logic_error("Game state not found!");
	}

	return gameStatesIterator->second.get();
}

GameState* GameStateManager::getActiveState() const
{
	return mGameStateStack.front();
}
