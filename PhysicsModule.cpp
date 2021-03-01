#include "PhysicsModule.hpp"

#include "SFML/System/Time.hpp"

#include "GameObject.hpp"

void PhysicsModule::update(GameObject& object, const sf::Time& frameTime) const noexcept
{
    updateMovement(object, frameTime);
    applyFriction(object, frameTime);
}

constexpr float PhysicsModule::getFriction() noexcept
{
	return mFriction;
}

void PhysicsModule::updateMovement(GameObject& object, const sf::Time& frameTime) const noexcept
{
    applyAcceleration(object, frameTime);
    updatePosition(object, frameTime);
}

void PhysicsModule::applyAcceleration(GameObject& object, const sf::Time& frameTime) const noexcept
{
    sf::Vector2f acceleration{};
    acceleration.x = object.getAcceleration().getX() * frameTime.asSeconds();
    acceleration.y = object.getAcceleration().getY() * frameTime.asSeconds();

    object.accelerateVelocity(acceleration);
}

void PhysicsModule::updatePosition(GameObject& object, const sf::Time& frameTime) const noexcept
{
    sf::Vector2f offset{};
    offset.x = object.getVelocity().getX() * frameTime.asSeconds();
    offset.y = object.getVelocity().getY() * frameTime.asSeconds();

    object.move(offset);
}

void PhysicsModule::applyFriction(GameObject& object, const sf::Time& frameTime) const noexcept
{
    constexpr const auto friction = getFriction();

    sf::Vector2f velocity{};
    velocity.x = object.getVelocity().getX() * std::pow(friction, frameTime.asSeconds());
    velocity.y = object.getVelocity().getY() * std::pow(friction, frameTime.asSeconds());

    object.setVelocity(velocity);
}
