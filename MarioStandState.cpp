#include "MarioStandState.hpp"

#include "GameObject.hpp"
#include "MarioMoveState.hpp"

MarioStandState MarioStandState::mState;

MarioStandState* MarioStandState::getInstance()
{
    return &mState;
}

void MarioStandState::onSet(GameObject& object)
{
    object.setTextureArea({0, 0, 24, 32});

    object.setAcceleration({});
    object.setMaxVelocity({});
    object.setVelocity({});
}

void MarioStandState::update(GameObject&, const sf::Time&)
{

}

void MarioStandState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent)
{
    if (isKeyPressed(keyEvent, sf::Keyboard::Q))
    {
        object.setDirection(GameObject::Directions::Left);
        object.setState(MarioMoveState::getInstance());
    }
    else if (isKeyPressed(keyEvent, sf::Keyboard::E))
    {
        object.setDirection(GameObject::Directions::Right);
        object.setState(MarioMoveState::getInstance());
    }
}
