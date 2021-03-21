#pragma once

#include "EntityStateMachine.hpp"
#include "Spriteset.hpp"
#include "SpritesetRegions.hpp"
#include "Animation.hpp"

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

	Mario(const sf::Texture& texture, const Spriteset<MarioSpritesetRegions>& spriteset) noexcept;

	void setState(const Mario::States identifier);

	void setMoveAnimation() noexcept;
	void updateMoveAnimation(const sf::Time& dt) noexcept;

	void setStandSprite() noexcept;
	void setJumpSprite() noexcept;
	void setSlideSprite() noexcept;

	void update(const sf::Time& dt) noexcept override;

	void tileCollision(const Tile& tile, const Tile::Sides side) noexcept override;
	void entityCollision(Entity& collider) noexcept override;

	void falling() noexcept override;

	bool isJumping() const noexcept override;
	bool isFalling() const noexcept override;

protected:
	void onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(const sf::Event::KeyEvent& keyEvent) noexcept override;

private:
	Animation mMoveAnimation;
	IntArea mStandSpriteArea;
	IntArea mJumpSpriteArea;
	IntArea mSlideSpriteArea;

	EntityStateMachine<Mario, Mario::States> mStates;
};
