#include "GoombaMoveState.hpp"

#include "GoombaFallState.hpp"
#include "GoombaLoseState.hpp"

void GoombaMoveState::onSet(Goomba& entity) noexcept
{
    entity.setAccelerationX(Constants::World::Tilemap::TileSize * 5.0);
    entity.setAccelerationY(0.0f);
    entity.playMoveAnimation();
}

void GoombaMoveState::update(Goomba& entity, const sf::Time& dt) noexcept
{
    entity.updateMoveAnimation(dt);
}

void GoombaMoveState::collision(Goomba& entity, const Tile&, const CollisionSideType side) noexcept
{
    if (side == CollisionSideType::Left || side == CollisionSideType::Right)
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

void GoombaMoveState::collision(Goomba& entity, const Entity& collider, const CollisionSideType side) noexcept
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

        if (collider.hasType(EntityType::Enemy))
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

void GoombaMoveState::falling(Goomba& entity) noexcept
{
    entity.setState<GoombaFallState>();
}

void GoombaMoveState::onKeyPressed(Goomba&, const sf::Event::KeyEvent&) noexcept
{

}

void GoombaMoveState::onKeyReleased(Goomba&, const sf::Event::KeyEvent&) noexcept
{

}
