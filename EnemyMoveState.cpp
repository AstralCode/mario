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

    object.setVelocity({32.0f, 32.0f});
    object.setMaxVelocity({84.0f, 84.0f});
    object.setAcceleration({64.0f, 64.0f});
}

void EnemyMoveState::update(GameObject& object, const sf::Time& frameTime)
{
    mAnimation.update(frameTime);
    object.setTextureArea(mAnimation.getCurrentFrame());

    const auto accelerationX = object.getAcceleration().x * frameTime.asSeconds();
    object.accelerateVelocity({accelerationX, 0.0f});

    const auto move = object.getVelocity().x * frameTime.asSeconds();
    object.move({move, 0.0f});
}
