#include "Enemy.hpp"

#include "EnemyMoveState.hpp"
#include "EnemyFallState.hpp"
#include "EnemyLoseState.hpp"

Enemy::Enemy(const sf::Texture& texture, const SpritesetRegion& moveSprites, const IntArea& loseSpriteArea) noexcept :
	mMoveAnimation{moveSprites},
	mLoseSpriteArea{loseSpriteArea}
{
	mMoveAnimation.setDuration(sf::seconds(Constants::World::Enemy::MoveAnimationDuration));
	mMoveAnimation.setRepeating(true);

	mStates.registerState<EnemyMoveState>();
	mStates.registerState<EnemyFallState>();
	mStates.registerState<EnemyLoseState>();

	setComponent(Entity::ComponentType::Mass);
	setComponent(Entity::ComponentType::Movement);
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

void Enemy::setLoseSprite() noexcept
{
	setSpriteArea(mLoseSpriteArea);

	move(0.0f, Constants::World::Tilemap::TileSize - mLoseSpriteArea.getHeight());
}

void Enemy::updateLoseTime(const sf::Time& dt) noexcept
{
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

bool Enemy::isJumping() const noexcept
{
	return mStates.getState().isJumping();
}

bool Enemy::isFalling() const noexcept
{
	return mStates.getState().isFalling();
}
