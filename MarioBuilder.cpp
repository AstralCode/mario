#include "MarioBuilder.hpp"

#include "ResourceContainer.hpp"
#include "ResourceIdentifiers.hpp"
#include "SpritesetContainer.hpp"
#include "SpritesetRegionIdentifiers.hpp"
#include "EntityContainer.hpp"
#include "HeroStandState.hpp"

MarioBuilder::MarioBuilder(const ResourceContainer& resources, const SpritesetContainer& spritesets) noexcept :
	mResources{resources},
	mSpritesets{spritesets},
	mMario{nullptr}
{

}

void MarioBuilder::create(EntityContainer& heroes) noexcept
{
	mMario = heroes.create<Hero>();
}

void MarioBuilder::buildTexture() noexcept
{
	mMario->setTexture(mResources.getTexture(TextureId::Hero));
}

void MarioBuilder::buildComponents() noexcept
{
	mMario->setComponent(Entity::ComponentType::Mass);
	mMario->setComponent(Entity::ComponentType::Movement);
}

void MarioBuilder::buildStandAnimation() noexcept
{
	Animation animation;
	animation.setSpriteset(mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegionType::Stand));
	animation.setDuration(sf::seconds(0.0f));
	animation.setRepeating(false);

	mMario->setStandAnimation(animation);
}

void MarioBuilder::buildMoveAnimation() noexcept
{
	Animation animation;
	animation.setSpriteset(mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegionType::Move));
	animation.setDuration(sf::seconds(0.25f));
	animation.setRepeating(true);

	mMario->setMoveAnimation(animation);
}

void MarioBuilder::buildJumpAnimation() noexcept
{
	Animation animation;
	animation.setSpriteset(mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegionType::Move));
	animation.setDuration(sf::seconds(0.0f));
	animation.setRepeating(true);

	mMario->setJumpAnimation(animation);
}

void MarioBuilder::buildSlideAnimation() noexcept
{
	Animation animation;
	animation.setSpriteset(mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegionType::Slide));
	animation.setDuration(sf::seconds(0.0f));
	animation.setRepeating(false);

	mMario->setSlideAnimation(animation);
}

void MarioBuilder::buildLoseAnimation() noexcept
{
	Animation animation;
	animation.setSpriteset(mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegionType::Lose));
	animation.setDuration(sf::seconds(0.0f));
	animation.setRepeating(false);

	mMario->setLoseAnimation(animation);
}

void MarioBuilder::buildState() noexcept
{
	mMario->setState<HeroStandState>();
}

Hero* MarioBuilder::getHero() const noexcept
{
	return mMario;
}
