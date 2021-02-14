#include "InitialGameState.hpp"

#include "GameContextData.hpp"
#include "GameStateChanger.hpp"
#include "GraphicsRectangleItem.hpp"

InitialGameState::InitialGameState(GameContextData& gameContextData, GameStateChanger& gameStateChanger) :
	GameState{gameContextData, gameStateChanger},
	mGameObjectFactory{gameContextData.getResourceContainer(), gameContextData.getSpritesetContainer(), gameContextData.getGameObjectCreator()}
{
	mSceneLayer = getGraphicsScene().addItem();

	mPlayersLayer = mSceneLayer->addItem();
	mEnemiesLayer = mSceneLayer->addItem();
	mItemsLayer = mSceneLayer->addItem();
	mBlocksLayer = mSceneLayer->addItem();
}

void InitialGameState::onEnter()
{
	const std::vector<std::vector<unsigned int>> tileIdentifierMap =
	{
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
	tiledMap.setBackgroundColor({97, 133, 246});
	tiledMap.build({32u, 32u});

	mGameObjectFactory.createGoomba(mEnemiesLayer)->setPosition(tiledMap.getGrid().getTilePosition({5, 12}));
	mGameObjectFactory.createGoomba(mEnemiesLayer)->setPosition(tiledMap.getGrid().getTilePosition({7, 12}));

	mGameObjectFactory.createCoin(mItemsLayer)->setPosition(tiledMap.getGrid().getTilePosition({10, 7}));
	mGameObjectFactory.createCoin(mItemsLayer)->setPosition(tiledMap.getGrid().getTilePosition({11, 7}));
	mGameObjectFactory.createCoin(mItemsLayer)->setPosition(tiledMap.getGrid().getTilePosition({12, 7}));
	mGameObjectFactory.createCoin(mItemsLayer)->setPosition(tiledMap.getGrid().getTilePosition({13, 7}));
	mGameObjectFactory.createCoin(mItemsLayer)->setPosition(tiledMap.getGrid().getTilePosition({10, 8}));
	mGameObjectFactory.createCoin(mItemsLayer)->setPosition(tiledMap.getGrid().getTilePosition({11, 8}));
	mGameObjectFactory.createCoin(mItemsLayer)->setPosition(tiledMap.getGrid().getTilePosition({12, 8}));
	mGameObjectFactory.createCoin(mItemsLayer)->setPosition(tiledMap.getGrid().getTilePosition({13, 8}));

	mGameObjectFactory.createQuestionMarkBox(mBlocksLayer)->setPosition(tiledMap.getGrid().getTilePosition({7, 7}));
	mGameObjectFactory.createQuestionMarkBox(mBlocksLayer)->setPosition(tiledMap.getGrid().getTilePosition({8, 7}));
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
