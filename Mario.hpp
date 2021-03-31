#pragma once

#include "EntityStateMachine.hpp"
#include "Animation.hpp"

class Mario final : public Entity
{
public:
	Mario(World& world) noexcept;

	template <typename TState>
	void setState();

	void playStandAnimation() noexcept;
	void updateStandAnimation(const sf::Time& dt) noexcept;

	void playMoveAnimation() noexcept;
	void updateMoveAnimation(const sf::Time& dt) noexcept;

	void playJumpAnimation() noexcept;
	void updateJumpAnimation(const sf::Time& dt) noexcept;

	void playSlideAnimation() noexcept;
	void updateSlideAnimation(const sf::Time& dt) noexcept;

	void playLoseAnimation() noexcept;
	void updateLoseAnimation(const sf::Time& dt) noexcept;

	void setJumpVelocity(const float velocity) noexcept;

	void update(const sf::Time& dt) noexcept override;

	void collision(const Tile& tile, const CollisionSideType side) noexcept override;
	void collision(const Entity& collider, const CollisionSideType side) noexcept override;

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

	EntityStateMachine<Mario> mStates;
};

template <typename TState>
void Mario::setState()
{
	mStates.setState<TState>(*this);
}
