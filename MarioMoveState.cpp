#include "MarioMoveState.hpp"

#include "GameObject.hpp"
#include "MarioStandState.hpp"

MarioMoveState::MarioMoveState(const Spriteset& spriteset) noexcept :
    GameObjectState{spriteset}
{

}

void MarioMoveState::onSet(GameObject&) noexcept
{
    auto animation = createAnimation(SpritesetRegionIdentifiers::Mario::Move);
    animation->setDuration(sf::seconds(0.25f));
    animation->setRepeating(true);

    setAnimation(std::move(animation));
}

void MarioMoveState::onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
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

void MarioMoveState::onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept
{
    if (keyEvent.code == sf::Keyboard::Q || keyEvent.code == sf::Keyboard::E)
    {
        object.setAcceleration({});
    }

    if (keyEvent.code == sf::Keyboard::Q)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            object.moveRight();
        }
    }
    else if (keyEvent.code == sf::Keyboard::E)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            object.moveLeft();
        }
    }
}

void MarioMoveState::updateSelf(GameObject& object, const sf::Time&) noexcept
{
    if (std::abs(object.getAcceleration().getX()) > 32.0f)
    {
        const bool sliding =
            object.hasDirection(GameObject::Directions::Left) && object.getVelocity().getX() > 0.0f ||
            object.hasDirection(GameObject::Directions::Right) && object.getVelocity().getX() < 0.0f;

        if (sliding)
        {
            object.setTextureArea(getSpriteArea(SpritesetRegionIdentifiers::Mario::Slide));
        }

    }
    else if (std::abs(object.getVelocity().getX()) < 1.0f)
    {
        object.setState(createState<MarioStandState>());
    }
}
