#pragma once

#include "GameObjectState.hpp"

class MarioStandState final : public GameObjectState
{
public:
	MarioStandState(const Spriteset& spriteset);

	void onSet(GameObject& object) override;

	void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) override;

private:
	void updateSelf(GameObject& object, const sf::Time& frameTime) override;
};
