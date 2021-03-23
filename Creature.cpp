#include "Creature.hpp"

#include "CreatureMoveState.hpp"
#include "CreatureFallState.hpp"

Creature::Creature(const sf::Texture& texture, const SpritesetRegion& sprites) noexcept :
	mMoveAnimation{sprites}
{
	mMoveAnimation.setDuration(sf::seconds(Constants::World::Creature::MoveAnimationDuration));
	mMoveAnimation.setRepeating(true);

	mStates.registerState<CreatureMoveState>(Creature::States::Move);
	mStates.registerState<CreatureFallState>(Creature::States::Fall);

	setAttribute(Entity::Attributes::Movable);
	setAttribute(Entity::Attributes::Deadly);
	setTexture(texture);
	setState(Creature::States::Move);
}

void Creature::setState(const Creature::States identifier)
{
	mStates.setCurrentState(*this, identifier);
}

void Creature::setMoveAnimation() noexcept
{
	mMoveAnimation.play();

	setSpriteArea(mMoveAnimation.getCurrentSpriteArea());
}

void Creature::updateMoveAnimation(const sf::Time& dt) noexcept
{
	mMoveAnimation.update(dt);

	setSpriteArea(mMoveAnimation.getCurrentSpriteArea());
}

void Creature::update(const sf::Time& dt) noexcept
{
	mStates.getCurrentState().update(*this, dt);
}

void Creature::tileCollision(const Tile& tile, const Sides side) noexcept
{
	mStates.getCurrentState().tileCollision(*this, tile, side);
}

void Creature::entityCollision(const Entity& collider, const Sides side) noexcept
{
	mStates.getCurrentState().entityCollision(*this, collider, side);
}

void Creature::falling() noexcept
{
	mStates.getCurrentState().falling(*this);
}

bool Creature::isJumping() const noexcept
{
	return mStates.getCurrentState().isJumping();
}

bool Creature::isFalling() const noexcept
{
	return mStates.getCurrentState().isFalling();
}
