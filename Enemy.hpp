#pragma once

#include "EntityStateMachine.hpp"
#include "Animation.hpp"

class Enemy final : public Entity
{
public:
	Enemy() noexcept;

	template <typename TState>
	void setState();

	void setMoveAnimation(const Animation& animation) noexcept;
	void setLoseAnimation(const Animation& animation) noexcept;

	void setMoveAnimation() noexcept;
	void updateMoveAnimation(const sf::Time& dt) noexcept;

	void setLoseAnimation() noexcept;
	void updateLoseAnimation(const sf::Time& dt) noexcept;

	void update(const sf::Time& dt) noexcept override;

	void collision(const Tile& tile, const CollisionSideType side) noexcept override;
	void collision(Entity& entity, const CollisionSideType side) const noexcept override;

	void collision(const Hero& hero, const CollisionSideType side) noexcept override;
	void collision(const Enemy& enemy, const CollisionSideType side) noexcept override;
	void collision(const Item& item, const CollisionSideType side) noexcept override;

	void falling() noexcept override;

	const sf::Time& getLoseTime() const noexcept;

private:
	Animation mMoveAnimation;
	Animation mLoseAnimation;

	sf::Time mLoseTime;

	EntityStateMachine<Enemy> mStates;
};

template <typename TState>
void Enemy::setState()
{
	mStates.setState<TState>(*this);
}
