#pragma once

class GraphicsItem;
class GameResourceContainer;
class GameSpriteAtlasManager;
class GameObjectCreator;

class GameContextData final
{
public:
	GameContextData(GraphicsItem& graphicsScene, GameResourceContainer& gameResourceContainer, GameSpriteAtlasManager& gameSpriteAtlasManager, GameObjectCreator& gameObjectCreator);

	GraphicsItem& getGraphicsScene();
	GameResourceContainer& getGameResourceContainer();
	GameSpriteAtlasManager& getGameSpriteAtlasManager();
	GameObjectCreator& getGameObjectCreator();

private:
	GraphicsItem& mGraphicsScene;
	GameResourceContainer& mGameResourceContainer;
	GameSpriteAtlasManager& mGameSpriteAtlasManager;
	GameObjectCreator& mGameObjectCreator;
};
