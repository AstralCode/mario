#include "GameObjectFactory.hpp"

#include "ResourceContainer.hpp"
#include "GraphicsScene.hpp"
#include "MarioStandState.hpp"

GameObjectFactory::GameObjectFactory(ResourceContainer& resources, SpritesetContainer& spritesets, GraphicsScene& scene) noexcept :
	mResources{resources},
	mSpritesets{spritesets},
	mScene{scene}
{

}

GameObject* GameObjectFactory::createMario() noexcept
{
	auto state = std::make_unique<MarioStandState>(mSpritesets.getMarioSpriteset());

	auto object = createObject(GameObjectIdentifiers::Mario, Textures::Mario);
	object->setMaxVelocity({Constants::GameObjects::Mario::MaxVelocityX, Constants::GameObjects::Mario::MaxVelocityY});
	object->setState(std::move(state));

	return object;
}

GameObject* GameObjectFactory::createGoomba() noexcept
{
	auto animation = std::make_unique<Animation>SpritesetIdentifiers::Enemy, SpritesetRegionIdentifiers::Goomba::Move);
	animation->setDuration(sf::seconds(Constants::GameObjects::Goomba::MoveAnimationDuration));
	animation->setDirection(Animation::Directions::Normal);
	animation->setRepeating(true);

	auto state = createObjectState<GameObjectState>(SpritesetIdentifiers::Enemy);
	state->setAnimation(std::move(animation));

	auto object = createObject(GameObjectIdentifiers::Goomba, Textures::Enemies);
	object->setState(std::move(state));
    object->setMaxVelocity({32.0f * 8.0f, 32.0f * 8.0f});
	object->setAccelerationX(object->getMaxAcceleration().getX());

	return object;
}

GameObject* GameObjectFactory::createCoin() noexcept
{
	auto animation = createAnimation(SpritesetIdentifiers::Items, SpritesetRegionIdentifiers::Items::Coin);
	animation->setDuration(sf::seconds(0.25f));
	animation->setDelay(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Alternate);
	animation->setRepeating(true);

	auto state = createObjectState<GameObjectState>(SpritesetIdentifiers::Items);
	state->setAnimation(std::move(animation));

	auto object = createObject(GameObjectIdentifiers::Coin, Textures::Items);
	object->setState(std::move(state));

	return object;
}

GameObject* GameObjectFactory::createScoreCoin() noexcept
{
	auto animation = createAnimation(SpritesetIdentifiers::Items, SpritesetRegionIdentifiers::Items::ScoreCoin);
	animation->setDuration(sf::seconds(0.25f));
	animation->setDelay(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Alternate);
	animation->setRepeating(true);

	auto state = createObjectState<GameObjectState>(SpritesetIdentifiers::Items);
	state->setAnimation(std::move(animation));

	auto object = createObject(GameObjectIdentifiers::ScoreCoin, Textures::Items);
	object->setState(std::move(state));

	return object;
}

GameObject* GameObjectFactory::createQuestionMarkBox() noexcept
{
	auto animation = createAnimation(SpritesetIdentifiers::Blocks, SpritesetRegionIdentifiers::Blocks::QuestionMarkBox);
	animation->setDuration(sf::seconds(0.25f));
	animation->setDelay(sf::seconds(0.25f));
	animation->setDirection(Animation::Directions::Alternate);
	animation->setRepeating(true);

	auto state = createObjectState<GameObjectState>(SpritesetIdentifiers::Blocks);
	state->setAnimation(std::move(animation));

	auto object = createObject(GameObjectIdentifiers::QuestionMarkBox, Textures::Items);
	object->setState(std::move(state));

	return object;
}

GameObject* GameObjectFactory::createObject(const GameObjectIdentifiers identifier, const Textures textureIdentifier) const noexcept
{
	auto object = mScene.createGameObject(identifier);
	object->setTexture(mResources.getTexture(textureIdentifier));

	return object;
}
