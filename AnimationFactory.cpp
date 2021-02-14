#include "AnimationFactory.hpp"

#include "Animation.hpp"
#include "GameResourceContainer.hpp"
#include "GameSpriteAtlasContainer.hpp"
#include "GameSpriteAtlas.hpp"

AnimationFactory::AnimationFactory(GameResourceContainer& gameResourceContainer, GameSpriteAtlasContainer& gameSpriteAtlasContainer) noexcept :
	mGameResourceContainer{gameResourceContainer},
	mGameSpriteAtlasContainer{gameSpriteAtlasContainer}
{

}

std::unique_ptr<Animation> AnimationFactory::createMarioMove() const noexcept
{
	auto animation = create(SpriteAtlasIdentifiers::Mario, SpriteAtlasRegionIdentifiers::Mario::Move);
	animation->setDuration(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Normal);
	animation->setRepeating(true);
	animation->stop();
	animation->play();

	return animation;
}

std::unique_ptr<Animation> AnimationFactory::createGoombaMove() const noexcept
{
	auto animation = create(SpriteAtlasIdentifiers::Enemy, SpriteAtlasRegionIdentifiers::Goomba::Move);
	animation->setDuration(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Normal);
	animation->setRepeating(true);
	animation->stop();
	animation->play();

	return animation;
}

std::unique_ptr<Animation> AnimationFactory::createCoinShine() const noexcept
{
	auto animation = create(SpriteAtlasIdentifiers::Items, SpriteAtlasRegionIdentifiers::Items::Coin);
	animation->setDuration(sf::seconds(0.25f));
	animation->setDelay(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Alternate);
	animation->setRepeating(true);
	animation->stop();
	animation->play();

	return animation;
}

std::unique_ptr<Animation> AnimationFactory::createQuestionMarkBoxShine() const noexcept
{
	auto animation = create(SpriteAtlasIdentifiers::Blocks, SpriteAtlasRegionIdentifiers::Blocks::QuestionMarkBox);
	animation->setDuration(sf::seconds(0.25f));
	animation->setDelay(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Alternate);
	animation->setRepeating(true);
	animation->stop();
	animation->play();

	return animation;
}

std::unique_ptr<Animation> AnimationFactory::create(const std::string& atlasIdentifier, const std::string& regionIdentifier) const noexcept
{
	return std::make_unique<Animation>(mGameSpriteAtlasContainer.getAtlas(atlasIdentifier).getRegion(regionIdentifier));
}
