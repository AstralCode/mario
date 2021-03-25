#include "Enemy.hpp"

#include "EnemyMoveState.hpp"
#include "EnemyFallState.hpp"

Enemy::Enemy(const sf::Texture& texture, const SpritesetRegion& sprites) noexcept :
	mMoveAnimation{sprites}
{
	mMoveAnimation.setDuration(sf::seconds(Constants::World::Enemy::MoveAnimationDuration));
	mMoveAnimation.setRepeating(true);

	mStates.registerState<EnemyMoveState>();
	mStates.registerState<EnemyFallState>();

	setAttribute(Entity::Attributes::Movable);
	setAttribute(Entity::Attributes::Deadly);
	setTexture(texture);

	setState<EnemyMoveState>();
}

void Enemy::setMoveAnimation() noexcept
{
	mMoveAnimation.play();

	setSpriteArea(mMoveAnimation.getCurrentSpriteArea());
}

void Enemy::updateMoveAnimation(const sf::Time& dt) noexcept
{
	mMoveAnimation.update(dt);

	setSpriteArea(mMoveAnimation.getCurrentSpriteArea());
}

void Enemy::update(const sf::Time& dt) noexcept
{
	mStates.getState().update(*this, dt);
}

void Enemy::tileCollision(const Tile& tile, const CollisionSideType side) noexcept
{
	mStates.getState().tileCollision(*this, tile, side);
}

void Enemy::entityCollision(const Entity& collider, const CollisionSideType side) noexcept
{
	mStates.getState().entityCollision(*this, collider, side);
}

void Enemy::falling() noexcept
{
	mStates.getState().falling(*this);
}

bool Enemy::isJumping() const noexcept
{
	return mStates.getState().isJumping();
}

bool Enemy::isFalling() const noexcept
{
	return mStates.getState().isFalling();
}
