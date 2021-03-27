#pragma once

#include "EntityStateMachine.hpp"
#include "Animation.hpp"

class Item final : public Entity
{
public:
	Item(const sf::Texture& texture, const SpritesetRegion& activeSprites, const SpritesetRegion& pickupSprites) noexcept;

	template <typename TState>
	void setState();

	void setActiveAnimation() noexcept;
	void updateActiveAnimation(const sf::Time& dt) noexcept;

	void setPickupAnimation() noexcept;
	void updatePickupAnimation(const sf::Time& dt) noexcept;

	void update(const sf::Time& dt) noexcept override;

	void collision(const Tile& tile, const CollisionSideType side) noexcept override;
	void collision(Entity& entity, const CollisionSideType side) const noexcept override;

	void collision(const Hero& hero, const CollisionSideType side) noexcept override;
	void collision(const Enemy& enemy, const CollisionSideType side) noexcept override;
	void collision(const Item& item, const CollisionSideType side) noexcept override;

	void falling() noexcept override;

	const sf::Time& getPickupTime() const noexcept;

	bool isJumping() const noexcept override;
	bool isFalling() const noexcept override;

private:
	Animation mActiveAnimation;
	Animation mPickupAnimation;

	sf::Time mPickupAnimationTime;

	EntityStateMachine<Item> mStates;
};

template <typename TState>
void Item::setState()
{
	mStates.setState<TState>(*this);
}
