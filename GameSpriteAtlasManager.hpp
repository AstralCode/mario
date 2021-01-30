#pragma once

#include <memory>

#include "GameSpriteAtlas.hpp"

class GameSpriteAtlasManager final
{
public:
	GameSpriteAtlas& createAtlas(const std::string& identifier);
	GameSpriteAtlas& getAtlas(const std::string& identifier) const;

private:
	std::unordered_map<std::string, std::unique_ptr<GameSpriteAtlas>> mSpriteAtlases;
};
