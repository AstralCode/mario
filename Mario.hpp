#pragma once

#include "EntityStateMachine.hpp"
#include "Animation.hpp"
#include "ResourceContainer.hpp"
#include "SpritesetContainer.hpp"

class Mario final : public Entity
{
public:
	enum class States
	{
		Stand,
		Move,
		Jump,
		Fall
	};

	Mario(const ResourceContainer& resources, const SpritesetContainer& spritesets) noexcept;

	void setState(const Mario::States identifier);

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

	EntityStateMachine<Mario, Mario::States> mStates;
};
