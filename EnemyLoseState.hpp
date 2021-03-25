#pragma once

#include "EntityState.hpp"
#include "Enemy.hpp"

class EnemyLoseState final : public EntityState<Enemy>
{
public:
	void onSet(Enemy& entity) noexcept override;

	void update(Enemy& entity, const sf::Time& dt) noexcept override;

	void tileCollision(Enemy& entity, const Tile& tile, const CollisionSideType side) noexcept override;
	void entityCollision(Enemy& entity, const Entity& collider, const CollisionSideType side) noexcept override;

	void falling(Enemy& entity) noexcept override;

	void onKeyPressed(Enemy& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(Enemy& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;

	bool isJumping() const noexcept override;
	bool isFalling() const noexcept override;
};
