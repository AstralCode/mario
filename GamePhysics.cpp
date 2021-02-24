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
    acceleration.x = object.getAcceleration().x * frameTime.asSeconds();
    acceleration.y = object.getAcceleration().y * frameTime.asSeconds();

    object.accelerateVelocity(acceleration);
}

void GamePhysics::updatePosition(GameObject& object, const sf::Time& frameTime) const noexcept
{
    sf::Vector2f offset{};
    offset.x = object.getVelocity().x * frameTime.asSeconds();
    offset.y = object.getVelocity().y * frameTime.asSeconds();

    object.move(offset);
}

void GamePhysics::applyFriction(GameObject& object, const sf::Time& frameTime) const noexcept
{
    constexpr const auto friction = getFriction();

    sf::Vector2f velocity{};
    velocity.x = object.getVelocity().x * std::pow(friction, frameTime.asSeconds());
    velocity.y = object.getVelocity().y * std::pow(friction, frameTime.asSeconds());

    object.setVelocity(velocity);
}
