#include "Mario.hpp"

#include "MarioStandState.hpp"
#include "MarioMoveState.hpp"
#include "MarioJumpState.hpp"
#include "MarioFallState.hpp"
#include "MarioLoseState.hpp"

#include "World.hpp"
#include "ResourceContainer.hpp"
#include "SpritesetContainer.hpp"

Mario::Mario(World& world) noexcept :
	Entity{EntityType::Hero, world},
	mJumpVelocity{0.0f}
{
	mStates.registerState<MarioStandState>();
	mStates.registerState<MarioMoveState>();
	mStates.registerState<MarioJumpState>();
	mStates.registerState<MarioFallState>();
	mStates.registerState<MarioLoseState>();

	auto& resources = world.getResources();
	auto& spritesets = world.getSpritesets();

	setTexture(resources.getTexture(TextureId::Mario));
	setComponent(Entity::ComponentType::Mass);
	setComponent(Entity::ComponentType::Movement);

	mStandAnimation.setSpriteset(spritesets.getMarioSpriteset().getRegion(MarioSpritesetRegionType::Stand));

	mMoveAnimation.setSpriteset(spritesets.getMarioSpriteset().getRegion(MarioSpritesetRegionType::Move));
	mMoveAnimation.setDuration(sf::seconds(0.25f));
	mMoveAnimation.setRepeating(true);

	mJumpAnimation.setSpriteset(spritesets.getMarioSpriteset().getRegion(MarioSpritesetRegionType::Jump));
	mSlideAnimation.setSpriteset(spritesets.getMarioSpriteset().getRegion(MarioSpritesetRegionType::Slide));
	mLoseAnimation.setSpriteset(spritesets.getMarioSpriteset().getRegion(MarioSpritesetRegionType::Lose));

	setState<MarioStandState>();
}

void Mario::playStandAnimation() noexcept
{
	mStandAnimation.play();
	setSpriteArea(mStandAnimation.getCurrentSpriteArea());
}

void Mario::updateStandAnimation(const sf::Time& dt) noexcept
{
	mStandAnimation.update(dt);
	setSpriteArea(mStandAnimation.getCurrentSpriteArea());
}

void Mario::playMoveAnimation() noexcept
{
	mMoveAnimation.play();
	setSpriteArea(mMoveAnimation.getCurrentSpriteArea());
}

void Mario::updateMoveAnimation(const sf::Time& dt) noexcept
{
	mMoveAnimation.update(dt);
	setSpriteArea(mMoveAnimation.getCurrentSpriteArea());
}

void Mario::playJumpAnimation() noexcept
{
	mJumpAnimation.play();
	setSpriteArea(mJumpAnimation.getCurrentSpriteArea());
}

void Mario::updateJumpAnimation(const sf::Time& dt) noexcept
{
	mJumpAnimation.update(dt);
	setSpriteArea(mJumpAnimation.getCurrentSpriteArea());
}

void Mario::playSlideAnimation() noexcept
{
	mSlideAnimation.play();
	setSpriteArea(mSlideAnimation.getCurrentSpriteArea());
}

void Mario::updateSlideAnimation(const sf::Time& dt) noexcept
{
	mSlideAnimation.update(dt);
	setSpriteArea(mSlideAnimation.getCurrentSpriteArea());
}

void Mario::playLoseAnimation() noexcept
{
	mLoseAnimation.play();
	setSpriteArea(mLoseAnimation.getCurrentSpriteArea());
}

void Mario::updateLoseAnimation(const sf::Time& dt) noexcept
{
	mLoseAnimation.update(dt);
	setSpriteArea(mLoseAnimation.getCurrentSpriteArea());

	mLoseTime += dt;
}

void Mario::setJumpVelocity(const float velocity) noexcept
{
	mJumpVelocity = velocity;
}

void Mario::update(const sf::Time& dt) noexcept
{
	mStates.getState().update(*this, dt);
}

void Mario::collision(const Tile& tile, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, tile, side);
}

void Mario::collision(const Entity& entity, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, entity, side);
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

void Mario::onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept
{
	mStates.getState().onKeyPressed(*this, keyEvent);
}

void Mario::onKeyReleased(const sf::Event::KeyEvent& keyEvent) noexcept
{
	mStates.getState().onKeyReleased(*this, keyEvent);
}
