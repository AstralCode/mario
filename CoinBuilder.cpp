#include "CoinBuilder.hpp"

#include "ResourceContainer.hpp"
#include "ResourceIdentifiers.hpp"
#include "SpritesetContainer.hpp"
#include "SpritesetRegionIdentifiers.hpp"
#include "EntityContainer.hpp"
#include "ItemActiveState.hpp"

CoinBuilder::CoinBuilder(const ResourceContainer& resources, const SpritesetContainer& spritesets) noexcept :
	mResources{resources},
	mSpritesets{spritesets},
	mItem{nullptr}
{

}

void CoinBuilder::create(EntityContainer& enemies) noexcept
{
	mItem = enemies.create<Item>();
}

void CoinBuilder::buildTexture() noexcept
{
	mItem->setTexture(mResources.getTexture(TextureId::Enemies));
}

void CoinBuilder::buildComponents() noexcept
{
	mItem->setComponent(Entity::ComponentType::Mass);
	mItem->setComponent(Entity::ComponentType::Movement);
}

void CoinBuilder::buildActiveAnimation() noexcept
{
	Animation animation;
	animation.setSpriteset(mSpritesets.getItemSpriteset().getRegion(ItemSpritesetRegionType::Coin));
	animation.setDuration(sf::seconds(0.25f));
	animation.setDelay(sf::seconds(0.25f));
	animation.setDirection(Animation::Directions::Alternate);
	animation.setRepeating(true);

	mItem->setActiveAnimation(animation);
}

void CoinBuilder::buildPickupAnimation() noexcept
{
	Animation animation;
	animation.setSpriteset(mSpritesets.getItemSpriteset().getRegion(ItemSpritesetRegionType::Coin));
	animation.setDuration(sf::seconds(0.15f));
	animation.setRepeating(true);

	mItem->setPickupAnimation(animation);
}

void CoinBuilder::buildState() noexcept
{
	mItem->setState<ItemActiveState>();
}

Item* CoinBuilder::getItem() const noexcept
{
	return mItem;
}
