#pragma once

#include "SFML/Graphics/Color.hpp"

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

	GameObject(const GameObjectIdentifiers identifier) noexcept;

	void setState(std::unique_ptr<GameObjectState> state) noexcept;

	void setPositionX(const float x) noexcept;
	void setPositionY(const float y) noexcept;

	void setTexture(const sf::Texture& texture) noexcept;
	void setTextureArea(const SpriteArea& spriteArea) noexcept;

	void setMaxAcceleration(const sf::Vector2f& acceleration) noexcept;
	void setMaxVelocity(const sf::Vector2f& velocity) noexcept;

	void setAcceleration(const sf::Vector2f& acceleration) noexcept;
	void setAccelerationX(const float value) noexcept;
	void setAccelerationY(const float value) noexcept;

	void setVelocity(const sf::Vector2f& velocity) noexcept;
	void setVelocityX(const float value) noexcept;
	void setVelocityY(const float value) noexcept;
	
	void setAreaBoundsVisible(const bool visible) noexcept;
	void setAreaBoundsColor(const sf::Color& color) noexcept;

	void accelerateVelocity(const sf::Vector2f& acceleration) noexcept;

	void setDirection(const Directions direction) noexcept;
	void turnAround() noexcept;

	void destroy() noexcept;

	void moveLeft() noexcept;
	void moveRight() noexcept;

	void onObjectCollision(GameObject& object) noexcept;

	void receiveEvents(const sf::Event& event) noexcept;

	void update(const sf::Time& frameTime) noexcept;

	GameObjectIdentifiers getIdentifier() const noexcept;

	FloatArea getArea() const noexcept override;

	const sf::Vector2f& getMaxAcceleration() const noexcept;
	const sf::Vector2f& getAcceleration() const noexcept;
	const sf::Vector2f& getMaxVelocity() const noexcept;
	const sf::Vector2f& getVelocity() const noexcept;

	Directions getDirection() const noexcept;

	bool hasDirection(const Directions direction) const noexcept;
	bool hasIdentifier(const GameObjectIdentifiers identifier) const noexcept;

	bool isAreaBoundsVisible() const noexcept;

	bool isContainsPoint(const sf::Vector2f& point) const noexcept;
	bool isDestroyed() const noexcept;

private:
	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;
	void drawAreaBounds(sf::RenderTarget& target) const noexcept;

	GameObjectIdentifiers mIdentifier;

	GraphicsSpriteItem* mSprite;

	std::unique_ptr<GameObjectState> mState;

	sf::Vector2f mMaxAcceleration;
	sf::Vector2f mAcceleration;
	sf::Vector2f mVelocity;
	sf::Vector2f mMaxVelocity;

	Directions mDirection;

	sf::Color mAreaBoundsColor;

	bool mAreaBoundsVisible;
	bool mMouseOver;
};
