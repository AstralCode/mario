#pragma once

#include "GameObjectState.hpp"
#include "Animation.hpp"

class MarioMoveState final : public GameObjectState
{
public:
	static MarioMoveState* getInstance();

	void onSet(GameObject& object) override;
	void update(GameObject& object, const sf::Time& frameTime);

	void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) override;
	void onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent) override;

private:
	static MarioMoveState mState;

	Animation mAnimation;

	bool mMoving;
};
