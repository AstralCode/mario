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
    mAnimation.setSpriteAtlasRegion(&object.getSpriteAtlas().getRegion("mario_move"));
    mAnimation.setDuration(sf::seconds(0.25f));
    mAnimation.stop();
    mAnimation.play();

    object.setAcceleration(object.getMaxAcceleration());
}

void MarioMoveState::update(GameObject& object, const sf::Time& frameTime)
{
    mAnimation.update(frameTime);

    object.setTextureArea(mAnimation.getCurrentSprite());

    if (object.getAcceleration().x == 0.0f && std::abs(object.getVelocity().x) <= 32.0f)
    {
        object.setState(MarioStandState::getInstance());
    }
}

void MarioMoveState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent)
{
    if (isKey(keyEvent, sf::Keyboard::Q))
    {
        object.setDirection(GameObject::Directions::Left);
        object.setAcceleration(object.getMaxAcceleration());
    }
    else if (isKey(keyEvent, sf::Keyboard::E))
    {
        object.setDirection(GameObject::Directions::Right);
        object.setAcceleration(object.getMaxAcceleration());
    }
}

void MarioMoveState::onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent)
{
    if (isKey(keyEvent, sf::Keyboard::Q) || isKey(keyEvent, sf::Keyboard::E))
    {
        object.setAcceleration({});
    }
}
