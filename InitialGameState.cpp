#include "InitialGameState.hpp"

#include "GameContextData.hpp"
#include "GameStateChanger.hpp"
#include "GraphicsRectangleItem.hpp"

InitialGameState::InitialGameState(GameContextData& gameContextData, GameStateChanger& gameStateChanger) :
	GameState{gameContextData, gameStateChanger},
	mGameObjectFactory{gameContextData.getGameResourceContainer(), gameContextData.getGameSpriteAtlasManager(), gameContextData.getGameObjectCreator()}
{
	mSceneLayer = getGraphicsScene().addItem();

	mPlayersLayer = mSceneLayer->addItem();
	mEnemiesLayer = mSceneLayer->addItem();
}

void InitialGameState::onEnter()
{
	const sf::Color backgroundColor{97, 133, 246};

	const std::vector< std::vector<unsigned int>> tileIdentifierMap = {
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 120, 121, 122, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 138, 139, 140, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000,  51, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000,  47,  48,  50, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{  47,  48,  49,  48,  50, 000, 000, 000, 000, 000, 000,  44,  45,  45,  45,  46, 000, 000, 000, 000 },
		{ 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001 },
		{ 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001 }
	};

	auto& tiledMap = getTiledMap();
	tiledMap.setTileset(&getTexture(TextureIdentifiers::Scenery));
	tiledMap.setTileIdentifierMap(tileIdentifierMap);
	tiledMap.setBackgroundColor(backgroundColor);
	tiledMap.build({32u, 32u});

	auto mario = mGameObjectFactory.createMario(mPlayersLayer);
	mario->setPosition(tiledMap.getGrid().getTilePosition({3, 12}));

	auto goomba = mGameObjectFactory.createGoomba(mEnemiesLayer);
	goomba->setPosition(tiledMap.getGrid().getTilePosition({5, 12}));
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
