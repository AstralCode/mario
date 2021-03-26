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
	mMoveAnimation{spritesets.getMarioSpriteset().getRegion(MarioSpritesetRegions::Move)},
	mStandSpriteArea{mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegions::Stand).getSpriteArea(0)},
	mJumpSpriteArea{mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegions::Jump).getSpriteArea(0)},
	mSlideSpriteArea{mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegions::Slide).getSpriteArea(0)},
	mLoseSpriteArea{mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegions::Lose).getSpriteArea(0)}
{
	mMoveAnimation.setDuration(sf::seconds(Constants::World::Hero::MoveAnimationDuration));
	mMoveAnimation.setRepeating(true);

	mStates.registerState<HeroStandState>();
	mStates.registerState<HeroMoveState>();
	mStates.registerState<HeroJumpState>();
	mStates.registerState<HeroFallState>();
	mStates.registerState<HeroLoseState>();

	setAttribute(Entity::Attributes::Destroyer);
	setAttribute(Entity::Attributes::Movable);
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

void Hero::tileCollision(const Tile& tile, const CollisionSideType side) noexcept
{
	mStates.getState().tileCollision(*this, tile, side);
}

void Hero::entityCollision(const Entity& collider, const CollisionSideType side) noexcept
{
	mStates.getState().entityCollision(*this, collider, side);
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
