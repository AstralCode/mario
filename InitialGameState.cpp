#include "InitialGameState.hpp"

#include "GameContextData.hpp"
#include "GameStateChanger.hpp"
#include "RectangleShape.hpp"

InitialGameState::InitialGameState(GameContextData& contextData) noexcept :
	GameState{contextData},
	mGameObjectFactory{contextData.getResources(), contextData.getSpritesets(), contextData.getScene()}
{

}

void InitialGameState::onEnter() noexcept
{
	auto tilemap = std::make_unique<Tilemap>(15, 20, FloatSize{Constants::World::TileSize, Constants::World::TileSize});
	tilemap->getRow(0)  = Tilemap::Row{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	tilemap->getRow(1)  = Tilemap::Row{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	tilemap->getRow(2)  = Tilemap::Row{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  50,  51,   0,   0,   0,   0 };
	tilemap->getRow(3)	= Tilemap::Row{  0,   0,   0,   0,   0,   0,  50,  51,   0,   0,   0,   0,   0,   0,  64,  65,   0,   0,   0,   0 };
	tilemap->getRow(4)	= Tilemap::Row{  0,   0,   0,   0,   0,   0,  64,  65,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	tilemap->getRow(5)	= Tilemap::Row{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	tilemap->getRow(6)	= Tilemap::Row{ 51,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	tilemap->getRow(7)	= Tilemap::Row{ 65,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	tilemap->getRow(8)	= Tilemap::Row{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	tilemap->getRow(9)	= Tilemap::Row{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   6,   7,   0 };
	tilemap->getRow(10) = Tilemap::Row{  0,   0,  10,   0,   0,   0,   0,   5,   6,   7,   0,   0,   0,   0,   0,   0,   0,  47,   0,   0 };
	tilemap->getRow(11) = Tilemap::Row{  0,  23,  24,  25,   0,   0,   0,   0,  47,   0,   0,   0,   0,   0,   0,   0,   0,  47,   0,   0 };
	tilemap->getRow(12) = Tilemap::Row{ 23,  24,  39,  39,  25,  36,  37,  38,  47,   0,   0,  36,  37,  37,  37,  38,   0,  47,   0,   0 };
	tilemap->getRow(13) = Tilemap::Row{  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 };
	tilemap->getRow(14) = Tilemap::Row{  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 };

	const Tilemap::TileAttributes tileAttributes =
	{
		{1, {{Tile::Attributes::Collider}}},
		{2, {{Tile::Attributes::Collider}}},
		{3, {{Tile::Attributes::Collider}}},
		{5, {{Tile::Attributes::Collider}}},
		{6, {{Tile::Attributes::Collider}}},
		{7, {{Tile::Attributes::Collider}}},
		{47, {{Tile::Attributes::Collider}}}
	};

	tilemap->setTileAttributes(tileAttributes);

	auto& tilemapView = getScene().getTilemapView();
	tilemapView.setTilemap(std::move(tilemap));
	tilemapView.setTilemapTexture(getTexture(Textures::Scenery));
	tilemapView.setInformationText(getFont(Fonts::Roboto));
	tilemapView.setBackgroundColor({97, 133, 246});
	tilemapView.build();

	mGameObjectFactory.createMario()->setPosition(tilemapView.getTilePosition({12, 1}));

//	mGameObjectFactory.createGoomba()->setPosition(tilemapView.getTilePosition({12,  9}));
//	mGameObjectFactory.createGoomba()->setPosition(tilemapView.getTilePosition({12, 13}));
	mGameObjectFactory.createGoomba()->setPosition(tilemapView.getTilePosition({6, 9}));
}

void InitialGameState::onLeave() noexcept
{

}

void InitialGameState::processLogic(const sf::Time&) noexcept
{
	
}

void InitialGameState::onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept
{
	if (keyEvent.code == sf::Keyboard::F2)
	{
		getScene().getTilemapView().setGridVisible(!getScene().getTilemapView().isGridVisible());
	}
}

void InitialGameState::onEscapePressed() noexcept
{
	getStateChanger().clearStatesRequest();
}
