#include "EnemyMoveState.hpp"

#include "GameObject.hpp"

EnemyMoveState EnemyMoveState::mState;

EnemyMoveState* EnemyMoveState::getInstance()
{
    return &mState;
}

void EnemyMoveState::onSet(GameObject& object)
{
    mAnimation.setDuration(sf::seconds(0.25f));
    mAnimation.setFrameCount({2, 0});
    mAnimation.setFrameOffset({ 0, 0});
    mAnimation.setFrameSize({0, 0, 32, 32});

    mAnimation.stop();
    mAnimation.play();

    object.setVelocity({32.0f, 0.0f});
    object.setMaxVelocity({32.0f, 0.0f});
    object.setAcceleration({64.0f, 0.0f});
}

void EnemyMoveState::update(GameObject& object, const sf::Time& frameTime)
{
    mAnimation.update(frameTime);
    object.setTextureArea(mAnimation.getCurrentFrame());

    const auto accelerationX = object.getAcceleration().x * frameTime.asSeconds() * object.getDirectionFactor().x;
    object.accelerateVelocity({accelerationX, 0.0f});

    const auto moveX = object.getVelocity().x * frameTime.asSeconds();
    object.move({moveX, 0.0f});
}
