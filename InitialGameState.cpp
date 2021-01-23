#include "InitialGameState.hpp"

#include "GameStateChanger.hpp"
#include "GameContextData.hpp"
#include "GameResourceManager.hpp"
#include "GraphicsTextItem.hpp"

InitialGameState::InitialGameState(GameContextData& gameContextData, GameStateChanger& gameStateChanger) :
	GameState{gameContextData, gameStateChanger},
	isResourceLoaded{false}
{
}

void InitialGameState::onEnter()
{
	if (!isResourceLoaded)
	{
		isResourceLoaded = loadResources();
	}
}

void InitialGameState::onLeave()
{

}

void InitialGameState::processLogic(const sf::Time& frameTime)
{

}

bool InitialGameState::loadResources()
{
	if (!isResourceLoaded)
	{
		auto& resourceManager = mGameContextData.getResourceManager();
		resourceManager.addFont(FontIdentifiers::Roboto, "Resources/Fonts/Roboto.ttf");

		isResourceLoaded = true;
	}

	return true;
}

void InitialGameState::onKeyPressed(const sf::Event::KeyEvent& keyEvent)
{
	mGameStateChanger.clearStatesRequest();
}

void InitialGameState::onClosed()
{
	mGameStateChanger.clearStatesRequest();
}
