#include "Creature.hpp"

#include "CreatureMoveState.hpp"
#include "CreatureFallState.hpp"

Creature::Creature(const sf::Texture& texture, const SpritesetRegion& sprites) noexcept :
	mMoveAnimation{sprites}
{
	setTexture(texture);

	mMoveAnimation.setDuration(sf::seconds(Constants::World::Creature::MoveAnimationDuration));
	mMoveAnimation.setRepeating(true);

	mStates.registerState<CreatureMoveState>(Creature::States::Move);
	mStates.registerState<CreatureFallState>(Creature::States::Fall);

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

void Creature::tileCollision(const Tile& tile, const Tile::Sides side) noexcept
{
	mStates.getCurrentState().tileCollision(*this, tile, side);
}

void Creature::entityCollision(Entity& collider) noexcept
{
	mStates.getCurrentState().entityCollision(*this, collider);
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
