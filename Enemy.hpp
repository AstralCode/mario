#pragma once

#include "EntityStateMachine.hpp"
#include "Animation.hpp"

class Enemy final : public Entity
{
public:
	Enemy(const sf::Texture& texture, const SpritesetRegion& sprites) noexcept;

	template <typename TState>
	void setState();

	void setMoveAnimation() noexcept;
	void updateMoveAnimation(const sf::Time& dt) noexcept;

	void update(const sf::Time& dt) noexcept override;

	void tileCollision(const Tile& tile, const CollisionSideType side) noexcept override;
	void entityCollision(const Entity& collider, const CollisionSideType side) noexcept override;

	void falling() noexcept override;

	bool isJumping() const noexcept override;
	bool isFalling() const noexcept override;

private:
	Animation mMoveAnimation;

	EntityStateMachine<Enemy> mStates;
};

template <typename TState>
void Enemy::setState()
{
	mStates.setState<TState>(*this);
}
