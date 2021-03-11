#include "GraphicsScene.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

#include "StandardCollisionHandler.hpp"
#include "MarioCollisionHandler.hpp"
#include "CreaturesCollisionHandler.hpp"

GraphicsScene::GraphicsScene() noexcept :
	mGameObjectLayer{*mRoot.addItem<GraphicsItem>()},
	mCollisionModule{mTilemapView},
	mGameObjectContainer{mGameObjectLayer}
{
	mCollisionModule.addHandler<StandardCollisionHandler>();
	mCollisionModule.addHandler<MarioCollisionHandler>();
	mCollisionModule.addHandler<CreaturesCollisionHandler>();
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

void GraphicsScene::update(const sf::Time& fixedFrameTime) noexcept
{
	for (auto& object : mGameObjectContainer)
	{
		object->update(fixedFrameTime);
		mPhysicsModule.update(*object, fixedFrameTime);
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
