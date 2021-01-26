#include "MarioWalkStand.hpp"

#include "GameObject.hpp"
#include "MarioStandState.hpp"

MarioWalkState MarioWalkState::mState;

MarioWalkState* MarioWalkState::getInstance()
{
    return &mState;
}

MarioWalkState::MarioWalkState() :
    mIsDestroyed{false}
{

}

void MarioWalkState::onSet(GameObject& object)
{
    object.setTextureArea({32, 0, 32, 32});
}

void MarioWalkState::onUnset(GameObject&)
{

}

void MarioWalkState::destroy()
{
    mIsDestroyed = true;
}

void MarioWalkState::update(GameObject& object, const sf::Time& frameTime)
{

}

void MarioWalkState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent)
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

bool MarioWalkState::isDestroyed() const
{
    return mIsDestroyed;
}
