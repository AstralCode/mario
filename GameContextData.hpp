#pragma once

#include "SFML/System/NonCopyable.hpp"

class GameResourceManager;

class GameContextData final : private sf::NonCopyable
{
public:
	GameContextData(GameResourceManager& gameResourceManager);

	GameResourceManager& GetGameResourceManager() const;

private:
	GameResourceManager& mGameResourceManager;
};
