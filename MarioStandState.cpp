#include "MarioStandState.hpp"

#include "GameObject.hpp"
#include "MarioMoveState.hpp"

MarioStandState::MarioStandState(const Spriteset& spriteset) :
    GameObjectState{spriteset}
{

}

void MarioStandState::onSet(GameObject& object)
{
    object.setTextureArea(getSpriteArea(SpritesetRegionIdentifiers::Mario::Stand));
    object.setAcceleration({});
    object.setVelocity({});
}

void MarioStandState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent)
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
}

void MarioStandState::updateSelf(GameObject&, const sf::Time&)
{

}
