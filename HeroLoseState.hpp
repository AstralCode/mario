#pragma once

#include "EntityState.hpp"
#include "Hero.hpp"

class SpritesetRegion;

class HeroLoseState final : public EntityState<Hero>
{
public:
	void onSet(Hero& entity) noexcept override;

	void update(Hero& entity, const sf::Time& dt) noexcept override;

	void collision(Hero& entity, const Tile& tile, const CollisionSideType side) noexcept override;

	void collision(Hero& entity, const Hero& hero, const CollisionSideType side) noexcept override;
	void collision(Hero& entity, const Enemy& enemy, const CollisionSideType side) noexcept override;
	void collision(Hero& entity, const Item& item, const CollisionSideType side) noexcept override;

	void falling(Hero& entity) noexcept override;

	void onKeyPressed(Hero& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(Hero& entity, const sf::Event::KeyEvent& keyEvent) noexcept override;
};
