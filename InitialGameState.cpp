#include "InitialGameState.hpp"

#include "GameContextData.hpp"
#include "GameStateChanger.hpp"
#include "GraphicsRectangleItem.hpp"

InitialGameState::InitialGameState(GameContextData& gameContextData, GameStateChanger& gameStateChanger) :
	GameState{gameContextData, gameStateChanger},
	mGameObjectFactory{gameContextData.getGameResourceContainer(), gameContextData.getGameSpriteAtlasManager(), gameContextData.getGameObjectCreator()}
{
	mSceneLayer = getGraphicsScene().addItem();

	mBackgroundLayer = mSceneLayer->addItem();
	mPlayersLayer = mSceneLayer->addItem();
	mEnemiesLayer = mSceneLayer->addItem();
}

void InitialGameState::onEnter()
{
	auto& tiledMap = getTiledMap();
	tiledMap.setTileSize({32.0f, 32.0f});
	tiledMap.setTileCount({640 / 32, 480 / 32});
	tiledMap.build();

	auto sky = mBackgroundLayer->addItem<GraphicsRectangleItem>();
	sky->setSize({640u, 480u});
	sky->setFillColor({97, 133, 246});

	auto mario = mGameObjectFactory.createMario(mPlayersLayer);
	mario->setPosition({32, 32});

	auto goomba = mGameObjectFactory.createGoomba(mEnemiesLayer);
	goomba->setPosition({96, 32});
}

void InitialGameState::onLeave()
{

}

void InitialGameState::processLogic(const sf::Time&)
{
	
}

void InitialGameState::onKeyPressed(const sf::Event::KeyEvent& keyEvent)
{
	if (keyEvent.code == sf::Keyboard::F1)
	{
		mEnemiesLayer->setVisible(!mEnemiesLayer->isVisible());
	}
	else if (keyEvent.code == sf::Keyboard::F3)
	{
		getTiledMap().setGridVisible(!getTiledMap().isGridVisible());
	}
}

void InitialGameState::onEscapePressed()
{
	mGameStateChanger.clearStatesRequest();
}
