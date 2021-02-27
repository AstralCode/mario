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
		{1, {{TileAttributes::Solid}}},
		{2, {{TileAttributes::Solid}}},
		{3, {{TileAttributes::Solid}}},
		{50, {{TileAttributes::Solid}}},
		{51, {{TileAttributes::Solid}}},
		{52, {{TileAttributes::Solid}}},
		{70, {{TileAttributes::Solid}}}
	};

	const std::vector<std::vector<TileIdentifier>> tileIdentifiers =
	{
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,  46,  47, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000,  46,  47, 000, 000, 000, 000, 000, 000,  61,  62, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000,  61,  62, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 },
		{ 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,  50,  51,  52, 000, 000, 000, 000, 000 },
		{ 000, 000,  45, 000, 000, 000, 000,  50,  51,  52, 000, 000, 000, 000, 000, 000, 000,  70, 000, 000, 000, 000, 000, 000 },
		{ 000,  41,  42,  44, 000, 000, 000, 000,  70, 000, 000, 000, 000, 000, 000, 000, 000,  70, 000, 000, 000, 000, 000, 000 },
		{  41,  43,  43,  42,  44,  38,  39,  40,  70, 000, 000,  38,  39,  39,  39,   40, 000,  70, 000, 000, 000, 000, 000, 000 },
		{   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 },
		{   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }
	};

	auto& tilemap = getTilemap();
	tilemap.setInformationText(getFont(FontIdentifiers::Roboto));
	tilemap.setTilesetTexture(&getTexture(TextureIdentifiers::Scenery));
	tilemap.setTileAttributes(tileAttributes);
	tilemap.setTileIdentifiers(tileIdentifiers);
	tilemap.setBackgroundColor({97, 133, 246});
	tilemap.build({32, 32});

	mGameObjectFactory.createMario()->setPosition(tilemap.getTileArea({4, 12}).getCenter());
	
	mGameObjectFactory.createGoomba()->setPosition(tilemap.getTileArea({11, 12}).getCenter());
	mGameObjectFactory.createGoomba()->setPosition(tilemap.getTileArea({13, 12}).getCenter());
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
		getTilemap().setGridVisible(!getTilemap().isGridVisible());
	}
}

void InitialGameState::onEscapePressed() noexcept
{
	mGameStateChanger.clearStatesRequest();
}
