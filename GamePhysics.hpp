#pragma once

#include "SFML/System/Time.hpp"

class GraphicsGameObject;

class GamePhysics final
{
public:
	void update(GraphicsGameObject& object, const sf::Time& frameTime) const;

	static float getFriction();

private:
	void updateMovement(GraphicsGameObject& object, const sf::Time& frameTime) const;

	void applyAcceleration(GraphicsGameObject& object, const sf::Time& frameTime) const;
	void updatePosition(GraphicsGameObject& object, const sf::Time& frameTime) const;

	void applyFriction(GraphicsGameObject& object, const sf::Time& frameTime) const;

	static constexpr const float mFriction = 0.918f;
};
