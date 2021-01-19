#include "GameContextData.hpp"

GameContextData::GameContextData(GameResourceManager& gameResourceManager) :
	mGameResourceManager{gameResourceManager}
{

}

GameResourceManager& GameContextData::GetGameResourceManager() const
{
	return mGameResourceManager;
}
