#pragma once

#include "GameObjectState.hpp"
#include "GraphicsSpriteItem.hpp"
#include "GameSpriteAtlas.hpp"

class GameObject
{
public:
	enum class Directions
	{
		Left, Right
	};

	GameObject(GraphicsSpriteItem* sprite);

	void setState(std::unique_ptr<GameObjectState> state);

	void setPosition(const sf::Vector2f& position);
	void setTexture(const sf::Texture& texture);
	void setTextureArea(const sf::IntRect& area);

	void setMaxAcceleration(const sf::Vector2f& acceleration);
	void setAcceleration(const sf::Vector2f& acceleration);
	void setMaxVelocity(const sf::Vector2f& velocity);
	void setVelocity(const sf::Vector2f& velocity);

	void accelerateVelocity(const sf::Vector2f& acceleration);
	void move(const sf::Vector2f& offset);

	void setDirectionFactor(const sf::Vector2f& factor);
	void setDirection(const Directions direction);
	void turnAround();

	void dispose();
	void destroy();

	void receiveEvents(const sf::Event& event);
	
	void update(const sf::Time& frameTime);

	sf::Vector2f getPosition() const;

	const sf::Vector2f& getMaxAcceleration() const;
	const sf::Vector2f& getAcceleration() const;
	const sf::Vector2f& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;

	const sf::Vector2f& getDirectionFactor() const;
	Directions getDirection() const;

	bool hasCollision(const GameObject& object) const;

	bool isContainsPoint(const sf::Vector2f& point) const;
	bool isDestroyed() const;

private:
	GraphicsSpriteItem* mSprite;
	std::unique_ptr<GameObjectState> mState;

	sf::Vector2f mMaxAcceleration;
	sf::Vector2f mAcceleration;
	sf::Vector2f mVelocity;
	sf::Vector2f mMaxVelocity;

	sf::Vector2f mDirectionFactor;
	Directions mDirection;

	bool mMouseOver;
};
