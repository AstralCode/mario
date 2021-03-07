#include "GraphicsScene.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

#include "MarioCollisionHandler.hpp"
#include "EnemyCollisionHandler.hpp"

GraphicsScene::GraphicsScene() noexcept :
	mGameObjectLayer{*mRoot.addItem<GraphicsItem>()},
	mCollisionModule{*this},
	mGameObjectContainer{mGameObjectLayer}
{
	mCollisionModule.addHandler<MarioCollisionHandler>();
	mCollisionModule.addHandler<EnemyCollisionHandler>();
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

void GraphicsScene::update(const sf::Time& frameTime) noexcept
{
	for (auto& object : mGameObjectContainer)
	{
		object->update(frameTime);
		mPhysicsModule.update(*object, frameTime);
	}

	mCollisionModule.detectCollisions(mGameObjectContainer);

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
