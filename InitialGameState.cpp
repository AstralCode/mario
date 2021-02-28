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

	const std::vector<std::vector<TileIdentifier>> tileIdentifiers =
	{
		{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
		{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
		{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  50,  51,   0,   0,   0,   0 },
		{   0,   0,   0,   0,   0,   0,  50,  51,   0,   0,   0,   0,   0,   0,  64,  65,   0,   0,   0,   0 },
		{   0,   0,   0,   0,   0,   0,  64,  65,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
		{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
		{  51,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
		{  65,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
		{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
		{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   6,   7,   0 },
		{   0,   0,  10,   0,   0,   0,   0,   5,   6,   7,   0,   0,   0,   0,   0,   0,   0,  47,   0,   0 },
		{   0,  23,  24,  25,   0,   0,   0,   0,  47,   0,   0,   0,   0,   0,   0,   0,   0,  47,   0,   0 },
		{  23,  24,  39,  39,  25,  36,  37,  38,  47,   0,   0,  36,  37,  37,  37,  38,   0,  47,   0,   0 },
		{   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 },
		{   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }
	};

	auto& tilemapView = getTilemapView();
	tilemapView.setInformationText(getFont(FontIdentifiers::Roboto));
	tilemapView.setTilesetTexture(&getTexture(TextureIdentifiers::Scenery));
	tilemapView.setTileAttributes(tileAttributes);
	tilemapView.setTileIdentifiers(tileIdentifiers);
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
