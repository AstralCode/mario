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
    mAnimation.setDuration(sf::seconds(0.25f));
    mAnimation.setFrameCount({3, 0});
    mAnimation.setFrameOffset({1, 0});
    mAnimation.setFrameSize({0, 0, 32, 32});

    mAnimation.stop();
    mAnimation.play();

    object.setAcceleration({250.0f, 0.0f});
    object.setMaxVelocity({200.0f, 0.0f});
    object.setVelocity({25.0f, 0.0f});
}

void MarioMoveState::update(GameObject& object, const sf::Time& frameTime)
{
    mAnimation.update(frameTime);

    object.setTextureArea(mAnimation.getCurrentFrame());
}

void MarioMoveState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent)
{
    if (isKeyPressed(keyEvent, sf::Keyboard::Q))
    {
        object.setDirection(GameObject::Directions::Left);
    }
    else if (isKeyPressed(keyEvent, sf::Keyboard::E))
    {
        object.setDirection(GameObject::Directions::Right);
    }
    else if (isKeyPressed(keyEvent, sf::Keyboard::W))
    {
        object.setState(MarioStandState::getInstance());
    }
}
