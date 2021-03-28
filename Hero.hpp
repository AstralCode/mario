#pragma once

#include "EntityStateMachine.hpp"
#include "Animation.hpp"

class Hero final : public Entity
{
public:
	Hero() noexcept;

	template <typename TState>
	void setState();

	void setStandAnimation(const Animation& animation) noexcept;
	void setMoveAnimation(const Animation& animation) noexcept;
	void setJumpAnimation(const Animation& animation) noexcept;
	void setSlideAnimation(const Animation& animation) noexcept;
	void setLoseAnimation(const Animation& animation) noexcept;

	void setStandAnimation() noexcept;
	void updateStandAnimation(const sf::Time& dt) noexcept;

	void setMoveAnimation() noexcept;
	void updateMoveAnimation(const sf::Time& dt) noexcept;

	void setJumpAnimation() noexcept;
	void updateJumpAnimation(const sf::Time& dt) noexcept;

	void setSlideAnimation() noexcept;
	void updateSlideAnimation(const sf::Time& dt) noexcept;

	void setLoseAnimation() noexcept;
	void updateLoseAnimation(const sf::Time& dt) noexcept;

	void setJumpVelocity(const float velocity) noexcept;

	void update(const sf::Time& dt) noexcept override;

	void collision(const Tile& tile, const CollisionSideType side) noexcept override;
	void collision(Entity& entity, const CollisionSideType side) const noexcept override;

	void collision(const Hero& hero, const CollisionSideType side) noexcept override;
	void collision(const Enemy& enemy, const CollisionSideType side) noexcept override;
	void collision(const Item& item, const CollisionSideType side) noexcept override;

	void falling() noexcept override;

	float getJumpVelocity() const noexcept;

	const sf::Time& getLoseTime() const noexcept;

protected:
	void onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(const sf::Event::KeyEvent& keyEvent) noexcept override;

private:
	Animation mStandAnimation;
	Animation mMoveAnimation;
	Animation mJumpAnimation;
	Animation mSlideAnimation;
	Animation mLoseAnimation;

	float mJumpVelocity;

	sf::Time mLoseTime;

	EntityStateMachine<Hero> mStates;
};

template <typename TState>
void Hero::setState()
{
	mStates.setState<TState>(*this);
}
