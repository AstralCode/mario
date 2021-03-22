#include "Item.hpp"

Item::Item(const sf::Texture& texture, const SpritesetRegion& sprites) noexcept :
	mShineAnimation{sprites}
{
	setTexture(texture);

	mShineAnimation.setDuration(sf::seconds(Constants::World::Items::ShineAnimationDuration));
	mShineAnimation.setDirection(Animation::Directions::Alternate);
	mShineAnimation.setDelay(sf::seconds(1.0f));
	mShineAnimation.setRepeating(true);

	//mStates.registerState<ItemMoveState>(Item::States::Move);

	//setState(Item::States::Move);
}

void Item::setState(const Item::States identifier)
{
	mStates.setCurrentState(*this, identifier);
}

void Item::setMoveAnimation() noexcept
{
	mShineAnimation.play();

	setSpriteArea(mShineAnimation.getCurrentSpriteArea());
}

void Item::updateMoveAnimation(const sf::Time& dt) noexcept
{
	mShineAnimation.update(dt);

	setSpriteArea(mShineAnimation.getCurrentSpriteArea());
}

void Item::update(const sf::Time& dt) noexcept
{
	mStates.getCurrentState().update(*this, dt);
}

void Item::tileCollision(const Tile& tile, const Tile::Sides side) noexcept
{
	mStates.getCurrentState().tileCollision(*this, tile, side);
}

void Item::entityCollision(Entity& collider) noexcept
{
	mStates.getCurrentState().entityCollision(*this, collider);
}

void Item::falling() noexcept
{
	mStates.getCurrentState().falling(*this);
}

bool Item::isJumping() const noexcept
{
	return mStates.getCurrentState().isJumping();
}

bool Item::isFalling() const noexcept
{
	return mStates.getCurrentState().isFalling();
}
