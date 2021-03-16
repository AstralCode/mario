#include "MarioJumpState.hpp"

#include "GameObject.hpp"
#include "MarioStandState.hpp"
#include "MarioMoveState.hpp"

MarioJumpState::MarioJumpState(const Spriteset& spriteset) noexcept :
    GameObjectState{spriteset}
{

}

void MarioJumpState::onSet(GameObject& object) noexcept
{
    object.setTextureArea(getSpriteArea(SpritesetRegionIdentifiers::Mario::Jump));
    object.setAccelerationY(object.getMaxAcceleration().getY());
}

void MarioJumpState::onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == sf::Keyboard::W)
    {
        object.setAccelerationY(0.0f);
    }
}

void MarioJumpState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == sf::Keyboard::Q)
    {
        object.moveLeft();
    }
    else if (keyEvent.code == sf::Keyboard::E)
    {
        object.moveRight();
    }
}

bool MarioJumpState::isJumping() const noexcept
{
    return true;
}

void MarioJumpState::updateSelf(GameObject& object, const sf::Time&) noexcept
{
    if (std::abs(object.getVelocity().getY()) < 1.0f)
    {
        object.setState(createState<MarioStandState>());
    }
}
