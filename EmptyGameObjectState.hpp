#pragma once

#include "GameObjectState.hpp"

class EmptyGameObjectState final : public GameObjectState
{
public:
	static EmptyGameObjectState* getInstance();

	void onSet(GameObject& object) override;
	void update(GameObject& object, const sf::Time& frameTime) override;

private:
	static EmptyGameObjectState mState;
};
