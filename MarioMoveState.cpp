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
    mMoving = true;

    mAnimation.setDuration(sf::seconds(0.25f));
    mAnimation.setFrameCount({3, 0});
    mAnimation.setFrameOffset({1, 0});
    mAnimation.setFrameSize({0, 0, 32, 32});

    mAnimation.stop();
    mAnimation.play();

    object.setAcceleration({128.0f, 0.0f});
    object.setMaxVelocity({32.0f, 0.0f});
    object.setVelocity({32.0f * object.getDirectionFactor().x, 0.0f});
}

void MarioMoveState::update(GameObject& object, const sf::Time& frameTime)
{
    mAnimation.update(frameTime);
    object.setTextureArea(mAnimation.getCurrentFrame());

    const auto accelerationX = object.getAcceleration().x * frameTime.asSeconds() * object.getDirectionFactor().x;
    object.accelerateVelocity({accelerationX, 0.0f});

    const auto moveX = object.getVelocity().x * frameTime.asSeconds();
    object.move({moveX, 0.0f});

    if (!mMoving)
    {
        if (std::abs(object.getVelocity().x) < 32.0f)
        {
            object.setState(MarioStandState::getInstance());
        }
    }
}

void MarioMoveState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent)
{
    if (isKey(keyEvent, sf::Keyboard::Q))
    {
        object.setDirection(GameObject::Directions::Left);
        object.setAcceleration({128.0f, 0.0f});
        object.setVelocity({-32.0f, 0.0f});
        mMoving = true;
    }
    else if (isKey(keyEvent, sf::Keyboard::E))
    {
        object.setDirection(GameObject::Directions::Right);
        object.setAcceleration({128.0f, 0.0f});
        object.setVelocity({+32.0f, 0.0f});
        mMoving = true;
    }
}

void MarioMoveState::onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent)
{
    if (isKey(keyEvent, sf::Keyboard::Q) || isKey(keyEvent, sf::Keyboard::E))
    {
        object.setAcceleration({0.0f, 0.0f});
        mMoving = false;
    }
}
