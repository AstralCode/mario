#pragma once

#include "GameObjectState.hpp"

class MarioStandState final : public GameObjectState
{
public:
	static MarioStandState* getInstance();

	MarioStandState();

	void onSet(GameObject& object) override;
	void onUnset(GameObject& object) override;

	void destroy() override;

	void update(GameObject& object, const sf::Time& frameTime);

	void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) override;

	bool isDestroyed() const override;

private:
	static MarioStandState mState;

	bool mIsDestroyed;
};
