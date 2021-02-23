#include "InitialGameState.hpp"

#include "GameContextData.hpp"
#include "GameStateChanger.hpp"
#include "GraphicsRectangleItem.hpp"

InitialGameState::InitialGameState(GameContextData& gameContextData, GameStateChanger& gameStateChanger) :
	GameState{gameContextData, gameStateChanger},
	mGameObjectFactory{gameContextData.getResourceContainer(), gameContextData.getSpritesetContainer(), gameContextData.getGameObjectCreator()}
{

}

void InitialGameState::onEnter()
{
	const std::map<unsigned int, Flags<TileAttributes>> tileAttributes =
	{
		{1u, {{TileAttributes::Solid}}},
		{2u, {{TileAttributes::Solid}}},
		{3u, {{TileAttributes::Solid}}},
		{50u, {{TileAttributes::Solid}}},
		{51u, {{TileAttributes::Solid}}},
		{52u, {{TileAttributes::Solid}}},
		{70u, {{TileAttributes::Solid}}}
	};

	const std::vector<std::vector<unsigned int>> tileIdentifiers =
	{
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,  50,  51,  51,  51,  52 },
		{ 000, 000,  45, 000, 000, 000, 000,  50,  51,  52, 000, 000, 000, 000, 000, 000, 000,  70, 000, 000 },
		{ 000,  41,  42,  44, 000, 000, 000, 000,  70, 000, 000, 000, 000, 000, 000, 000, 000,  70, 000, 000 },
		{  41,  43,  43,  42,  44, 000, 000, 000,  70, 000, 000,  38,  39,  39,  39,  40, 000,  70, 000, 000 },
		{ 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001 },
		{ 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001 }
	};

	auto& tilemap = getTilemap();
	tilemap.setInformationText(getFont(FontIdentifiers::Roboto));
	tilemap.setTilesetTexture(&getTexture(TextureIdentifiers::Scenery));
	tilemap.setTileAttributes(tileAttributes);
	tilemap.setTileIdentifiers(tileIdentifiers);
	tilemap.setBackgroundColor({97, 133, 246});
	tilemap.build({32u, 32u});

	//mGameObjectFactory.createScoreCoin()->setPosition(tilemap.getTileCenterPosition({0, 0}));

	mGameObjectFactory.createMario()->setPosition(tilemap.getTileCenterPosition({2, 12}));

	//mGameObjectFactory.createGoomba()->setPosition(tilemap.getTileCenterPosition({5, 12}));
	//mGameObjectFactory.createGoomba()->setPosition(tilemap.getTileCenterPosition({7, 12}));

	//mGameObjectFactory.createCoin()->setPosition(tilemap.getTileCenterPosition({10, 7}));
	//mGameObjectFactory.createCoin()->setPosition(tilemap.getTileCenterPosition({11, 7}));
	//mGameObjectFactory.createCoin()->setPosition(tilemap.getTileCenterPosition({12, 7}));
	//mGameObjectFactory.createCoin()->setPosition(tilemap.getTileCenterPosition({13, 7}));
	//mGameObjectFactory.createCoin()->setPosition(tilemap.getTileCenterPosition({10, 8}));
	//mGameObjectFactory.createCoin()->setPosition(tilemap.getTileCenterPosition({11, 8}));
	//mGameObjectFactory.createCoin()->setPosition(tilemap.getTileCenterPosition({12, 8}));
	//mGameObjectFactory.createCoin()->setPosition(tilemap.getTileCenterPosition({13, 8}));

	//mGameObjectFactory.createQuestionMarkBox()->setPosition(tilemap.getTileCenterPosition({8, 6}));
	//mGameObjectFactory.createQuestionMarkBox()->setPosition(tilemap.getTileCenterPosition({17, 5}));
}

void InitialGameState::onLeave()
{

}

void InitialGameState::processLogic(const sf::Time&)
{
	
}

void InitialGameState::onKeyPressed(const sf::Event::KeyEvent& keyEvent)
{
	if (keyEvent.code == sf::Keyboard::F2)
	{
		getTilemap().setGridVisible(!getTilemap().isGridVisible());
	}
}

void InitialGameState::onEscapePressed()
{
	mGameStateChanger.clearStatesRequest();
}
