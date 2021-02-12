#pragma once

#include <string>

class GameSpriteAtlas;

namespace SpriteAtlasIdentifiers
{
constexpr const auto Mario = "mario";
constexpr const auto Enemy = "enemy";
constexpr const auto Items = "items";
}

namespace SpriteAtlasRegionIdentifiers
{
namespace Mario
{
constexpr const auto Stand = "stand";
constexpr const auto Move = "move";
constexpr const auto Slide = "slide";
}

namespace Goomba
{
constexpr const auto Move = "move";
constexpr const auto Dead = "dead";
}
namespace Items
{
constexpr const auto Coin = "coin";
}
}

class GameSpriteAtlasContainer
{
public:
	virtual ~GameSpriteAtlasContainer() = default;

	virtual const GameSpriteAtlas& getAtlas(const std::string& identifier) const = 0;
};
