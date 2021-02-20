#include "MarioStandState.hpp"

#include "GraphicsGameObject.hpp"
#include "MarioMoveState.hpp"

MarioStandState::MarioStandState(const Spriteset& spriteset) :
    GameObjectState{spriteset}
{

}

void MarioStandState::onSet(GraphicsGameObject& object)
{
    object.setTextureArea(getSpriteArea(SpritesetRegionIdentifiers::Mario::Stand));
    object.setAcceleration({});
}

void MarioStandState::onKeyPressed(GraphicsGameObject& object, const sf::Event::KeyEvent& keyEvent)
{
    if (keyEvent.code == sf::Keyboard::Q)
    {
        object.setDirection(GraphicsGameObject::Directions::Left);
        object.setState(createState<MarioMoveState>());
    }
    else if (keyEvent.code == sf::Keyboard::E)
    {
        object.setDirection(GraphicsGameObject::Directions::Right);
        object.setState(createState<MarioMoveState>());
    }
}

void MarioStandState::updateSelf(GraphicsGameObject&, const sf::Time&)
{

}
