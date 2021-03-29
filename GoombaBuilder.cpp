#include "GoombaBuilder.hpp"

#include "ResourceContainer.hpp"
#include "ResourceIdentifiers.hpp"
#include "SpritesetContainer.hpp"
#include "SpritesetRegionIdentifiers.hpp"
#include "EntityContainer.hpp"
#include "EnemyMoveState.hpp"

GoombaBuilder::GoombaBuilder(const ResourceContainer& resources, const SpritesetContainer& spritesets) noexcept :
	mResources{resources},
	mSpritesets{spritesets},
	mEnemy{nullptr}
{

}

void GoombaBuilder::create(EntityContainer& enemies) noexcept
{
	mEnemy = enemies.create<Enemy>();
}

void GoombaBuilder::buildTexture() noexcept
{
	mEnemy->setTexture(mResources.getTexture(TextureId::Enemies));
}

void GoombaBuilder::buildComponents() noexcept
{
	mEnemy->setComponent(Entity::ComponentType::Mass);
	mEnemy->setComponent(Entity::ComponentType::Movement);
}

void GoombaBuilder::buildMoveAnimation() noexcept
{
	Animation animation;
	animation.setSpriteset(mSpritesets.getGoombaSpriteset().getRegion(GoombaSpritesetRegionType::Move));
	animation.setDuration(sf::seconds(0.25f));
	animation.setRepeating(true);

	mEnemy->setMoveAnimation(animation);
}

void GoombaBuilder::buildLoseAnimation() noexcept
{
	Animation animation;
	animation.setSpriteset(mSpritesets.getGoombaSpriteset().getRegion(GoombaSpritesetRegionType::Lose));

	mEnemy->setLoseAnimation(animation);
}

void GoombaBuilder::buildState() noexcept
{
	mEnemy->setState<EnemyMoveState>();
}

Enemy* GoombaBuilder::getEnemy() const noexcept
{
    return mEnemy;
}
