#pragma once

#include "EntityState.hpp"
#include "Coin.hpp"

class SpritesetRegion;

class CoinPickupState final : public EntityState<Coin>
{
public:
	void onSet(Coin& entity) noexcept override;

	void update(Coin& entity, const sf::Time& dt) noexcept override;

	void collision(Coin& entity, const Tile& tile, const CollisionSideType side) noexcept override;
	void collision(Coin& entity, const Entity& collider, const CollisionSideType side) noexcept override;

	void falling(Coin& entity) noexcept override;

	void onKeyPressed(Coin& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(Coin& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;
};
