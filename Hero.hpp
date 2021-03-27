#pragma once

#include "EntityStateMachine.hpp"
#include "ResourceContainer.hpp"
#include "SpritesetContainer.hpp"
#include "Animation.hpp"

class Hero final : public Entity
{
public:
	Hero(const ResourceContainer& resources, const SpritesetContainer& spritesets) noexcept;

	template <typename TState>
	void setState();

	void setJumpVelocity(const float velocity) noexcept;

	void setMoveAnimation() noexcept;
	void updateMoveAnimation(const sf::Time& dt) noexcept;

	void updateLoseAnimation(const sf::Time& dt) noexcept;

	void setStandSprite() noexcept;
	void setJumpSprite() noexcept;
	void setSlideSprite() noexcept;
	void setLoseSprite() noexcept;

	void update(const sf::Time& dt) noexcept override;

	void collision(const Tile& tile, const CollisionSideType side) noexcept override;
	void collision(Entity& entity, const CollisionSideType side) const noexcept override;

	void collision(const Hero& hero, const CollisionSideType side) noexcept override;
	void collision(const Enemy& enemy, const CollisionSideType side) noexcept override;
	void collision(const Item& item, const CollisionSideType side) noexcept override;

	void falling() noexcept override;

	float getJumpVelocity() const noexcept;

	const sf::Time& getLoseTime() const noexcept;

	bool isJumping() const noexcept override;
	bool isFalling() const noexcept override;

protected:
	void onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(const sf::Event::KeyEvent& keyEvent) noexcept override;

private:
	const ResourceContainer& mResources;
	const SpritesetContainer& mSpritesets;

	Animation mMoveAnimation;

	IntArea mStandSpriteArea;
	IntArea mJumpSpriteArea;
	IntArea mSlideSpriteArea;
	IntArea mLoseSpriteArea;

	float mJumpVelocity;

	sf::Time mLoseTime;

	EntityStateMachine<Hero> mStates;
};

template <typename TState>
void Hero::setState()
{
	mStates.setState<TState>(*this);
}
