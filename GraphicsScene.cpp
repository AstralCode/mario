#include "GraphicsScene.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

GraphicsScene::GraphicsScene() noexcept :
	mGameObjectLayer{*mRoot.addItem<GraphicsItem>()},
	mGameObjectContainer{mGameObjectLayer}
{

}

GameObject* GraphicsScene::createGameObject(const GameObjectIdentifiers identifier) noexcept
{
	return mGameObjectContainer.create(identifier);
}

void GraphicsScene::receiveEvents(const sf::Event& event) noexcept
{
	mTilemapView.receiveEvents(event);
	mRoot.receiveEvents(event);
}

void GraphicsScene::update(const sf::Time& dt) noexcept
{
	for (auto& object : mGameObjectContainer)
	{
		object->update(dt);
		mPhysicsModule.update(*object, dt);
	}

	mCollisionModule.detectCollisions(mGameObjectContainer, mTilemapView);

	mGameObjectContainer.clean();
	mRoot.clean();
}

TilemapView& GraphicsScene::getTilemapView() noexcept
{
	return mTilemapView;
}

const TilemapView& GraphicsScene::getTilemapView() const noexcept
{
	return mTilemapView;
}

void GraphicsScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mTilemapView, states);
	target.draw(mRoot, states);
}
