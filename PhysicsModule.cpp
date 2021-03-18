#include "PhysicsModule.hpp"

#include "GameObject.hpp"

void PhysicsModule::update(GameObject& object, const sf::Time& fixedFrameTime) const noexcept
{
	auto accelerateX = calculateAccelerate(object.getAcceleration().getX(), fixedFrameTime);
	accelerateX *= object.hasDirection(GameObjectDirections::Left) ? -1.0f : +1.0f;
	auto accelerateY = calculateAccelerate(object.getAcceleration().getY(), fixedFrameTime);

	auto velocityX = calculateVelocity(object.getVelocity().getX(), accelerateX);
	velocityX *= getFriction();
	auto velocityY = calculateVelocity(object.getVelocity().getY(), accelerateY);
	velocityY *= getFriction();

	velocityY += calculateGravity(fixedFrameTime);

	const auto positionX = calculatePosition(velocityX, fixedFrameTime);
	object.setVelocityX(velocityX);
	object.move(positionX, 0.0f);

	const auto positionY = calculatePosition(velocityY, fixedFrameTime);
	object.setVelocityY(velocityY);
	object.move(0.0f, positionY);
}

constexpr float PhysicsModule::getFriction() noexcept
{
	return mFriction;
}

constexpr float PhysicsModule::getGravity() noexcept
{
    return mGravity;
}

inline float PhysicsModule::calculateAccelerate(const float accelerate, const sf::Time& fixedFrameTime) const noexcept
{
	return accelerate * fixedFrameTime.asSeconds();
}

inline float PhysicsModule::calculateVelocity(const float velocity, const float accelerate) const noexcept
{
	return velocity + accelerate;
}

inline float PhysicsModule::calculatePosition(const float velocity, const sf::Time& fixedFrameTime) const noexcept
{
	return velocity * fixedFrameTime.asSeconds();
}

inline float PhysicsModule::calculateGravity(const sf::Time& fixedFrameTime) const noexcept
{
	return mGravity * fixedFrameTime.asSeconds();
}
