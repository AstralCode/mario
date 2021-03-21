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
	setTexture(resources.getTexture(Textures::Mario));

	mMoveAnimation.setDuration(sf::seconds(Constants::World::Mario::MoveAnimationDuration));
	mMoveAnimation.setRepeating(true);

	mStates.registerState<MarioStandState>(Mario::States::Stand);
	mStates.registerState<MarioMoveState>(Mario::States::Move);
	mStates.registerState<MarioJumpState>(Mario::States::Jump);
	mStates.registerState<MarioFallState>(Mario::States::Fall);

	setState(Mario::States::Stand);
}

void Mario::setState(const Mario::States identifier)
{
	mStates.setCurrentState(*this, identifier);
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
	mStates.getCurrentState().update(*this, dt);
}

void Mario::tileCollision(const Tile& tile, const Tile::Sides side) noexcept
{
	mStates.getCurrentState().tileCollision(*this, tile, side);
}

void Mario::entityCollision(Entity& collider) noexcept
{
	mStates.getCurrentState().entityCollision(*this, collider);
}

void Mario::falling() noexcept
{
	mStates.getCurrentState().falling(*this);
}

bool Mario::isJumping() const noexcept
{
	return mStates.getCurrentState().isJumping();
}

bool Mario::isFalling() const noexcept
{
	return mStates.getCurrentState().isFalling();
}

void Mario::onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept
{
	mStates.getCurrentState().onKeyPressed(*this, keyEvent);
}

void Mario::onKeyReleased(const sf::Event::KeyEvent& keyEvent) noexcept
{
	mStates.getCurrentState().onKeyReleased(*this, keyEvent);
}
