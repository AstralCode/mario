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

	void setMoveAnimation() noexcept;
	void updateMoveAnimation(const sf::Time& dt) noexcept;

	void update(const sf::Time& dt) noexcept override;

	void tileCollision(const Tile& tile, const Tile::Sides side) noexcept override;
	void entityCollision(Entity& collider) noexcept override;

	void falling() noexcept override;

	bool isJumping() const noexcept override;
	bool isFalling() const noexcept override;

private:
	Animation mShineAnimation;

	EntityStateMachine<Item, Item::States> mStates;
};
