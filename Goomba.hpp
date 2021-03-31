#pragma once

#include "EntityStateMachine.hpp"
#include "Animation.hpp"

class Goomba final : public Entity
{
public:
	Goomba(World& world) noexcept;

	template <typename TState>
	void setState();

	void playMoveAnimation() noexcept;
	void updateMoveAnimation(const sf::Time& dt) noexcept;

	void playLoseAnimation() noexcept;
	void updateLoseAnimation(const sf::Time& dt) noexcept;

	void update(const sf::Time& dt) noexcept override;

	void collision(const Tile& tile, const CollisionSideType side) noexcept override;
	void collision(const Entity& collider, const CollisionSideType side) noexcept override;

	void falling() noexcept override;

	const sf::Time& getLoseTime() const noexcept;

private:
	Animation mMoveAnimation;
	Animation mLoseAnimation;

	sf::Time mLoseTime;

	EntityStateMachine<Goomba> mStates;
};

template <typename TState>
void Goomba::setState()
{
	mStates.setState<TState>(*this);
}
