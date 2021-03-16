#include "PhysicsModule.hpp"

#include "SFML/System/Time.hpp"

#include "GameObject.hpp"

void PhysicsModule::update(GameObject& object, const sf::Time& fixedFrameTime) const noexcept
{
    updateMovement(object, fixedFrameTime);
    updatePosition(object, fixedFrameTime);
}

constexpr float PhysicsModule::getFriction() noexcept
{
	return mFriction;
}

constexpr float PhysicsModule::getGravity() noexcept
{
    return mGravity;
}

void PhysicsModule::updateMovement(GameObject& object, const sf::Time& fixedFrameTime) const noexcept
{
    applyAcceleration(object, fixedFrameTime);
    applyFriction(object, fixedFrameTime);
}

void PhysicsModule::updatePosition(GameObject& object, const sf::Time& fixedFrameTime) const noexcept
{
    FloatPoint offset{};
    offset.setX(object.getVelocity().getX() * fixedFrameTime.asSeconds());
    offset.setY(object.getVelocity().getY() * fixedFrameTime.asSeconds());

    object.move(offset);
}

void PhysicsModule::applyAcceleration(GameObject& object, const sf::Time& fixedFrameTime) const noexcept
{
    FloatPoint acceleration{};
    acceleration.setX(object.getAcceleration().getX() * fixedFrameTime.asSeconds());
    acceleration.setY(object.getAcceleration().getY() * fixedFrameTime.asSeconds());

    object.accelerateVelocity(acceleration);
}

void PhysicsModule::applyFriction(GameObject& object, const sf::Time& fixedFrameTime) const noexcept
{
    const auto firiction = std::pow(getFriction(), fixedFrameTime.asSeconds());

    FloatPoint velocity{};
    velocity.setX(object.getVelocity().getX() * firiction);
    velocity.setY(object.getVelocity().getY() * firiction);

    object.setVelocity(velocity);
}
