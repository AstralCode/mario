#pragma once

#include "SFML/System/Time.hpp"

class GameObject;

class PhysicsModule final
{
public:
	void update(GameObject& object, const sf::Time& fixedFrameTime) const noexcept;

	static constexpr float getFriction() noexcept;
	static constexpr float getGravity() noexcept;

private:
	inline float calculateAccelerate(const float accelerate, const sf::Time& fixedFrameTime) const noexcept;
	inline float calculateVelocity(const float velocity, const float accelerate) const noexcept;
	inline float calculatePosition(const float velocity, const sf::Time& fixedFrameTime) const noexcept;
	inline float calculateGravity(const sf::Time& fixedFrameTime) const noexcept;

	static constexpr const auto mFriction = 0.95f;
	static constexpr const auto mGravity = 32.0f * 5.0f;
};
