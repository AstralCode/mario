#pragma once

#include "EntityState.hpp"
#include "Creature.hpp"

class CreatureMoveState final : public EntityState<Creature>
{
public:
	void onSet(Creature& entity) noexcept;

	void update(Creature& entity, const sf::Time& dt) noexcept;

	void tileCollision(Creature& entity, const Tile& tile, const Tile::Sides side) noexcept;
	void entityCollision(Creature& entity, Creature& collider) noexcept;

	void falling() noexcept;

	bool isJumping() const noexcept;
	bool isFalling() const noexcept;
};
