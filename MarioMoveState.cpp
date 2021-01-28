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

    object.setAcceleration({128.0f, 128.0f});
    object.setMaxVelocity({168.0f, 168.0f});
    object.setVelocity({74.0f, 74.0f});
}

void MarioMoveState::update(GameObject& object, const sf::Time& frameTime)
{
    mAnimation.update(frameTime);
    object.setTextureArea(mAnimation.getCurrentFrame());

    const auto acceleration = object.getAcceleration().x * frameTime.asSeconds();
    object.accelerateVelocity({acceleration, 0.0f});

    const auto move = object.getVelocity().x * frameTime.asSeconds();
    object.move({move, 0.0f});
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
