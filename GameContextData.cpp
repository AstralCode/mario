#include "GameContextData.hpp"

GameContextData::GameContextData(GameResourceManager& gameResourceManager) :
	mGameResourceManager{gameResourceManager}
{

}

GameResourceManager& GameContextData::getResourceManager()
{
	return mGameResourceManager;
}
