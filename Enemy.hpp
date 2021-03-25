#pragma once

#include "EntityStateMachine.hpp"
#include "Animation.hpp"

class Enemy final : public Entity
{
public:
	Enemy(const sf::Texture& texture, const SpritesetRegion& moveSprites, const IntArea& loseSpriteArea) noexcept;

	template <typename TState>
	void setState();

	void setMoveAnimation() noexcept;
	void updateMoveAnimation(const sf::Time& dt) noexcept;

	void setLoseSprite() noexcept;
	void updateLoseTime(const sf::Time& dt) noexcept;

	void update(const sf::Time& dt) noexcept override;

	void tileCollision(const Tile& tile, const CollisionSideType side) noexcept override;
	void entityCollision(const Entity& collider, const CollisionSideType side) noexcept override;

	void falling() noexcept override;

	const sf::Time& getLoseTime() const noexcept;

	bool isJumping() const noexcept override;
	bool isFalling() const noexcept override;

private:
	Animation mMoveAnimation;

	IntArea mLoseSpriteArea;

	sf::Time mLoseTime;

	EntityStateMachine<Enemy> mStates;
};

template <typename TState>
void Enemy::setState()
{
	mStates.setState<TState>(*this);
}
