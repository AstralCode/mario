#include "World.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

World::World() noexcept :
	mEntityLayer{*mRoot.addItem<GraphicsItem>()},
	mEntities{mEntityLayer}
{

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

TilemapView& World::getTilemapView() noexcept
{
	return mTilemapView;
}

const TilemapView& World::getTilemapView() const noexcept
{
	return mTilemapView;
}

EntityContainer& World::getEntities() noexcept
{
	return mEntities;
}

const EntityContainer& World::getEntities() const noexcept
{
	return mEntities;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mTilemapView, states);
	target.draw(mRoot, states);
}
