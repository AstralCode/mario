#include "Item.hpp"

#include "ItemActiveState.hpp"
#include "ItemPickupState.hpp"

Item::Item() noexcept
{
	mStates.registerState<ItemActiveState>();
	mStates.registerState<ItemPickupState>();
}

void Item::setActiveAnimation(const Animation& animation) noexcept
{
	mActiveAnimation = animation;
}

void Item::setPickupAnimation(const Animation& animation) noexcept
{
	mPickupAnimation = animation;
}

void Item::setActiveAnimation() noexcept
{
	mActiveAnimation.play();
	setSpriteArea(mActiveAnimation.getCurrentSpriteArea());
}

void Item::updateActiveAnimation(const sf::Time& dt) noexcept
{
	mActiveAnimation.update(dt);
	setSpriteArea(mActiveAnimation.getCurrentSpriteArea());
}

void Item::setPickupAnimation() noexcept
{
	mPickupAnimation.play();
	setSpriteArea(mPickupAnimation.getCurrentSpriteArea());
}

void Item::updatePickupAnimation(const sf::Time& dt) noexcept
{
	mPickupAnimation.update(dt);
	setSpriteArea(mPickupAnimation.getCurrentSpriteArea());

	mPickupAnimationTime += dt;
}

void Item::update(const sf::Time& dt) noexcept
{
	mStates.getState().update(*this, dt);
}

void Item::collision(const Tile& tile, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, tile, side);
}

void Item::collision(Entity& entity, const CollisionSideType side) const noexcept
{
	entity.collision(*this, side);
}

void Item::collision(const Hero& hero, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, hero, side);
}

void Item::collision(const Enemy& enemy, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, enemy, side);
}

void Item::collision(const Item& item, const CollisionSideType side) noexcept
{
	mStates.getState().collision(*this, item, side);
}

void Item::falling() noexcept
{
	mStates.getState().falling(*this);
}

const sf::Time& Item::getPickupTime() const noexcept
{
	return mPickupAnimationTime;
}
