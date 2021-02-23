#pragma once

#include "GraphicsItem.hpp"
#include "GameObjectIdentifiers.hpp"
#include "GameObjectState.hpp"

class GraphicsSpriteItem;

class GameObject final : public GraphicsItem
{
public:
	enum class Directions
	{
		Left,
		Right
	};

	GameObject(const GameObjectIdentifiers identifier);

	void setState(std::unique_ptr<GameObjectState> state);

	void setTexture(const sf::Texture& texture);
	void setTextureArea(const SpriteArea& spriteArea);

	void setMaxAcceleration(const sf::Vector2f& acceleration);
	void setAcceleration(const sf::Vector2f& acceleration);
	void setMaxVelocity(const sf::Vector2f& velocity);
	void setVelocity(const sf::Vector2f& velocity);
	
	void setBoundsVisible(const bool visible);

	void accelerateVelocity(const sf::Vector2f& acceleration);

	void setDirectionFactor(const sf::Vector2f& factor);
	void setDirection(const Directions direction);
	void turnAround();

	void destroy();

	void onObjectCollision(GameObject& object);

	void receiveEvents(const sf::Event& event);

	void update(const sf::Time& frameTime);

	GameObjectIdentifiers getIdentifier() const;

	sf::FloatRect getBounds() const override;

	const sf::Vector2f& getMaxAcceleration() const;
	const sf::Vector2f& getAcceleration() const;
	const sf::Vector2f& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;

	const sf::Vector2f& getDirectionFactor() const;
	Directions getDirection() const;

	bool hasIdentifier(const GameObjectIdentifiers identifier) const;

	bool isBoundsVisible() const;;

	bool isContainsPoint(const sf::Vector2f& point) const;
	bool isDestroyed() const;

private:
	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;
	void drawBounds(sf::RenderTarget& target) const;

	GameObjectIdentifiers mIdentifier;

	GraphicsSpriteItem* mSprite;

	std::unique_ptr<GameObjectState> mState;

	sf::Vector2f mMaxAcceleration;
	sf::Vector2f mAcceleration;
	sf::Vector2f mVelocity;
	sf::Vector2f mMaxVelocity;

	sf::Vector2f mDirectionFactor;
	Directions mDirection;

	bool mBoundsVisible;
	bool mMouseOver;
};
