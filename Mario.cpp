#include "Mario.hpp"

#include "ResourceContainer.hpp"
#include "SpritesetContainer.hpp"
#include "SpritesetRegion.hpp"
#include "SpritesetRegions.hpp"
#include "MarioStandState.hpp"
#include "MarioMoveState.hpp"
#include "MarioJumpState.hpp"
#include "MarioFallState.hpp"
#include "MarioLoseState.hpp"

Mario::Mario(const ResourceContainer& resources, const SpritesetContainer& spritesets) noexcept :
	mResources{resources},
	mSpritesets{spritesets},
	mJumpVelocity{0.0f},
	mMoveAnimation{spritesets.getMarioSpriteset().getRegion(MarioSpritesetRegions::Move)},
	mStandSpriteArea{mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegions::Stand).getSpriteArea(0)},
	mJumpSpriteArea{mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegions::Jump).getSpriteArea(0)},
	mSlideSpriteArea{mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegions::Slide).getSpriteArea(0)},
	mLoseSpriteArea{mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegions::Lose).getSpriteArea(0)}
{
	mMoveAnimation.setDuration(sf::seconds(Constants::World::Mario::MoveAnimationDuration));
	mMoveAnimation.setRepeating(true);

	mStates.registerState<MarioStandState>();
	mStates.registerState<MarioMoveState>();
	mStates.registerState<MarioJumpState>();
	mStates.registerState<MarioFallState>();
	mStates.registerState<MarioLoseState>();

	setAttribute(Entity::Attributes::Destroyer);
	setAttribute(Entity::Attributes::Movable);
	setTexture(resources.getTexture(TextureId::Mario));

	setState<MarioStandState>();
}

void Mario::setJumpVelocity(const float velocity) noexcept
{
	mJumpVelocity = velocity;
}

void Mario::setMoveAnimation() noexcept
{
	mMoveAnimation.play();

	setSpriteArea(mMoveAnimation.getCurrentSpriteArea());
}

void Mario::updateMoveAnimation(const sf::Time& dt) noexcept
{
	mMoveAnimation.update(dt);

	setSpriteArea(mMoveAnimation.getCurrentSpriteArea());
}

void Mario::updateLoseAnimation(const sf::Time& dt) noexcept
{
	mLoseTime += dt;
}

void Mario::setStandSprite() noexcept
{
	setSpriteArea(mStandSpriteArea);
}

void Mario::setJumpSprite() noexcept
{
	setSpriteArea(mJumpSpriteArea);
}

void Mario::setSlideSprite() noexcept
{
	setSpriteArea(mSlideSpriteArea);
}

void Mario::setLoseSprite() noexcept
{
	setSpriteArea(mLoseSpriteArea);
}

void Mario::update(const sf::Time& dt) noexcept
{
	mStates.getState().update(*this, dt);
}

void Mario::tileCollision(const Tile& tile, const CollisionSideType side) noexcept
{
	mStates.getState().tileCollision(*this, tile, side);
}

void Mario::entityCollision(const Entity& collider, const CollisionSideType side) noexcept
{
	mStates.getState().entityCollision(*this, collider, side);
}

void Mario::falling() noexcept
{
	mStates.getState().falling(*this);
}

float Mario::getJumpVelocity() const noexcept
{
	return mJumpVelocity;
}

const sf::Time& Mario::getLoseTime() const noexcept
{
	return mLoseTime;
}

bool Mario::isJumping() const noexcept
{
	return mStates.getState().isJumping();
}

bool Mario::isFalling() const noexcept
{
	return mStates.getState().isFalling();
}

void Mario::onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept
{
	mStates.getState().onKeyPressed(*this, keyEvent);
}

void Mario::onKeyReleased(const sf::Event::KeyEvent& keyEvent) noexcept
{
	mStates.getState().onKeyReleased(*this, keyEvent);
}
