#include "InitialGameState.hpp"

#include "GameStateChanger.hpp"
#include "GameResourceContainer.hpp"

InitialGameState::InitialGameState(GameContextData& gameContextData, GameStateChanger& gameStateChanger) :
	GameState{gameContextData, gameStateChanger}
{

}

void InitialGameState::onEnter()
{
	mUser = getGameObjectCreator().create();
	mUser->setTexture(getTexture(TextureIdentifiers::Mario));
	mUser->setTextureArea({0, 0, 32, 32});
}

void InitialGameState::onLeave()
{

}

void InitialGameState::processLogic(const sf::Time& frameTime)
{

}

void InitialGameState::onKeyPressed(const sf::Event::KeyEvent& keyEvent)
{
	if (keyEvent.code == sf::Keyboard::Q)
	{
		mUser->setDestroyed(true);
	}
}

void InitialGameState::onEscapePressed()
{
	mGameStateChanger.clearStatesRequest();
}
