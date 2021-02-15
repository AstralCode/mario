#pragma once

#include <memory>

#include "GameObjectState.hpp"
#include "Animation.hpp"

namespace sf
{
class Texture;
}

class GraphicsItem;

class GameObject
{
public:
	enum class Directions
	{
		Left, Right
	};

	virtual void setState(std::unique_ptr<GameObjectState> state) = 0;
	virtual void setAnimation(std::unique_ptr<Animation> animation) = 0;

	virtual void setPosition(const sf::Vector2f& position) = 0;
	virtual void setTexture(const sf::Texture& texture) = 0;
	virtual void setTextureArea(const sf::IntRect& area) = 0;

	virtual void setMaxAcceleration(const sf::Vector2f& acceleration) = 0;
	virtual void setAcceleration(const sf::Vector2f& acceleration) = 0;
	virtual void setMaxVelocity(const sf::Vector2f& velocity) = 0;
	virtual void setVelocity(const sf::Vector2f& velocity) = 0;

	virtual void accelerateVelocity(const sf::Vector2f& acceleration) = 0;
	virtual void move(const sf::Vector2f& offset) = 0;

	virtual void setDirectionFactor(const sf::Vector2f& factor) = 0;
	virtual void setDirection(const Directions direction) = 0;
	virtual void turnAround() = 0;

	virtual void destroy() = 0;

	virtual void receiveEvents(const sf::Event& event) = 0;
	
	virtual void update(const sf::Time& frameTime) = 0;

	virtual sf::Vector2f getPosition() const = 0;

	virtual const sf::Vector2f& getMaxAcceleration() const = 0;
	virtual const sf::Vector2f& getAcceleration() const = 0;
	virtual const sf::Vector2f& getMaxVelocity() const = 0;
	virtual const sf::Vector2f& getVelocity() const = 0;

	virtual const sf::Vector2f& getDirectionFactor() const = 0;
	virtual Directions getDirection() const = 0;

	virtual bool hasCollision(const GraphicsItem& item) const = 0;

	virtual bool isContainsPoint(const sf::Vector2f& point) const = 0;
	virtual bool isDestroyed() const = 0;
};
