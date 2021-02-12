#pragma once

#include "GameObjectState.hpp"
#include "Animation.hpp"

class MarioMoveState final : public GameObjectState
{
public:
	void onSet(GameObject& object) override;
	void update(GameObject& object, const sf::Time& frameTime);

	void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) override;
	void onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent) override;

private:
	void moveLeft(GameObject& object) const;
	void moveRight(GameObject& object) const;

	Animation mAnimation;
};
