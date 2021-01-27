#include "MarioMoveState.hpp"

#include "GameObject.hpp"
#include "MarioStandState.hpp"

MarioMoveState MarioMoveState::mState;

MarioMoveState* MarioMoveState::getInstance()
{
    return &mState;
}

void MarioMoveState::onSet(GameObject& object)
{
    object.setVelocity({0.0f, 0.0f});
    object.setTextureArea({32, 0, 32, 32});
}

void MarioMoveState::update(GameObject& object, const sf::Time& frameTime)
{
    const auto movement = mSpeed * frameTime.asSeconds();
    object.move({movement, 0.0f});
}

void MarioMoveState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent)
{
    if (keyEvent.code == sf::Keyboard::Q)
    {
        object.destroy();
    }
    else if (isKeyPressed(keyEvent, sf::Keyboard::E))
    {
        object.setState(MarioStandState::getInstance());
    }
}
