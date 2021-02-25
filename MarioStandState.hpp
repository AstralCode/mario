#pragma once

#include "GameObjectState.hpp"

class MarioStandState final : public GameObjectState
{
public:
	MarioStandState(const Spriteset& spriteset) noexcept;

	void onSet(GameObject& object) noexcept override;

	void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept override;

private:
	void updateSelf(GameObject& object, const sf::Time& frameTime) noexcept override;
};
