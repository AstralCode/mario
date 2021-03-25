#include "InitialGameState.hpp"

#include "GameStateChanger.hpp"
#include "ResourceIdentifiers.hpp"

InitialGameState::InitialGameState(GameStateChanger& stateChanger, World& world) noexcept :
	GameState{stateChanger, world}
{

}

void InitialGameState::onEnter() noexcept
{
	auto tilemap = std::make_unique<Tilemap>(15, 20, FloatSize{Constants::World::Tilemap::TileSize, Constants::World::Tilemap::TileSize});
	tilemap->setTileIdentifiers(
		{
			{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
			{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
			{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  50,  51,   0,   0,   0,   0 },
			{  0,   0,   0,   0,   0,   0,  50,  51,   0,   0,   0,   0,   0,   0,  64,  65,   0,   0,   0,   0 },
			{  0,   0,   0,   0,   0,   0,  64,  65,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
			{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  50 },
			{ 51,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  64 },
			{ 65,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
			{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
			{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   6,   7,   0,   0 },
			{  0,   0,  10,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  47,   0,   0,   0 },
			{  0,  23,  24,  25,   0,   0,   5,   6,   7,   0,   5,   6,   7,   0,   0,   0,  47,   0,   0,   0 },
			{ 23,  24,  39,  39,  25,   0,   0,  47,  36,  37,  38,  47,   0,   0,  36,  38,  47,   0,   0,  23 },
			{  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 },
			{  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }
		});

	tilemap->setTileColliders({1, 2, 3, 5, 6, 7, 47});

	auto& world = getWorld();
	world.setTilemap(std::move(tilemap), TextureId::Scenery, FontId::Roboto, {97, 133, 246});
	world.spawnMario({12, 1});
	world.spawnGoomba({12,  8});
	world.spawnGoomba({12,  10});

	world.putCoin({9, 7});
	world.putCoin({8, 8});
	world.putCoin({7, 9});
	world.putCoin({8, 10});
	world.putCoin({9, 11});

	world.getTilemapView().addOnMouseClick([&world](auto point, auto)
	{
		world.putCoin(world.getTilemapView().getTile(point).index);
	});
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
		auto& world = getWorld();

		world.getTilemapView().setGridVisible(!world.getTilemapView().isGridVisible());
	}
}

void InitialGameState::onEscapePressed() noexcept
{
	getStateChanger().clearStatesRequest();
}
