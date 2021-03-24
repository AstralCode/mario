#pragma once

#include "EntityState.hpp"
#include "Item.hpp"

class SpritesetRegion;

class ItemActiveState final : public EntityState<Item>
{
public:
	void onSet(Item& entity) noexcept override;

	void update(Item& entity, const sf::Time& dt) noexcept override;

	void tileCollision(Item& entity, const Tile& tile, const CollisionSideType side) noexcept override;
	void entityCollision(Item& entity, const Entity& collider, const CollisionSideType side) noexcept override;

	void falling(Item& entity) noexcept override;

	void onKeyPressed(Item& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(Item& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;

	bool isJumping() const noexcept override;
	bool isFalling() const noexcept override;
};
