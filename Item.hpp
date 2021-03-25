#pragma once

#include "EntityStateMachine.hpp"
#include "Animation.hpp"

class Item final : public Entity
{
public:
	Item(const sf::Texture& texture, const SpritesetRegion& sprites) noexcept;

	template <typename TState>
	void setState();

	void setActiveAnimation() noexcept;
	void updateActiveAnimation(const sf::Time& dt) noexcept;

	void setPickupAnimation() noexcept;
	void updatePickupAnimation(const sf::Time& dt) noexcept;

	void update(const sf::Time& dt) noexcept override;

	void tileCollision(const Tile& tile, const CollisionSideType side) noexcept override;
	void entityCollision(const Entity& collider, const CollisionSideType side) noexcept override;

	void falling() noexcept override;

	bool isJumping() const noexcept override;
	bool isFalling() const noexcept override;

private:
	Animation mActiveAnimation;
	Animation mPickupAnimation;

	EntityStateMachine<Item> mStates;
};

template <typename TState>
void Item::setState()
{
	mStates.setState<TState>(*this);
}
