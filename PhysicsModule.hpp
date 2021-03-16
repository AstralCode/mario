#pragma once

namespace sf
{
class Time;
}

class GameObject;

class PhysicsModule final
{
public:
	void update(GameObject& object, const sf::Time& fixedFrameTime) const noexcept;

	static constexpr float getFriction() noexcept;
	static constexpr float getGravity() noexcept;

private:
	void updateMovement(GameObject& object, const sf::Time& fixedFrameTime) const noexcept;
	void updatePosition(GameObject& object, const sf::Time& fixedFrameTime) const noexcept;

	void applyAcceleration(GameObject& object, const sf::Time& fixedFrameTime) const noexcept;
	void applyFriction(GameObject& object, const sf::Time& fixedFrameTime) const noexcept;

	static constexpr const auto mFriction = 0.005f;
	static constexpr const auto mGravity = 32.0f * 5.0f;
};
