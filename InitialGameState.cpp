#include "InitialGameState.hpp"

#include "GameContextData.hpp"
#include "GameStateChanger.hpp"
#include "World.hpp"
#include "Mario.hpp"
#include "Creature.hpp"

InitialGameState::InitialGameState(GameContextData& contextData, GameStateChanger& stateChanger) noexcept :
	GameState{contextData, stateChanger},
	mResources{contextData.getResources()},
	mSpritesets{contextData.getSpritesets()},
	mWorld{contextData.getWorld()}
{

}

void InitialGameState::onEnter() noexcept
{
	auto tilemap = std::make_unique<Tilemap>(15, 20, FloatSize{Constants::World::Tilemap::TileSize, Constants::World::Tilemap::TileSize});
	tilemap->getRow(0)  = Tilemap::Row{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	tilemap->getRow(1)  = Tilemap::Row{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	tilemap->getRow(2)  = Tilemap::Row{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  50,  51,   0,   0,   0,   0 };
	tilemap->getRow(3)	= Tilemap::Row{  0,   0,   0,   0,   0,   0,  50,  51,   0,   0,   0,   0,   0,   0,  64,  65,   0,   0,   0,   0 };
	tilemap->getRow(4)	= Tilemap::Row{  0,   0,   0,   0,   0,   0,  64,  65,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	tilemap->getRow(5)	= Tilemap::Row{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	tilemap->getRow(6)	= Tilemap::Row{ 51,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	tilemap->getRow(7)	= Tilemap::Row{ 65,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	tilemap->getRow(8)	= Tilemap::Row{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	tilemap->getRow(9)	= Tilemap::Row{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   6,   7,   0,   0,   0,   0,   0 };
	tilemap->getRow(10) = Tilemap::Row{  0,   0,  10,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  47,   0,   0,   0,   0,   0,   0 };
	tilemap->getRow(11) = Tilemap::Row{  0,  23,  24,  25,   0,   0,   0,   5,   6,   7,   0,   0,   0,  47,   0,   0,   0,   0,   0,   0 };
	tilemap->getRow(12) = Tilemap::Row{ 23,  24,  39,  39,  25,  36,  37,  38,  47,  36,  37,  37,  38,  47,   0,  36,  37,  38,   0,  23 };
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

	auto& tilemapView = getContextData().getWorld().getTilemapView();
	tilemapView.setTilemap(std::move(tilemap));
	tilemapView.setTilemapTexture(mResources.getTexture(Textures::Scenery));
	tilemapView.setInformationText(mResources.getFont(Fonts::Roboto));
	tilemapView.setBackgroundColor({97, 133, 246});
	tilemapView.build();

	auto mario = mWorld.getEntities().create<Mario>(mResources.getTexture(Textures::Mario), mSpritesets.getMarioSpriteset());
	mario->setPosition(tilemapView.getTilePosition({12, 1}));

	mWorld.getEntities().create<Creature>(mResources.getTexture(Textures::Enemies), mSpritesets.getGoombaSpriteset().getRegion(GoombaSpritesetRegions::Move))->setPosition(tilemapView.getTilePosition({12,  9}));
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
		mWorld.getTilemapView().setGridVisible(!mWorld.getTilemapView().isGridVisible());
	}
}

void InitialGameState::onEscapePressed() noexcept
{
	getStateChanger().clearStatesRequest();
}
