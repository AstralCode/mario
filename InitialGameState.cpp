#include "InitialGameState.hpp"

#include "ResourceContainer.hpp"
#include "GameStateChanger.hpp"
#include "ResourceIdentifiers.hpp"

InitialGameState::InitialGameState(GameStateChanger& stateChanger, World& world) noexcept :
	GameState{stateChanger, world}
{

}

void InitialGameState::onEnter() noexcept
{
	auto& world = getWorld();

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

	world.setTilemapTexture(TextureId::Scenery);
	world.setTilemapBackground({97, 133, 246});
	world.setTilemap(std::move(tilemap));

	world.spawnMario(TileIndex{12, 1});
	world.spawnGoomba(TileIndex{12,  8});

	world.getTilemapView().addOnMouseClick([this](auto point, auto button)
	{
		auto& world = getWorld();

		if (button == sf::Mouse::Button::Left)
		{
			if (!world.isTileEmpty(point))
			{
				world.removeEntity(point);
			}
			else
			{
				world.putCoin(point);
			}
			
		}
		else if (button == sf::Mouse::Button::Right)
		{
			if (!world.isTileEmpty(point))
			{
				world.removeEntity(point);
			}
			else
			{
				world.putQBox(point);
			}
		}
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
	auto& world = getWorld();

	if (keyEvent.code == sf::Keyboard::F1)
	{
		world.spawnMario(TileIndex{12, 1});
	}
	else if (keyEvent.code == sf::Keyboard::F2)
	{
		world.getTilemapView().setGridVisible(!world.getTilemapView().isGridVisible());
	}
}

void InitialGameState::onEscapePressed() noexcept
{
	getStateChanger().clearStatesRequest();
}
