#include "MarioMoveState.hpp"

#include "GameObject.hpp"
#include "MarioStandState.hpp"

MarioMoveState::MarioMoveState(const Spriteset& spriteset) :
    GameObjectState{spriteset}
{

}

void MarioMoveState::onSet(GameObject& object)
{
    auto animation = createAnimation(SpritesetRegionIdentifiers::Mario::Move);
    animation->setDuration(sf::seconds(0.25f));
    animation->setRepeating(true);

    setAnimation(std::move(animation));

    object.setAcceleration(object.getMaxAcceleration());
}

void MarioMoveState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent)
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

void MarioMoveState::onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent)
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

void MarioMoveState::updateSelf(GameObject& object, const sf::Time&)
{
    const auto minVelocity = 4.0f;

    if (std::abs(object.getVelocity().x) > minVelocity)
    {
        const bool sliding =
            (object.getDirection() == GameObject::Directions::Left && object.getVelocity().x > 0.0f) ||
            (object.getDirection() == GameObject::Directions::Right && object.getVelocity().x < 0.0f);

        if (sliding)
        {
            object.setTextureArea(getSprite(SpritesetRegionIdentifiers::Mario::Slide));
        }

    }
    else if (object.getAcceleration().x == 0.0f)
    {
        object.setState(createState<MarioStandState>());
    }
}

void MarioMoveState::moveLeft(GameObject& object) const
{
    object.setDirection(GameObject::Directions::Left);
    object.setAcceleration(object.getMaxAcceleration());
}

void MarioMoveState::moveRight(GameObject& object) const
{
    object.setDirection(GameObject::Directions::Right);
    object.setAcceleration(object.getMaxAcceleration());
}
