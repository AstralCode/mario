#include "Hero.hpp"

#include "ResourceContainer.hpp"
#include "SpritesetContainer.hpp"
#include "SpritesetRegion.hpp"
#include "SpritesetRegions.hpp"
#include "HeroStandState.hpp"
#include "HeroMoveState.hpp"
#include "HeroJumpState.hpp"
#include "HeroFallState.hpp"
#include "HeroLoseState.hpp"

Hero::Hero(const ResourceContainer& resources, const SpritesetContainer& spritesets) noexcept :
	mResources{resources},
	mSpritesets{spritesets},
	mJumpVelocity{0.0f},
	mMoveAnimation{spritesets.getMarioSpriteset().getRegion(MarioSpritesetRegionType::Move)},
	mStandSpriteArea{mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegionType::Stand).getSpriteArea(0)},
	mJumpSpriteArea{mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegionType::Jump).getSpriteArea(0)},
	mSlideSpriteArea{mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegionType::Slide).getSpriteArea(0)},
	mLoseSpriteArea{mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegionType::Lose).getSpriteArea(0)}
{
	mMoveAnimation.setDuration(sf::seconds(Constants::World::Hero::MoveAnimationDuration));
	mMoveAnimation.setRepeating(true);

	mStates.registerState<HeroStandState>();
	mStates.registerState<HeroMoveState>();
	mStates.registerState<HeroJumpState>();
	mStates.registerState<HeroFallState>();
	mStates.registerState<HeroLoseState>();

	setComponent(Entity::ComponentType::Mass);
	setComponent(Entity::ComponentType::Movement);
	setTexture(resources.getTexture(TextureId::Hero));
	setState<HeroStandState>();
}

void Hero::setJumpVelocity(const float velocity) noexcept
{
	mJumpVelocity = velocity;
}

void Hero::setMoveAnimation() noexcept
{
	mMoveAnimation.play();

	setSpriteArea(mMoveAnimation.getCurrentSpriteArea());
}

void Hero::updateMoveAnimation(const sf::Time& dt) noexcept
{
	mMoveAnimation.update(dt);

	setSpriteArea(mMoveAnimation.getCurrentSpriteArea());
}

void Hero::updateLoseAnimation(const sf::Time& dt) noexcept
{
	mLoseTime += dt;
}

void Hero::setStandSprite() noexcept
{
	setSpriteArea(mStandSpriteArea);
}

void Hero::setJumpSprite() noexcept
{
	setSpriteArea(mJumpSpriteArea);
}

void Hero::setSlideSprite() noexcept
{
	setSpriteArea(mSlideSpriteArea);
}

void Hero::setLoseSprite() noexcept
{
	setSpriteArea(mLoseSpriteArea);
}

void Hero::update(const sf::Time& dt) noexcept
{
	mStates.getState().update(*this, dt);
}

void Hero::collision(const Tile& tile, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, tile, side);
}

void Hero::collision(Entity& entity, const CollisionSideType side) const noexcept
{
	entity.collision(*this, side);
}

void Hero::collision(const Hero& hero, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, hero, side);
}

void Hero::collision(const Enemy& enemy, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, enemy, side);
}

void Hero::collision(const Item& item, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, item, side);
}

void Hero::falling() noexcept
{
	mStates.getState().falling(*this);
}

float Hero::getJumpVelocity() const noexcept
{
	return mJumpVelocity;
}

const sf::Time& Hero::getLoseTime() const noexcept
{
	return mLoseTime;
}

bool Hero::isJumping() const noexcept
{
	return mStates.getState().isJumping();
}

bool Hero::isFalling() const noexcept
{
	return mStates.getState().isFalling();
}

void Hero::onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept
{
	mStates.getState().onKeyPressed(*this, keyEvent);
}

void Hero::onKeyReleased(const sf::Event::KeyEvent& keyEvent) noexcept
{
	mStates.getState().onKeyReleased(*this, keyEvent);
}
