#pragma once

#include "SFML/System/Time.hpp"

#include "Constants.hpp"

class Entity;

class PhysicsModule final
{
public:
	void update(Entity& entity, const sf::Time& dt) const noexcept;

	static constexpr float getFriction() noexcept;
	static constexpr float getGravity() noexcept;

private:
	inline float calculateAccelerate(const float accelerate, const sf::Time& dt) const noexcept;
	inline float calculateVelocity(const float velocity, const float accelerate) const noexcept;
	inline float calculatePosition(const float velocity, const sf::Time& dt) const noexcept;
	inline float calculateGravity(const sf::Time& dt) const noexcept;

	static constexpr const auto mFriction = Constants::World::Physics::Friction;
	static constexpr const auto mGravity = Constants::World::Physics::Gravity;
};
