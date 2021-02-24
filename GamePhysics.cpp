#include "GamePhysics.hpp"

#include "SFML/System/Time.hpp"

#include "GameObject.hpp"

void GamePhysics::update(GameObject& object, const sf::Time& frameTime) const noexcept
{
    updateMovement(object, frameTime);
    applyFriction(object, frameTime);
}

constexpr float GamePhysics::getFriction() noexcept
{
	return mFriction;
}

void GamePhysics::updateMovement(GameObject& object, const sf::Time& frameTime) const noexcept
{
    applyAcceleration(object, frameTime);
    updatePosition(object, frameTime);
}

void GamePhysics::applyAcceleration(GameObject& object, const sf::Time& frameTime) const noexcept
{
    sf::Vector2f acceleration{};
    acceleration.x = object.getAcceleration().x * frameTime.asSeconds() * object.getDirectionFactor().x;
    acceleration.y = object.getAcceleration().y * frameTime.asSeconds() * object.getDirectionFactor().y;

    object.accelerateVelocity(acceleration);
}

void GamePhysics::updatePosition(GameObject& object, const sf::Time& frameTime) const noexcept
{
    sf::Vector2f offset{};
    offset.x = object.getVelocity().x * frameTime.asSeconds();
    offset.y = object.getVelocity().y * frameTime.asSeconds();

    object.move(offset);
}

void GamePhysics::applyFriction(GameObject& object, const sf::Time&) const noexcept
{
    constexpr const auto friction = getFriction();

    sf::Vector2f velocity{};
    velocity.x = object.getVelocity().x * friction;
    velocity.y = object.getVelocity().y * friction;

    object.setVelocity(velocity);
}
