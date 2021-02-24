#pragma once

#include "SFML/Graphics/Color.hpp"

#include "GraphicsItem.hpp"
#include "GameObjectIdentifiers.hpp"
#include "GameObjectState.hpp"

class GraphicsSpriteItem;

enum class Directions
{
	Left,
	Right
};

class GameObject final : public GraphicsItem
{
public:
	GameObject(const GameObjectIdentifiers identifier);

	void setState(std::unique_ptr<GameObjectState> state);

	void setPositionX(const float x);
	void setPositionY(const float y);

	void setTexture(const sf::Texture& texture);
	void setTextureArea(const SpriteArea& spriteArea);

	void setMaxAcceleration(const sf::Vector2f& acceleration);
	void setMaxVelocity(const sf::Vector2f& velocity);

	void setAcceleration(const sf::Vector2f& acceleration);
	void setAccelerationX(const float value);
	void setAccelerationY(const float value);

	void setVelocity(const sf::Vector2f& velocity);
	void setVelocityX(const float value);
	void setVelocityY(const float value);
	
	void setBoundsVisible(const bool visible);
	void setBoundsColor(const sf::Color& color);

	void accelerateVelocity(const sf::Vector2f& acceleration);

	void setDirection(const Directions direction);
	void turnAround();

	void destroy();

	void moveLeft();
	void moveRight();

	void onObjectCollision(GameObject& object);

	void receiveEvents(const sf::Event& event);

	void update(const sf::Time& frameTime);

	GameObjectIdentifiers getIdentifier() const;

	sf::FloatRect getBounds() const override;

	const sf::Vector2f& getMaxAcceleration() const;
	const sf::Vector2f& getAcceleration() const;
	const sf::Vector2f& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;

	Directions getDirection() const;

	bool hasDirection(const Directions direction) const;
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

	Directions mDirection;

	sf::Color mBoundsColor;

	bool mBoundsVisible;
	bool mMouseOver;
};
