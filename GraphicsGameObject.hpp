#pragma once

#include "GraphicsItem.hpp"
#include "GameObjectState.hpp"

class GraphicsSpriteItem;

class GraphicsGameObject final : public GraphicsItem
{
public:
	enum class Directions
	{
		Left,
		Right
	};

	GraphicsGameObject();

	void setState(std::unique_ptr<GameObjectState> state);

	void setTexture(const sf::Texture& texture);
	void setTextureArea(const SpriteArea& spriteArea);

	void setMaxAcceleration(const sf::Vector2f& acceleration);
	void setAcceleration(const sf::Vector2f& acceleration);
	void setMaxVelocity(const sf::Vector2f& velocity);
	void setVelocity(const sf::Vector2f& velocity);
	
	void setBoundsVisible(const bool visible);

	void accelerateVelocity(const sf::Vector2f& acceleration);
	void move(const sf::Vector2f& offset);

	void setDirectionFactor(const sf::Vector2f& factor);
	void setDirection(const Directions direction);
	void turnAround();

	void destroy();

	void receiveEvents(const sf::Event& event);

	void update(const sf::Time& frameTime);

	sf::FloatRect getBounds() const override;

	const sf::Vector2f& getMaxAcceleration() const;
	const sf::Vector2f& getAcceleration() const;
	const sf::Vector2f& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;

	const sf::Vector2f& getDirectionFactor() const;
	Directions getDirection() const;

	bool hasCollision(const GraphicsGameObject& object) const;
		
	bool isBoundsVisible() const;;

	bool isContainsPoint(const sf::Vector2f& point) const;
	bool isDestroyed() const;

private:
	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;
	void drawBounds(sf::RenderTarget& target) const;

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
