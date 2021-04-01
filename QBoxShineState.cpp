#include "QBoxShineState.hpp"

void QBoxShineState::onSet(QBox& entity) noexcept
{
    entity.playShineAnimation();
}

void QBoxShineState::update(QBox& entity, const sf::Time& dt) noexcept
{
    entity.updateShineAnimation(dt);
}

void QBoxShineState::collision(QBox&, const Tile&, const CollisionSideType) noexcept
{

}

void QBoxShineState::collision(QBox& entity, const Entity& collider, const CollisionSideType side) noexcept
{

}

void QBoxShineState::falling(QBox&) noexcept
{

}

void QBoxShineState::onKeyPressed(QBox&, const sf::Event::KeyEvent&) noexcept
{

}

void QBoxShineState::onKeyReleased(QBox&, const sf::Event::KeyEvent&) noexcept
{

}
