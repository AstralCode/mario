#include "InitialGameState.hpp"

#include "GameContextData.hpp"
#include "GameStateChanger.hpp"
#include "GraphicsRectangleItem.hpp"

InitialGameState::InitialGameState(GameContextData& gameContextData, GameStateChanger& gameStateChanger) noexcept :
	GameState{gameContextData, gameStateChanger},
	mGameObjectFactory{gameContextData.getResourceContainer(), gameContextData.getSpritesetContainer(), gameContextData.getGameObjectCreator()}
{

}

void InitialGameState::onEnter() noexcept
{
	auto tilemap = std::make_unique<Tilemap>(20, 15);
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

	const std::map<TileIdentifier, TileAttributeFlags> tileAttributes =
	{
		{1, {{TileAttributes::Collider}}},
		{2, {{TileAttributes::Collider}}},
		{3, {{TileAttributes::Collider}}},
		{5, {{TileAttributes::Collider}}},
		{6, {{TileAttributes::Collider}}},
		{7, {{TileAttributes::Collider}}},
		{47, {{TileAttributes::Collider}}}
	};

	tilemap->setAttributes(tileAttributes);

	auto& tilemapView = getTilemapView();
	tilemapView.setTilemap(std::move(tilemap));
	tilemapView.setTilemapTexture(getTexture(TextureIdentifiers::Scenery));
	tilemapView.setInformationText(getFont(FontIdentifiers::Roboto));
	tilemapView.setBackgroundColor({97, 133, 246});
	tilemapView.build({32, 32});

	mGameObjectFactory.createMario()->setPosition(tilemapView.getTileArea({4, 12}).getCenter());
	mGameObjectFactory.createGoomba()->setPosition(tilemapView.getTileArea({11, 12}).getCenter());
	mGameObjectFactory.createGoomba()->setPosition(tilemapView.getTileArea({13, 12}).getCenter());
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
		getTilemapView().setGridVisible(!getTilemapView().isGridVisible());
	}
}

void InitialGameState::onEscapePressed() noexcept
{
	mGameStateChanger.clearStatesRequest();
}
