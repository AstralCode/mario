#pragma once

#include "EntityState.hpp"
#include "QBox.hpp"

class SpritesetRegion;

class QBoxShineState final : public EntityState<QBox>
{
public:
	void onSet(QBox& entity) noexcept override;

	void update(QBox& entity, const sf::Time& dt) noexcept override;

	void collision(QBox& entity, const Tile& tile, const CollisionSideType side) noexcept override;
	void collision(QBox& entity, const Entity& collider, const CollisionSideType side) noexcept override;

	void falling(QBox& entity) noexcept override;

	void onKeyPressed(QBox& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(QBox& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;
};
