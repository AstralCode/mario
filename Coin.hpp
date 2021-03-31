#pragma once

#include "EntityStateMachine.hpp"
#include "Animation.hpp"

class Coin final : public Entity
{
public:
	Coin(World& world) noexcept;

	template <typename TState>
	void setState();

	void playActiveAnimation() noexcept;
	void updateActiveAnimation(const sf::Time& dt) noexcept;

	void playPickupAnimation() noexcept;
	void updatePickupAnimation(const sf::Time& dt) noexcept;

	void update(const sf::Time& dt) noexcept override;

	void collision(const Tile& tile, const CollisionSideType side) noexcept override;
	void collision(const Entity& collider, const CollisionSideType side) noexcept override;

	void falling() noexcept override;

	const sf::Time& getPickupTime() const noexcept;

private:
	Animation mActiveAnimation;
	Animation mPickupAnimation;

	sf::Time mPickupAnimationTime;

	EntityStateMachine<Coin> mStates;
};

template <typename TState>
void Coin::setState()
{
	mStates.setState<TState>(*this);
}
