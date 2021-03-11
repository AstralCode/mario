#include "PhysicsModule.hpp"

#include "SFML/System/Time.hpp"

#include "GameObject.hpp"

void PhysicsModule::update(GameObject& object, const sf::Time& fixedFrameTime) const noexcept
{
    updateMovement(object, fixedFrameTime);
    applyFriction(object, fixedFrameTime);
}

constexpr float PhysicsModule::getFriction() noexcept
{
	return mFriction;
}

void PhysicsModule::updateMovement(GameObject& object, const sf::Time& fixedFrameTime) const noexcept
{
    applyAcceleration(object, fixedFrameTime);
    updatePosition(object, fixedFrameTime);
}

void PhysicsModule::applyAcceleration(GameObject& object, const sf::Time& fixedFrameTime) const noexcept
{
    sf::Vector2f acceleration{};
    acceleration.x = object.getAcceleration().getX() * fixedFrameTime.asSeconds();
    acceleration.y = object.getAcceleration().getY() * fixedFrameTime.asSeconds();

    object.accelerateVelocity(acceleration);
}

void PhysicsModule::updatePosition(GameObject& object, const sf::Time& fixedFrameTime) const noexcept
{
    sf::Vector2f offset{};
    offset.x = object.getVelocity().getX() * fixedFrameTime.asSeconds();
    offset.y = object.getVelocity().getY() * fixedFrameTime.asSeconds();

    object.move(offset);
}

void PhysicsModule::applyFriction(GameObject& object, const sf::Time& fixedFrameTime) const noexcept
{
    constexpr const auto friction = getFriction();

    sf::Vector2f velocity{};
    velocity.x = object.getVelocity().getX() * std::pow(friction, fixedFrameTime.asSeconds());
    velocity.y = object.getVelocity().getY() * std::pow(friction, fixedFrameTime.asSeconds());

    object.setVelocity(velocity);
}
