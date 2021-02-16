#include "MarioStandState.hpp"

#include "GameObject.hpp"
#include "MarioMoveState.hpp"

MarioStandState::MarioStandState(const Spriteset& spriteset) :
    GameObjectState{spriteset}
{

}

void MarioStandState::onSet(GameObject& object)
{
    object.setTextureArea(getSprite(SpritesetRegionIdentifiers::Mario::Stand));
    object.setAcceleration({});
}

void MarioStandState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent)
{
    if (keyEvent.code == sf::Keyboard::Q)
    {
        object.setDirection(GameObject::Directions::Left);
        object.setState(createState<MarioMoveState>());
    }
    else if (keyEvent.code == sf::Keyboard::E)
    {
        object.setDirection(GameObject::Directions::Right);
        object.setState(createState<MarioMoveState>());
    }
}

void MarioStandState::updateSelf(GameObject&, const sf::Time&)
{

}
