#pragma once

#include "EntityState.hpp"
#include "Mario.hpp"

class SpritesetRegion;

class MarioMoveState final : public EntityState<Mario>
{
public:
	void onSet(Mario& entity) noexcept override;

	void update(Mario& entity, const sf::Time& dt) noexcept override;

	void collision(Mario& entity, const Tile& tile, const CollisionSideType side) noexcept override;
	void collision(Mario& entity, const Entity& collider, const CollisionSideType side) noexcept override;

	void falling(Mario& entity) noexcept override;

	void onKeyPressed(Mario& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(Mario& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;
};
