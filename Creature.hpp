#pragma once

#include "Entity.hpp"
#include "Animation.hpp"

class Creature final : public Entity
{
public:
	void update(const sf::Time& dt) noexcept;

	void tileCollision(const Tile& tile, const Tile::Sides side) noexcept;
	void entityCollision(Creature& entity, Entity& collider) noexcept;

	void falling() noexcept;

	Animation& getMoveAnimation() noexcept;

	bool isJumping() const noexcept;
	bool isFalling() const noexcept;

private:
	Animation mMoveAnimation;
};
