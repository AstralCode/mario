#include "GameContextData.hpp"

GameContextData::GameContextData(GraphicsItem& graphicsScene, GameResourceContainer& gameResourceContainer, GameObjectCreator& gameObjectCreator) :
	mGraphicsScene{graphicsScene},
	mGameResourceContainer{gameResourceContainer},
	mGameObjectCreator{gameObjectCreator}
{

}

GraphicsItem& GameContextData::getGraphicsScene()
{
	return mGraphicsScene;
}

GameResourceContainer& GameContextData::getResourceContainer()
{
	return mGameResourceContainer;
}

GameObjectCreator& GameContextData::getGameObjectCreator()
{
	return mGameObjectCreator;
}
