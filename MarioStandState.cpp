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
    object.setTextureArea({0, 0, 32, 32});
}

void MarioStandState::update(GameObject& object, const sf::Time& frameTime)
{

}

void MarioStandState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent)
{
    if (isKeyPressed(keyEvent, sf::Keyboard::Q))
    {
        object.destroy();
    }
    else if (isKeyPressed(keyEvent, sf::Keyboard::E))
    {
        object.setState(MarioMoveState::getInstance());
    }
}
