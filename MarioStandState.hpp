#pragma once

#include "GameObjectState.hpp"

class MarioStandState final : public GameObjectState
{
public:
	MarioStandState(const Spriteset& spriteset);

	void onSet(GraphicsGameObject& object) override;

	void onKeyPressed(GraphicsGameObject& object, const sf::Event::KeyEvent& keyEvent) override;

private:
	void updateSelf(GraphicsGameObject& object, const sf::Time& frameTime) override;
};
