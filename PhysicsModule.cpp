#include "PhysicsModule.hpp"

#include "GameObject.hpp"

void PhysicsModule::update(GameObject& object, const sf::Time& dt) const noexcept
{
	auto accelerateX = calculateAccelerate(object.getAcceleration().getX(), dt);
	accelerateX *= object.hasDirection(GameObjectDirections::Left) ? -1.0f : +1.0f;
	auto accelerateY = calculateAccelerate(object.getAcceleration().getY(), dt);

	auto velocityX = calculateVelocity(object.getVelocity().getX(), accelerateX);
	velocityX *= getFriction();
	auto velocityY = calculateVelocity(object.getVelocity().getY(), accelerateY);
	velocityY *= getFriction();

	velocityY += calculateGravity(dt);

	const auto positionX = calculatePosition(velocityX, dt);
	object.setVelocityX(velocityX);
	object.move(positionX, 0.0f);

	const auto positionY = calculatePosition(velocityY, dt);
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

inline float PhysicsModule::calculateAccelerate(const float accelerate, const sf::Time& dt) const noexcept
{
	return accelerate * dt.asSeconds();
}

inline float PhysicsModule::calculateVelocity(const float velocity, const float accelerate) const noexcept
{
	return velocity + accelerate;
}

inline float PhysicsModule::calculatePosition(const float velocity, const sf::Time& dt) const noexcept
{
	return velocity * dt.asSeconds();
}

inline float PhysicsModule::calculateGravity(const sf::Time& dt) const noexcept
{
	return mGravity * dt.asSeconds();
}
