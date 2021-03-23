#pragma once

#include "EntityState.hpp"
#include "Creature.hpp"

class CreatureMoveState final : public EntityState<Creature>
{
public:
	void onSet(Creature& entity) noexcept override;

	void update(Creature& entity, const sf::Time& dt) noexcept override;

	void tileCollision(Creature& entity, const Tile& tile, const Sides side) noexcept override;
	void entityCollision(Creature& entity, const Entity& collider, const Sides side) noexcept override;

	void falling(Creature& entity) noexcept override;

	void onKeyPressed(Creature& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(Creature& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;

	bool isJumping() const noexcept override;
	bool isFalling() const noexcept override;
};
