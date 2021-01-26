#pragma once

#include "GameObjectState.hpp"

class EmptyGameObjectState final : public GameObjectState
{
public:
	static EmptyGameObjectState* getInstance();

	EmptyGameObjectState();

	void onSet(GameObject& object) override;
	void onUnset(GameObject& object) override;

	virtual void destroy() override;

	void update(GameObject& object, const sf::Time& frameTime) override;

	virtual bool isDestroyed() const override;

private:
	static EmptyGameObjectState mState;

	bool mIsDestroyed;
};
