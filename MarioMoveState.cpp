#include "MarioMoveState.hpp"

#include "GraphicsGameObject.hpp"
#include "MarioStandState.hpp"

MarioMoveState::MarioMoveState(const Spriteset& spriteset) :
    GameObjectState{spriteset}
{

}

void MarioMoveState::onSet(GraphicsGameObject& object)
{
    auto animation = createAnimation(SpritesetRegionIdentifiers::Mario::Move);
    animation->setDuration(sf::seconds(0.25f));
    animation->setRepeating(true);

    setAnimation(std::move(animation));

    object.setAcceleration(object.getMaxAcceleration());
}

void MarioMoveState::onKeyPressed(GraphicsGameObject& object, const sf::Event::KeyEvent& keyEvent)
{
    if (keyEvent.code == sf::Keyboard::Q)
    {
        moveLeft(object);
    }
    else if (keyEvent.code == sf::Keyboard::E)
    {
        moveRight(object);
    }
}

void MarioMoveState::onKeyReleased(GraphicsGameObject& object, const sf::Event::KeyEvent& keyEvent)
{
    if (keyEvent.code == sf::Keyboard::Q || keyEvent.code == sf::Keyboard::E)
    {
        object.setAcceleration({});
    }

    if (keyEvent.code == sf::Keyboard::Q)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            moveRight(object);
        }
    }
    else if (keyEvent.code == sf::Keyboard::E)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            moveLeft(object);
        }
    }
}

void MarioMoveState::updateSelf(GraphicsGameObject& object, const sf::Time&)
{
    const auto minVelocity = 4.0f;

    if (std::abs(object.getVelocity().x) > minVelocity)
    {
        const bool sliding =
            (object.getDirection() == GraphicsGameObject::Directions::Left && object.getVelocity().x > 0.0f) ||
            (object.getDirection() == GraphicsGameObject::Directions::Right && object.getVelocity().x < 0.0f);

        if (sliding)
        {
            object.setTextureArea(getSpriteArea(SpritesetRegionIdentifiers::Mario::Slide));
        }

    }
    else if (object.getAcceleration().x == 0.0f)
    {
        object.setState(createState<MarioStandState>());
    }
}

void MarioMoveState::moveLeft(GraphicsGameObject& object) const
{
    object.setDirection(GraphicsGameObject::Directions::Left);
    object.setAcceleration(object.getMaxAcceleration());
}

void MarioMoveState::moveRight(GraphicsGameObject& object) const
{
    object.setDirection(GraphicsGameObject::Directions::Right);
    object.setAcceleration(object.getMaxAcceleration());
}
