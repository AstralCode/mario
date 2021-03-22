#include "World.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

#include "ResourceContainer.hpp"
#include "Mario.hpp"
#include "Creature.hpp"

World::World(const ResourceContainer& resources, const SpritesetContainer& spritesets) noexcept :
	mResources{resources},
	mSpritesets{spritesets},
	mEntityLayer{*mRoot.addItem<GraphicsItem>()},
	mEntities{mEntityLayer}
{

}

void World::setTilemap(std::unique_ptr<Tilemap> tilemap, const Textures textureIdentifier, const Fonts fontIdentifier, const sf::Color& background) noexcept
{
	mTilemapView.setTilemap(std::move(tilemap));
	mTilemapView.setTilemapTexture(mResources.getTexture(textureIdentifier));
	mTilemapView.setInformationText(mResources.getFont(fontIdentifier));
	mTilemapView.setBackgroundColor(background);
	mTilemapView.build();
}

void World::spawnMario(const Tile::Index& tileIndex) noexcept
{
	auto entity = mEntities.create<Mario>(mResources, mSpritesets);
	entity->setPosition(mTilemapView.getTilePosition(tileIndex));
}

void World::spawnGoomba(const Tile::Index& tileIndex) noexcept
{
	auto entity = mEntities.create<Creature>(mResources.getTexture(Textures::Enemies), mSpritesets.getGoombaSpriteset().getRegion(GoombaSpritesetRegions::Move));
	entity->setPosition(mTilemapView.getTilePosition(tileIndex));
}

void World::putCoin(const Tile::Index& tileIndex) noexcept
{
	//auto entity = mEntities.create<Item>(mResources.getTexture(Textures::Items), mSpritesets.getItemSpriteset().getRegion(ItemSpritesetRegions::Coin));
	//entity->setPosition(mTilemapView.getTilePosition(tileIndex));
}

void World::receiveEvents(const sf::Event& event) noexcept
{
	mTilemapView.receiveEvents(event);
	mRoot.receiveEvents(event);
}

void World::update(const sf::Time& dt) noexcept
{
	for (auto& entity : mEntities)
	{
		entity->update(dt);
		mPhysicsModule.update(*entity, dt);
	}

	mCollisionModule.detectCollisions(mEntities, mTilemapView);

	mEntities.clean();
	mRoot.clean();
}

const ResourceContainer& World::getResources() noexcept
{
	return mResources;
}

const SpritesetContainer& World::getSpritesets() noexcept
{
	return mSpritesets;
}

TilemapView& World::getTilemapView() noexcept
{
	return mTilemapView;
}

const TilemapView& World::getTilemapView() const noexcept
{
	return mTilemapView;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mTilemapView, states);
	target.draw(mRoot, states);
}
