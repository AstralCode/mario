#pragma once

#include "EntityState.hpp"
#include "Goomba.hpp"

class GoombaFallState final : public EntityState<Goomba>
{
public:
	void onSet(Goomba& entity) noexcept override;

	void update(Goomba& entity, const sf::Time& dt) noexcept override;

	void collision(Goomba& entity, const Tile& tile, const CollisionSideType side) noexcept override;
	void collision(Goomba& entity, const Entity& collider, const CollisionSideType side) noexcept override;

	void falling(Goomba& entity) noexcept override;

	void onKeyPressed(Goomba& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(Goomba& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;
};
