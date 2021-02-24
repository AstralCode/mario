#pragma once

#include "GameObjectState.hpp"

class MarioMoveState final : public GameObjectState
{
public:
	MarioMoveState(const Spriteset& spriteset);

	void onSet(GameObject& object) override;

	void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) override;
	void onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent) override;

private:
	void updateSelf(GameObject& object, const sf::Time& frameTime) override;
};
