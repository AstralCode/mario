#pragma once

#include "SFML/System/Time.hpp"

class GameObject;

class GamePhysics final
{
public:
	void update(GameObject& object, const sf::Time& frameTime) const;

	static float getFriction();

private:
	void updateMovement(GameObject& object, const sf::Time& frameTime) const;

	void applyAcceleration(GameObject& object, const sf::Time& frameTime) const;
	void updatePosition(GameObject& object, const sf::Time& frameTime) const;

	void applyFriction(GameObject& object, const sf::Time& frameTime) const;

	static constexpr const float mFriction = 0.918f;
};
