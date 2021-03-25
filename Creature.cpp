#include "Creature.hpp"

#include "CreatureMoveState.hpp"
#include "CreatureFallState.hpp"

Creature::Creature(const sf::Texture& texture, const SpritesetRegion& sprites) noexcept :
	mMoveAnimation{sprites}
{
	mMoveAnimation.setDuration(sf::seconds(Constants::World::Creature::MoveAnimationDuration));
	mMoveAnimation.setRepeating(true);

	mStates.registerState<CreatureMoveState>();
	mStates.registerState<CreatureFallState>();

	setAttribute(Entity::Attributes::Movable);
	setAttribute(Entity::Attributes::Deadly);
	setTexture(texture);

	setState<CreatureMoveState>();
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
	mStates.getState().update(*this, dt);
}

void Creature::tileCollision(const Tile& tile, const CollisionSideType side) noexcept
{
	mStates.getState().tileCollision(*this, tile, side);
}

void Creature::entityCollision(const Entity& collider, const CollisionSideType side) noexcept
{
	mStates.getState().entityCollision(*this, collider, side);
}

void Creature::falling() noexcept
{
	mStates.getState().falling(*this);
}

bool Creature::isJumping() const noexcept
{
	return mStates.getState().isJumping();
}

bool Creature::isFalling() const noexcept
{
	return mStates.getState().isFalling();
}
