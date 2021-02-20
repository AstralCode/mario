#pragma once

#include "GameObjectState.hpp"

class MarioMoveState final : public GameObjectState
{
public:
	MarioMoveState(const Spriteset& spriteset);

	void onSet(GraphicsGameObject& object) override;

	void onKeyPressed(GraphicsGameObject& object, const sf::Event::KeyEvent& keyEvent) override;
	void onKeyReleased(GraphicsGameObject& object, const sf::Event::KeyEvent& keyEvent) override;

private:
	void updateSelf(GraphicsGameObject& object, const sf::Time& frameTime) override;

	void moveLeft(GraphicsGameObject& object) const;
	void moveRight(GraphicsGameObject& object) const;
};
