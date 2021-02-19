#include "InitialGameState.hpp"

#include "GameContextData.hpp"
#include "GameStateChanger.hpp"
#include "GraphicsRectangleItem.hpp"

InitialGameState::InitialGameState(GameContextData& gameContextData, GameStateChanger& gameStateChanger) :
	GameState{gameContextData, gameStateChanger},
	mGameObjectFactory{gameContextData.getResourceContainer(), gameContextData.getSpritesetContainer(), gameContextData.getGameObjectCreator()},
	mGoomba{nullptr}
{

}

void InitialGameState::onEnter()
{
	const std::unordered_map<unsigned int, Flags<TileAttributes>> tileAttributes =
	{
		{1, {{TileAttributes::Solid, TileAttributes::Visible}}}
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
		{ 000, 000, 000, 000, 120, 121, 122, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 138, 139, 140, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000,  51, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000,  47,  48,  50, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{  47,  48,  49,  48,  50, 000, 000, 000, 000, 000, 000,  44,  45,  45,  45,  46, 000, 000, 000, 000 },
		{ 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001 },
		{ 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001, 001 }
	};

	auto& tilemap = getTilemap();
	tilemap.setTilesetTexture(&getTexture(TextureIdentifiers::Scenery));
	tilemap.setTileAttributes(tileAttributes);
	tilemap.setTileIdentifiers(tileIdentifiers);
	tilemap.setBackgroundColor({97, 133, 246});
	tilemap.build({32u, 32u});

	mGameObjectFactory.createScoreCoin()->setPosition(tilemap.getTileCenterPosition({2, 0}));

	mGameObjectFactory.createMario()->setPosition(tilemap.getTileCenterPosition({2, 12}));

	(mGoomba = mGameObjectFactory.createGoomba())->setPosition(tilemap.getTileCenterPosition({5, 12}));
	mGameObjectFactory.createGoomba()->setPosition(tilemap.getTileCenterPosition({7, 12}));

	mGameObjectFactory.createCoin()->setPosition(tilemap.getTileCenterPosition({10, 7}));
	mGameObjectFactory.createCoin()->setPosition(tilemap.getTileCenterPosition({11, 7}));
	mGameObjectFactory.createCoin()->setPosition(tilemap.getTileCenterPosition({12, 7}));
	mGameObjectFactory.createCoin()->setPosition(tilemap.getTileCenterPosition({13, 7}));
	mGameObjectFactory.createCoin()->setPosition(tilemap.getTileCenterPosition({10, 8}));
	mGameObjectFactory.createCoin()->setPosition(tilemap.getTileCenterPosition({11, 8}));
	mGameObjectFactory.createCoin()->setPosition(tilemap.getTileCenterPosition({12, 8}));
	mGameObjectFactory.createCoin()->setPosition(tilemap.getTileCenterPosition({13, 8}));

	mGameObjectFactory.createQuestionMarkBox()->setPosition(tilemap.getTileCenterPosition({7, 7}));
	mGameObjectFactory.createQuestionMarkBox()->setPosition(tilemap.getTileCenterPosition({8, 7}));
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
	else if (keyEvent.code == sf::Keyboard::F3)
	{
		auto deadState = std::make_unique<GameObjectState>(getSpritesetContainer().getSpriteset(SpritesetIdentifiers::Enemy));
		
		mGoomba->setState(std::move(deadState));
		mGoomba->setTextureArea(getSpritesetContainer().getSpriteset(SpritesetIdentifiers::Enemy).getRegion(SpritesetRegionIdentifiers::Goomba::Dead).getSpriteArea(0));
	}
}

void InitialGameState::onEscapePressed()
{
	mGameStateChanger.clearStatesRequest();
}
