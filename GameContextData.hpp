#pragma once

class GraphicsItem;
class GameResourceContainer;
class GameObjectCreator;

class GameContextData final
{
public:
	GameContextData(GraphicsItem& graphicsScene, GameResourceContainer& gameResourceContainer, GameObjectCreator& gameObjectCreator);

	GraphicsItem& getGraphicsScene();
	GameResourceContainer& getResourceContainer();
	GameObjectCreator& getGameObjectCreator();

private:
	GraphicsItem& mGraphicsScene;
	GameResourceContainer& mGameResourceContainer;
	GameObjectCreator& mGameObjectCreator;
};
