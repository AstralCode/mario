#pragma once

#include "EntityStateMachine.hpp"
#include "Animation.hpp"
#include "ResourceContainer.hpp"
#include "SpritesetContainer.hpp"

class Mario final : public Entity
{
public:
	Mario(const ResourceContainer& resources, const SpritesetContainer& spritesets) noexcept;

	template <typename TState>
	void setState();

	void setMoveAnimation() noexcept;
	void updateMoveAnimation(const sf::Time& dt) noexcept;

	void setStandSprite() noexcept;
	void setJumpSprite() noexcept;
	void setSlideSprite() noexcept;

	void update(const sf::Time& dt) noexcept override;

	void tileCollision(const Tile& tile, const CollisionSideType side) noexcept override;
	void entityCollision(const Entity& collider, const CollisionSideType side) noexcept override;

	void falling() noexcept override;

	bool isJumping() const noexcept override;
	bool isFalling() const noexcept override;

protected:
	void onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(const sf::Event::KeyEvent& keyEvent) noexcept override;

private:
	const ResourceContainer& mResources;
	const SpritesetContainer& mSpritesets;

	Animation mMoveAnimation;

	EntityStateMachine<Mario> mStates;
};

template <typename TState>
void Mario::setState()
{
	mStates.setState<TState>(*this);
}
