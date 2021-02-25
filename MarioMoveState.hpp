#pragma once

#include "GameObjectState.hpp"

class MarioMoveState final : public GameObjectState
{
public:
	MarioMoveState(const Spriteset& spriteset) noexcept;

	void onSet(GameObject& object) noexcept override;

	void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept override;

private:
	void updateSelf(GameObject& object, const sf::Time& frameTime) noexcept override;
};
