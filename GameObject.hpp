#pragma once

#include "GameObjectState.hpp"
#include "GraphicsSpriteItem.hpp"

class GameObject
{
public:
	enum class Directions
	{
		Left,
		Right
	};

	GameObject(GraphicsSpriteItem* sprite);

	void setState(GameObjectState* state);

	void setPosition(const sf::Vector2f& position);
	void setTexture(const sf::Texture& texture);
	void setTextureArea(const sf::IntRect& area);
	
	void setAcceleration(const sf::Vector2f& acceleration);
	void setMaxVelocity(const sf::Vector2f& maxVelocity);
	void setVelocity(const sf::Vector2f& velocity);

	void accelerateVelocity(const sf::Vector2f& acceleration);
	void move(const sf::Vector2f& offset);

	void setDirection(const Directions direction);
	void turnAround();

	void dispose();
	void destroy();

	void receiveEvents(const sf::Event& event);
	
	void update(const sf::Time& frameTime);

	sf::Vector2f getPosition() const;

	const sf::Vector2f& getAcceleration() const;
	const sf::Vector2f& getVelocity() const;
	const sf::Vector2f& getMaxVelocity() const;

	const sf::Vector2f& getDirectionFactor() const;
	Directions getDirection() const;

	bool hasCollision(const GameObject& object) const;

	bool isContainsPoint(const sf::Vector2f& point) const;
	bool isDestroyed() const;

private:
	void updateMovement(const sf::Time& frameTime);

	GraphicsSpriteItem* mSprite;
	GameObjectState* mState;

	sf::Vector2f mVelocity;
	sf::Vector2f mMaxVelocity;
	sf::Vector2f mAcceleration;

	sf::Vector2f mDirectionFactor;
	Directions mDirection;

	bool mIsMouseOver;
};
