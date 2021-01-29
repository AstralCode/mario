#include "GamePhysics.hpp"

#include "GameObject.hpp"

void GamePhysics::update(GameObject& object, const sf::Time& frameTime) const
{
    updateMovement(object, frameTime);
    applyFriction(object, frameTime);
}

float GamePhysics::getFriction()
{
	return mFriction;
}

void GamePhysics::updateMovement(GameObject& object, const sf::Time& frameTime) const
{
    applyAcceleration(object, frameTime);
    updatePosition(object, frameTime);
}

void GamePhysics::applyAcceleration(GameObject& object, const sf::Time& frameTime) const
{
    sf::Vector2f acceleration{};
    acceleration.x = object.getAcceleration().x * frameTime.asSeconds() * object.getDirectionFactor().x;
    acceleration.y = object.getAcceleration().y * frameTime.asSeconds() * object.getDirectionFactor().y;

    object.accelerateVelocity(acceleration);
}

void GamePhysics::updatePosition(GameObject& object, const sf::Time& frameTime) const
{
    sf::Vector2f move{};
    move.x = object.getVelocity().x * frameTime.asSeconds();
    move.y = object.getVelocity().y * frameTime.asSeconds();

    object.move(move);
}

void GamePhysics::applyFriction(GameObject& object, const sf::Time& frameTime) const
{
    const auto friction = getFriction();

    sf::Vector2f velocity{};
    velocity.x = object.getVelocity().x * friction;
    velocity.y = object.getVelocity().y * friction;

    object.setVelocity(velocity);
}
