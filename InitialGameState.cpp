#include "InitialGameState.hpp"

#include "GameContextData.hpp"
#include "GameStateChanger.hpp"

InitialGameState::InitialGameState(GameContextData& gameContextData, GameStateChanger& gameStateChanger) :
	GameState{gameContextData, gameStateChanger},
	mGameObjectFactory{gameContextData.getResourceContainer(), gameContextData.getGameObjectCreator()}
{
	mSceneLayer = getGraphicsScene().addItem();
	mEnemiesLayer = mSceneLayer->addItem();
}

void InitialGameState::onEnter()
{
	auto mario = mGameObjectFactory.createMario(mSceneLayer);
	mario->setPosition({32, 32});

	auto goomba = mGameObjectFactory.createGoomba(mEnemiesLayer);
	goomba->setPosition({96, 32});
}

void InitialGameState::onLeave()
{

}

void InitialGameState::processLogic(const sf::Time& frameTime)
{
	
}

void InitialGameState::onKeyPressed(const sf::Event::KeyEvent& keyEvent)
{
	if (keyEvent.code == sf::Keyboard::F1)
	{
		mEnemiesLayer->setVisible(!mEnemiesLayer->isVisible());
	}
}

void InitialGameState::onEscapePressed()
{
	mGameStateChanger.clearStatesRequest();
}
