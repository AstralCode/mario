#pragma once

#include "EntityStateMachine.hpp"
#include "Animation.hpp"

class Creature final : public Entity
{
public:
	Creature(const sf::Texture& texture, const SpritesetRegion& sprites) noexcept;

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

	EntityStateMachine<Creature> mStates;
};

template <typename TState>
void Creature::setState()
{
	mStates.setState<TState>(*this);
}
