#include "GameObjectFactory.hpp"

#include "GameObject.hpp"
#include "GameObjectCreator.hpp"
#include "ResourceContainer.hpp"
#include "SpritesetContainer.hpp"
#include "Spriteset.hpp"
#include "GraphicsTextItem.hpp"

GameObjectFactory::GameObjectFactory(ResourceContainer& resourceContainer, SpritesetContainer& spritesetContainer, GameObjectCreator& gameObjectCreator) :
	mResourceContainer{resourceContainer},
	mSpritesetContainer{spritesetContainer},
	mGameObjectCreator{gameObjectCreator}
{

}

GameObject* GameObjectFactory::createMario(GraphicsItem* sceneLayer)
{
	auto object = create(sceneLayer, TextureIdentifiers::Mario);
	object->setMaxAcceleration({32.0f * 18.0f, 0.0f});
	object->setMaxVelocity({32.0f * 18.0f, 0.0f});

	return object;
}

GameObject* GameObjectFactory::createGoomba(GraphicsItem* sceneLayer)
{
	auto animation = std::make_unique<Animation>(getSpritesetRegion(SpritesetIdentifiers::Enemy, SpritesetRegionIdentifiers::Goomba::Move));
	animation->setDuration(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Normal);
	animation->setRepeating(true);
	animation->stop();
	animation->play();

	auto object = create(sceneLayer, TextureIdentifiers::Enemies);
	object->setAnimation(std::move(animation));
	object->setMaxAcceleration({32.0f * 8.0f, 0.0f});
    object->setMaxVelocity({32.0f * 8.0f, 0.0f});
	object->setAcceleration(object->getMaxAcceleration());

	return object;
}

GameObject* GameObjectFactory::createCoin(GraphicsItem* sceneLayer)
{
	auto animation = std::make_unique<Animation>(getSpritesetRegion(SpritesetIdentifiers::Items, SpritesetRegionIdentifiers::Items::Coin));
	animation->setDuration(sf::seconds(0.25f));
	animation->setDelay(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Alternate);
	animation->setRepeating(true);
	animation->stop();
	animation->play();

	auto object = create(sceneLayer, TextureIdentifiers::Scenery);
	object->setAnimation(std::move(animation));

	return object;
}

GameObject* GameObjectFactory::createScoreCoin(GraphicsItem* sceneLayer)
{
	auto animation = std::make_unique<Animation>(getSpritesetRegion(SpritesetIdentifiers::Items, SpritesetRegionIdentifiers::Items::ScoreCoin));
	animation->setDuration(sf::seconds(0.25f));
	animation->setDelay(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Alternate);
	animation->setRepeating(true);
	animation->stop();
	animation->play();

	auto object = create(sceneLayer, TextureIdentifiers::Scenery);
	object->setAnimation(std::move(animation));

	return object;
}

GameObject* GameObjectFactory::createQuestionMarkBox(GraphicsItem* sceneLayer)
{
	auto animation = std::make_unique<Animation>(getSpritesetRegion(SpritesetIdentifiers::Blocks, SpritesetRegionIdentifiers::Blocks::QuestionMarkBox));
	animation->setDuration(sf::seconds(0.25f));
	animation->setDelay(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Alternate);
	animation->setRepeating(true);
	animation->stop();
	animation->play();

	auto object = create(sceneLayer, TextureIdentifiers::Scenery);
	object->setAnimation(std::move(animation));

	return object;
}

GameObject* GameObjectFactory::create(GraphicsItem* sceneLayer, const TextureIdentifiers textureIdentifier) const
{
	auto object = mGameObjectCreator.create(sceneLayer->addItem<GraphicsSpriteItem>());
	object->setTexture(mResourceContainer.getTexture(textureIdentifier));

	return object;
}

const SpritesetRegion& GameObjectFactory::getSpritesetRegion(const std::string& spritesetIdetntifier, const std::string& spritesetRegionIdentifier) const noexcept
{
	return mSpritesetContainer.getSpriteset(spritesetIdetntifier).getRegion(spritesetRegionIdentifier);
}
