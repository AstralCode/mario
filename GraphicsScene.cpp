#include "GraphicsScene.hpp"

#include <algorithm>
#include <functional>

#include "SFML/Graphics/RenderTarget.hpp"

#include "MarioCollisionHandler.hpp"
#include "EnemyCollisionHandler.hpp"

GraphicsScene::GraphicsScene() noexcept :
	mCollisionModule{mTilemapView}
{
	mCollisionModule.addHandler<MarioCollisionHandler>();
	mCollisionModule.addHandler<EnemyCollisionHandler>();
}

GameObject* GraphicsScene::createGameObject(const GameObjectIdentifiers identifier) noexcept
{
	auto object = mGameObjectLayer.addItem<GameObject>(identifier);
	mGameObjects.push_back(object);

    return object;
}

void GraphicsScene::receiveEvents(const sf::Event& event) noexcept
{
	mTilemapView.receiveEvents(event);
	mGameObjectLayer.receiveEvents(event);
}

void GraphicsScene::update(const sf::Time& frameTime) noexcept
{
	for (auto& object : mGameObjects)
	{
		object->update(frameTime);
		mPhysicsModule.update(*object, frameTime);
	}

	mCollisionModule.detectCollisions(mGameObjects);

	auto gameObjectsIterator = std::remove_if(mGameObjects.begin(), mGameObjects.end(), std::mem_fn(&GameObject::isDestroyed));
	mGameObjects.erase(gameObjectsIterator, mGameObjects.end());

	mGameObjectLayer.clean();
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
	target.draw(mGameObjectLayer, states);
}
