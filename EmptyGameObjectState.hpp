#pragma once

#include "GameObjectState.hpp"

class EmptyGameObjectState final : public GameObjectState
{
public:
	EmptyGameObjectState();

	static EmptyGameObjectState* getInstance();

	virtual void destroy() override;

	void update(GameObject& object, const sf::Time& frameTime) override;

	virtual bool isDestroyed() const override;

private:
	static EmptyGameObjectState mState;

	bool mIsDestroyed;
};
