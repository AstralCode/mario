#include "QBox.hpp"

#include "QBoxShineState.hpp"

#include "World.hpp"
#include "ResourceContainer.hpp"
#include "SpritesetContainer.hpp"

QBox::QBox(World& world) noexcept :
	Entity{EntityType::Item, world}
{
	mStates.registerState<QBoxShineState>();

	auto& resources = world.getResources();
	auto& spritesets = world.getSpritesets();

	setTexture(resources.getTexture(TextureId::Items));
	setComponent(Entity::ComponentType::Solid);

	mShineAnimation.setSpriteset(spritesets.getItemSpriteset().getRegion(ItemSpritesetRegionType::QBox));
	mShineAnimation.setDuration(sf::seconds(0.25f));
	mShineAnimation.setDelay(sf::seconds(0.25f));
	mShineAnimation.setDirection(Animation::Directions::Alternate);
	mShineAnimation.setRepeating(true);

	setState<QBoxShineState>();
	Entity::centerOrigin(*this);
}

void QBox::playShineAnimation() noexcept
{
	mShineAnimation.play();
	setSpriteArea(mShineAnimation.getCurrentSpriteArea());
}

void QBox::updateShineAnimation(const sf::Time& dt) noexcept
{
	mShineAnimation.update(dt);
	setSpriteArea(mShineAnimation.getCurrentSpriteArea());
}

void QBox::update(const sf::Time& dt) noexcept
{
	mStates.getState().update(*this, dt);
}

void QBox::collision(const Tile& tile, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, tile, side);
}

void QBox::collision(const Entity& collider, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, collider, side);
}

void QBox::falling() noexcept
{
	mStates.getState().falling(*this);
}
