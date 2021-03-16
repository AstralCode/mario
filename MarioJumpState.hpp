#pragma once

#include "GameObjectState.hpp"

class MarioJumpState final : public GameObjectState
{
public:
	MarioJumpState(const Spriteset& spriteset) noexcept;

	void onSet(GameObject& object) noexcept override;

	void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept override;

	bool isJumping() const noexcept override;

private:
	void updateSelf(GameObject& object, const sf::Time& fixedFrameTime) noexcept override;
};
