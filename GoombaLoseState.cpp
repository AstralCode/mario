#include "GoombaLoseState.hpp"

void GoombaLoseState::onSet(Goomba& entity) noexcept
{
    entity.setComponent(Entity::ComponentType::Transparency);
    entity.unsetComponent(Entity::ComponentType::Movement);
    entity.unsetComponent(Entity::ComponentType::Mass);
    entity.setAccelerationX(0.0f);
    entity.setAccelerationY(0.0f);
    entity.playLoseAnimation();
}

void GoombaLoseState::update(Goomba& entity, const sf::Time& dt) noexcept
{
    entity.updateLoseAnimation(dt);

    if (entity.getLoseTime() >= sf::seconds(1.0f))
    {
        entity.destroy();
    }
}

void GoombaLoseState::collision(Goomba&, const Tile&, const CollisionSideType) noexcept
{

}

void GoombaLoseState::collision(Goomba&, const Entity&, const CollisionSideType) noexcept
{

}

void GoombaLoseState::falling(Goomba&) noexcept
{

}

void GoombaLoseState::onKeyPressed(Goomba&, const sf::Event::KeyEvent&) noexcept
{

}

void GoombaLoseState::onKeyReleased(Goomba&, const sf::Event::KeyEvent&) noexcept
{

}
