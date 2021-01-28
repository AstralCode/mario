#pragma once

#include "GameObjectState.hpp"
#include "Animation.hpp"

class EnemyMoveState final : public GameObjectState
{
public:
	static EnemyMoveState* getInstance();

	void onSet(GameObject& object) override;
	void update(GameObject& object, const sf::Time& frameTime);

private:
	static EnemyMoveState mState;

	Animation mAnimation;
};