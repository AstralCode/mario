#include "Enemy.hpp"

#include "EnemyMoveState.hpp"
#include "EnemyFallState.hpp"
#include "EnemyLoseState.hpp"

Enemy::Enemy() noexcept
{
	mStates.registerState<EnemyMoveState>();
	mStates.registerState<EnemyFallState>();
	mStates.registerState<EnemyLoseState>();
}

void Enemy::setMoveAnimation(const Animation& animation) noexcept
{
	mMoveAnimation = animation;
}

void Enemy::setLoseAnimation(const Animation& animation) noexcept
{
	mLoseAnimation = animation;
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

void Enemy::setLoseAnimation() noexcept
{
	mLoseAnimation.play();
	setSpriteArea(mLoseAnimation.getCurrentSpriteArea());

	auto& spriteArea = mLoseAnimation.getCurrentSpriteArea();
	move(0.0f, Constants::World::Tilemap::TileSize - spriteArea.getHeight());
}

void Enemy::updateLoseAnimation(const sf::Time& dt) noexcept
{
	mLoseAnimation.update(dt);
	setSpriteArea(mLoseAnimation.getCurrentSpriteArea());

	mLoseTime += dt;
}

void Enemy::update(const sf::Time& dt) noexcept
{
	mStates.getState().update(*this, dt);
}

void Enemy::collision(const Tile& tile, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, tile, side);
}

void Enemy::collision(Entity& entity, const CollisionSideType side) const noexcept
{
	entity.collision(*this, side);
}

void Enemy::collision(const Hero& hero, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, hero, side);
}

void Enemy::collision(const Enemy& enemy, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, enemy, side);
}

void Enemy::collision(const Item& item, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, item, side);
}

void Enemy::falling() noexcept
{
	mStates.getState().falling(*this);
}

const sf::Time& Enemy::getLoseTime() const noexcept
{
	return mLoseTime;
}
