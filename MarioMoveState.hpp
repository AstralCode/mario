#pragma once

#include "GameObjectState.hpp"
#include "Spriteset.hpp"
#include "SpritesetRegions.hpp"
#include "Animation.hpp"

class MarioMoveState final : public GameObjectState
{
public:
	MarioMoveState(const Spriteset<MarioSpritesetRegions>& spriteset) noexcept;

	void onSet(GameObject& object) noexcept override;
	void update(GameObject& object, const sf::Time& dt) noexcept override;

	void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept override;

	void onFalling(GameObject& object) noexcept override;

	bool isJumping() const noexcept override;
	bool isFalling() const noexcept override;

private:
	const Spriteset<MarioSpritesetRegions>& mSpriteset;

	Animation mMoveAnimation;
};
