#pragma once

#include "EntityState.hpp"
#include "Hero.hpp"

class SpritesetRegion;

class HeroLoseState final : public EntityState<Hero>
{
public:
	void onSet(Hero& entity) noexcept override;

	void update(Hero& entity, const sf::Time& dt) noexcept override;

	void tileCollision(Hero& entity, const Tile& tile, const CollisionSideType side) noexcept override;
	void entityCollision(Hero& entity, const Entity& collider, const CollisionSideType side) noexcept override;

	void falling(Hero& entity) noexcept override;

	void onKeyPressed(Hero& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(Hero& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;

	bool isJumping() const noexcept override;
	bool isFalling() const noexcept override;
};
