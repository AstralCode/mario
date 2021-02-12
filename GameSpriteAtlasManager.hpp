#pragma once

#include <memory>

#include "GameSpriteAtlasContainer.hpp"
#include "GameSpriteAtlas.hpp"

class GameSpriteAtlasManager final : public GameSpriteAtlasContainer
{
public:
	GameSpriteAtlas& createAtlas(const std::string& identifier);
	const GameSpriteAtlas& getAtlas(const std::string& identifier) const override;

private:
	std::unordered_map<std::string, std::unique_ptr<GameSpriteAtlas>> mSpriteAtlases;
};
