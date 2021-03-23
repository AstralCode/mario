#pragma once

#include "EntityStateMachine.hpp"
#include "Animation.hpp"

class Item final : public Entity
{
public:
	enum class States
	{
		Active
	};

	Item(const sf::Texture& texture, const SpritesetRegion& sprites) noexcept;

	void setState(const Item::States identifier);

	void setActiveAnimation() noexcept;
	void activeActiveAnimation(const sf::Time& dt) noexcept;

	void update(const sf::Time& dt) noexcept override;

	void tileCollision(const Tile& tile, const Sides side) noexcept override;
	void entityCollision(const Entity& collider, const Sides side) noexcept override;

	void falling() noexcept override;

	bool isJumping() const noexcept override;
	bool isFalling() const noexcept override;

private:
	Animation mActiveAnimation;

	EntityStateMachine<Item, Item::States> mStates;
};
