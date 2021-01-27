#include "EnemyMoveState.hpp"

#include "GameObject.hpp"

EnemyMoveState EnemyMoveState::mState;

EnemyMoveState* EnemyMoveState::getInstance()
{
    return &mState;
}

void EnemyMoveState::onSet(GameObject& object)
{
    object.setVelocity({0.0f, 0.0f});
    object.setTextureArea({32, 0, 32, 32});
}

void EnemyMoveState::update(GameObject& object, const sf::Time& frameTime)
{
    const auto movement = mSpeed * frameTime.asSeconds();
    object.move({movement, 0.0f});
}
