#include "GameObjectFactory.hpp"

#include "GameObject.hpp"
#include "GameObjectCreator.hpp"
#include "GameResourceContainer.hpp"
#include "GameSpriteAtlasContainer.hpp"
#include "AnimationFactory.hpp"
#include "GraphicsTextItem.hpp"
#include "MarioStandState.hpp"

GameObjectFactory::GameObjectFactory(GameResourceContainer& gameResourceContainer, GameSpriteAtlasContainer& gameSpriteAtlasContainer, GameObjectCreator& gameObjectCreator, AnimationFactory& animationFactory) :
	mGameResourceContainer{gameResourceContainer},
	mGameSpriteAtlasContainer{gameSpriteAtlasContainer},
	mGameObjectCreator{gameObjectCreator},
	mAnimationFactory{animationFactory}
{

}

GameObject* GameObjectFactory::createMario(GraphicsItem* sceneLayer) const
{
	auto object = create(sceneLayer, TextureIdentifiers::Mario);
	object->setMaxAcceleration({32.0f * 18.0f, 0.0f});
	object->setMaxVelocity({32.0f * 18.0f, 0.0f});

	return object;
}

GameObject* GameObjectFactory::createGoomba(GraphicsItem* sceneLayer) const
{
	auto moveAnimation = mAnimationFactory.createGoombaMove();

	auto state = std::make_unique<GameObjectState>();
	state->setAnimation(std::move(moveAnimation));

	auto object = create(sceneLayer, TextureIdentifiers::Enemies);
	object->setMaxAcceleration({32.0f * 8.0f, 0.0f});
    object->setMaxVelocity({32.0f * 8.0f, 0.0f});
	object->setAcceleration(object->getMaxAcceleration());
	object->setState(std::move(state));

	return object;
}

GameObject* GameObjectFactory::createCoin(GraphicsItem* sceneLayer) const
{
	auto animation = mAnimationFactory.createCoinShine();

	auto state = std::make_unique<GameObjectState>();
	state->setAnimation(std::move(animation));

	auto object = create(sceneLayer, TextureIdentifiers::Scenery);
	object->setState(std::move(state));

	return object;
}

GameObject* GameObjectFactory::create(GraphicsItem* sceneLayer, const TextureIdentifiers textureIdentifier) const
{
	auto object = mGameObjectCreator.create(sceneLayer->addItem<GraphicsSpriteItem>());
	object->setTexture(mGameResourceContainer.getTexture(textureIdentifier));

	return object;
}
