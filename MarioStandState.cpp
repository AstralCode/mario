#include "MarioStandState.hpp"

#include "GameObject.hpp"
#include "MarioMoveState.hpp"
#include "MarioJumpState.hpp"

MarioStandState::MarioStandState(const Spriteset& spriteset) noexcept :
    GameObjectState{spriteset}
{

}

void MarioStandState::onSet(GameObject& object) noexcept
{
    object.setTextureArea(getSpriteArea(SpritesetRegionIdentifiers::Mario::Stand));
    object.setAcceleration({});
    object.setVelocity({});
}

void MarioStandState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == sf::Keyboard::Q)
    {
        object.moveLeft();
        object.setState(createState<MarioMoveState>());
    }
    else if (keyEvent.code == sf::Keyboard::E)
    {
        object.moveRight();
        object.setState(createState<MarioMoveState>());
    }
    else if (keyEvent.code == sf::Keyboard::W)
    {
        object.setState(createState<MarioJumpState>());
    }
}

void MarioStandState::updateSelf(GameObject&, const sf::Time&) noexcept
{

}
