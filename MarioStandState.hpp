#pragma once

#include "GameObjectState.hpp"

class MarioStandState final : public GameObjectState
{
public:
	static MarioStandState* getInstance();

	void onSet(GameObject& object) override;
	void update(GameObject& object, const sf::Time& frameTime);

	void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) override;

private:
	static MarioStandState mState;
};
