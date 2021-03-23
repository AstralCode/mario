#pragma once

#include "EntityStateMachine.hpp"
#include "Animation.hpp"

class Creature final : public Entity
{
public:
	enum class States
	{
		Move,
		Fall
	};

	Creature(const sf::Texture& texture, const SpritesetRegion& sprites) noexcept;

	void setState(const Creature::States identifier);

	void setMoveAnimation() noexcept;
	void updateMoveAnimation(const sf::Time& dt) noexcept;

	void update(const sf::Time& dt) noexcept override;

	void tileCollision(const Tile& tile, const Sides side) noexcept override;
	void entityCollision(const Entity& collider, const Sides side) noexcept override;

	void falling() noexcept override;

	bool isJumping() const noexcept override;
	bool isFalling() const noexcept override;

private:
	Animation mMoveAnimation;

	EntityStateMachine<Creature, Creature::States> mStates;
};
