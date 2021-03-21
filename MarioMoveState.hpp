#pragma once

#include "EntityState.hpp"
#include "Mario.hpp"

class SpritesetRegion;

class MarioMoveState final : public EntityState<Mario>
{
public:
	void onSet(Mario& entity) noexcept override;

	void update(Mario& entity, const sf::Time& dt) noexcept override;

	void tileCollision(Mario& entity, const Tile& tile, const Tile::Sides side) noexcept override;
	void entityCollision(Mario& entity, Entity& collider) noexcept override;

	void falling(Mario& entity) noexcept override;

	void onKeyPressed(Mario& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(Mario& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;

	bool isJumping() const noexcept override;
	bool isFalling() const noexcept override;
};
