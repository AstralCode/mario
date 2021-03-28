#include "Hero.hpp"

#include "HeroStandState.hpp"
#include "HeroMoveState.hpp"
#include "HeroJumpState.hpp"
#include "HeroFallState.hpp"
#include "HeroLoseState.hpp"

Hero::Hero() noexcept :
	mJumpVelocity{0.0f}
{
	mStates.registerState<HeroStandState>();
	mStates.registerState<HeroMoveState>();
	mStates.registerState<HeroJumpState>();
	mStates.registerState<HeroFallState>();
	mStates.registerState<HeroLoseState>();
}

void Hero::setStandAnimation(const Animation& animation) noexcept
{
	mStandAnimation = animation;
}

void Hero::setMoveAnimation(const Animation& animation) noexcept
{
	mMoveAnimation = animation;
}

void Hero::setJumpAnimation(const Animation& animation) noexcept
{
	mJumpAnimation = animation;
}

void Hero::setSlideAnimation(const Animation& animation) noexcept
{
	mSlideAnimation = animation;
}

void Hero::setLoseAnimation(const Animation& animation) noexcept
{
	mLoseAnimation = animation;
}

void Hero::setStandAnimation() noexcept
{
	mStandAnimation.play();

	setSpriteArea(mStandAnimation.getCurrentSpriteArea());
}

void Hero::updateStandAnimation(const sf::Time& dt) noexcept
{
	mStandAnimation.update(dt);

	setSpriteArea(mStandAnimation.getCurrentSpriteArea());
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

void Hero::setJumpAnimation() noexcept
{
	mJumpAnimation.play();

	setSpriteArea(mJumpAnimation.getCurrentSpriteArea());
}

void Hero::updateJumpAnimation(const sf::Time& dt) noexcept
{
	mJumpAnimation.update(dt);

	setSpriteArea(mJumpAnimation.getCurrentSpriteArea());
}

void Hero::setSlideAnimation() noexcept
{
	mSlideAnimation.play();

	setSpriteArea(mSlideAnimation.getCurrentSpriteArea());
}

void Hero::updateSlideAnimation(const sf::Time& dt) noexcept
{
	mSlideAnimation.update(dt);

	setSpriteArea(mSlideAnimation.getCurrentSpriteArea());
}

void Hero::setLoseAnimation() noexcept
{
	mLoseAnimation.play();

	setSpriteArea(mLoseAnimation.getCurrentSpriteArea());
}

void Hero::updateLoseAnimation(const sf::Time& dt) noexcept
{
	mLoseAnimation.update(dt);
	mLoseTime += dt;

	setSpriteArea(mLoseAnimation.getCurrentSpriteArea());
}

void Hero::setJumpVelocity(const float velocity) noexcept
{
	mJumpVelocity = velocity;
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

void Hero::onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept
{
	mStates.getState().onKeyPressed(*this, keyEvent);
}

void Hero::onKeyReleased(const sf::Event::KeyEvent& keyEvent) noexcept
{
	mStates.getState().onKeyReleased(*this, keyEvent);
}
