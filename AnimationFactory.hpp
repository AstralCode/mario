#pragma once

#include <memory>
#include <string>

class Animation;
class GameResourceContainer;
class GameSpriteAtlasContainer;

class AnimationFactory final
{
public:
	AnimationFactory(GameResourceContainer& gameResourceContainer, GameSpriteAtlasContainer& gameSpriteAtlasContainer) noexcept;

	std::unique_ptr<Animation> createMarioMove() noexcept;
	std::unique_ptr<Animation> createGoombaMove() noexcept;
	std::unique_ptr<Animation> createCoinShine() noexcept;

private:
	std::unique_ptr<Animation> create(const std::string& atlasIdentifier, const std::string& regionIdentifier) noexcept;

	GameResourceContainer& mGameResourceContainer;
	GameSpriteAtlasContainer& mGameSpriteAtlasContainer;
};
