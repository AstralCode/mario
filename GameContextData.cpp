#include "GameContextData.hpp"

GameContextData::GameContextData(GraphicsItem& graphicsScene, GameResourceContainer& gameResourceContainer, GameSpriteAtlasManager& gameSpriteAtlasManager, GameObjectCreator& gameObjectCreator) :
	mGraphicsScene{graphicsScene},
	mGameResourceContainer{gameResourceContainer},
	mGameSpriteAtlasManager{gameSpriteAtlasManager},
	mGameObjectCreator{gameObjectCreator}
{

}

GraphicsItem& GameContextData::getGraphicsScene()
{
	return mGraphicsScene;
}

GameResourceContainer& GameContextData::getGameResourceContainer()
{
	return mGameResourceContainer;
}

GameSpriteAtlasManager& GameContextData::getGameSpriteAtlasManager()
{
	return mGameSpriteAtlasManager;
}

GameObjectCreator& GameContextData::getGameObjectCreator()
{
	return mGameObjectCreator;
}
