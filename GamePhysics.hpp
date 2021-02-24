#pragma once

namespace sf
{
class Time;
}

class GameObject;

class GamePhysics final
{
public:
	void update(GameObject& object, const sf::Time& frameTime) const noexcept;

	static float getFriction();

private:
	void updateMovement(GameObject& object, const sf::Time& frameTime) const noexcept;

	void applyAcceleration(GameObject& object, const sf::Time& frameTime) const noexcept;
	void updatePosition(GameObject& object, const sf::Time& frameTime) const noexcept;

	void applyFriction(GameObject& object, const sf::Time& frameTime) const noexcept;

	static constexpr const float mFriction = 0.918f;
};
