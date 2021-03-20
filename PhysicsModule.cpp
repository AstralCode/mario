#include "PhysicsModule.hpp"

#include "Entity.hpp"

void PhysicsModule::update(Entity& entity, const sf::Time& dt) const noexcept
{
	auto accelerateX = calculateAccelerate(entity.getAcceleration().getX(), dt);
	accelerateX *= entity.hasDirection(Entity::Direction::Left) ? -1.0f : +1.0f;
	auto accelerateY = calculateAccelerate(entity.getAcceleration().getY(), dt);

	auto velocityX = calculateVelocity(entity.getVelocity().getX(), accelerateX);
	velocityX *= getFriction();
	auto velocityY = calculateVelocity(entity.getVelocity().getY(), accelerateY);
	velocityY *= getFriction();

	velocityY += calculateGravity(dt);

	const auto positionX = calculatePosition(velocityX, dt);
	entity.setVelocityX(velocityX);
	entity.move(positionX, 0.0f);

	const auto positionY = calculatePosition(velocityY, dt);
	entity.setVelocityY(velocityY);
	entity.move(0.0f, positionY);
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
