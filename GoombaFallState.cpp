#include "GoombaFallState.hpp"

#include "GoombaMoveState.hpp"
#include "GoombaLoseState.hpp"

void GoombaFallState::onSet(Goomba& entity) noexcept
{
    entity.setAccelerationX(0.0f);
}

void GoombaFallState::update(Goomba&, const sf::Time&) noexcept
{

}

void GoombaFallState::collision(Goomba& entity, const Tile&, const CollisionSideType side) noexcept
{
    if (side == CollisionSideType::Top)
    {
        entity.setState<GoombaMoveState>();
    }
    else if (side == CollisionSideType::Left || side == CollisionSideType::Right)
    {
        if (entity.hasDirection(Entity::Directions::Right))
        {
            entity.setDirection(Entity::Directions::Left);
        }
        else
        {
            entity.setDirection(Entity::Directions::Right);
        }

        entity.setVelocityX(-entity.getVelocity().getX());
    }
}

void GoombaFallState::collision(Goomba& entity, const Entity& collider, const CollisionSideType side) noexcept
{
    if (!collider.hasComponent(Entity::ComponentType::Transparency))
    {
        if (collider.hasType(EntityType::Hero))
        {
            if (side == CollisionSideType::Bottom)
            {
                entity.setState<GoombaLoseState>();
            }
        }
        else
        {
            if (entity.hasDirection(Entity::Directions::Right))
            {
                entity.setDirection(Entity::Directions::Left);
            }
            else
            {
                entity.setDirection(Entity::Directions::Right);
            }

            entity.setVelocityX(-entity.getVelocity().getX());
        }
    }
}

void GoombaFallState::falling(Goomba&) noexcept
{

}

void GoombaFallState::onKeyPressed(Goomba&, const sf::Event::KeyEvent&) noexcept
{

}

void GoombaFallState::onKeyReleased(Goomba&, const sf::Event::KeyEvent&) noexcept
{

}
