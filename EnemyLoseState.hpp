#pragma once

#include "EntityState.hpp"
#include "Enemy.hpp"

class EnemyLoseState final : public EntityState<Enemy>
{
public:
	void onSet(Enemy& entity) noexcept override;

	void update(Enemy& entity, const sf::Time& dt) noexcept override;

	void collision(Enemy& entity, const Tile& tile, const CollisionSideType side) noexcept override;

	void collision(Enemy& entity, const Hero& hero, const CollisionSideType side) noexcept override;
	void collision(Enemy& entity, const Enemy& enemy, const CollisionSideType side) noexcept override;
	void collision(Enemy& entity, const Item& item, const CollisionSideType side) noexcept override;

	void falling(Enemy& entity) noexcept override;

	void onKeyPressed(Enemy& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(Enemy& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;
};
