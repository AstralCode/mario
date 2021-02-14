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

	std::unique_ptr<Animation> createMarioMove() const noexcept;
	std::unique_ptr<Animation> createGoombaMove() const noexcept;
	std::unique_ptr<Animation> createCoinShine() const noexcept;
	std::unique_ptr<Animation> createQuestionMarkBoxShine() const noexcept;

private:
	std::unique_ptr<Animation> create(const std::string& atlasIdentifier, const std::string& regionIdentifier) const noexcept;

	GameResourceContainer& mGameResourceContainer;
	GameSpriteAtlasContainer& mGameSpriteAtlasContainer;
};
