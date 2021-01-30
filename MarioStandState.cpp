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
    object.setTextureArea(object.getSpriteAtlas().getRegion("mario_stand").getSpriteAreas()[0][0]);
    object.setAcceleration({});
}

void MarioStandState::update(GameObject&, const sf::Time&)
{

}

void MarioStandState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent)
{
    if (isKey(keyEvent, sf::Keyboard::Q))
    {
        object.setDirection(GameObject::Directions::Left);
        object.setState(MarioMoveState::getInstance());
    }
    else if (isKey(keyEvent, sf::Keyboard::E))
    {
        object.setDirection(GameObject::Directions::Right);
        object.setState(MarioMoveState::getInstance());
    }
}
