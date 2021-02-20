#include "GamePhysics.hpp"

#include "GraphicsGameObject.hpp"

void GamePhysics::update(GraphicsGameObject& object, const sf::Time& frameTime) const
{
    updateMovement(object, frameTime);
    applyFriction(object, frameTime);
}

float GamePhysics::getFriction()
{
	return mFriction;
}

void GamePhysics::updateMovement(GraphicsGameObject& object, const sf::Time& frameTime) const
{
    applyAcceleration(object, frameTime);
    updatePosition(object, frameTime);
}

void GamePhysics::applyAcceleration(GraphicsGameObject& object, const sf::Time& frameTime) const
{
    sf::Vector2f acceleration{};
    acceleration.x = object.getAcceleration().x * frameTime.asSeconds() * object.getDirectionFactor().x;
    acceleration.y = object.getAcceleration().y * frameTime.asSeconds() * object.getDirectionFactor().y;

    object.accelerateVelocity(acceleration);
}

void GamePhysics::updatePosition(GraphicsGameObject& object, const sf::Time& frameTime) const
{
    sf::Vector2f move{};
    move.x = object.getVelocity().x * frameTime.asSeconds();
    move.y = object.getVelocity().y * frameTime.asSeconds();

    object.move(move);
}

void GamePhysics::applyFriction(GraphicsGameObject& object, const sf::Time&) const
{
    const auto friction = getFriction();

    sf::Vector2f velocity{};
    velocity.x = object.getVelocity().x * friction;
    velocity.y = object.getVelocity().y * friction;

    object.setVelocity(velocity);
}
