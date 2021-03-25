#include "Mario.hpp"

#include "ResourceContainer.hpp"
#include "SpritesetContainer.hpp"
#include "SpritesetRegion.hpp"
#include "SpritesetRegions.hpp"
#include "MarioStandState.hpp"
#include "MarioMoveState.hpp"
#include "MarioJumpState.hpp"
#include "MarioFallState.hpp"

Mario::Mario(const ResourceContainer& resources, const SpritesetContainer& spritesets) noexcept :
	mResources{resources},
	mSpritesets{spritesets},
	mMoveAnimation{spritesets.getMarioSpriteset().getRegion(MarioSpritesetRegions::Move)}
{
	mMoveAnimation.setDuration(sf::seconds(Constants::World::Mario::MoveAnimationDuration));
	mMoveAnimation.setRepeating(true);

	mStates.registerState<MarioStandState>();
	mStates.registerState<MarioMoveState>();
	mStates.registerState<MarioJumpState>();
	mStates.registerState<MarioFallState>();

	setAttribute(Entity::Attributes::Movable);
	setTexture(resources.getTexture(TextureId::Mario));

	setState<MarioStandState>();
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

void Mario::setStandSprite() noexcept
{
	setSpriteArea(mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegions::Stand).getSpriteArea(0));
}

void Mario::setJumpSprite() noexcept
{
	setSpriteArea(mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegions::Jump).getSpriteArea(0));
}

void Mario::setSlideSprite() noexcept
{
	setSpriteArea(mSpritesets.getMarioSpriteset().getRegion(MarioSpritesetRegions::Slide).getSpriteArea(0));
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
