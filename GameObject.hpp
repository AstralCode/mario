#pragma once

#include "SFML/Graphics/Color.hpp"

#include "GraphicsItem.hpp"
#include "GameObjectIdentifiers.hpp"
#include "GameObjectState.hpp"

class Sprite;

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

	void setTexture(const sf::Texture& texture) noexcept;
	void setTextureArea(const SpriteArea& area) noexcept;

	void setMaxAcceleration(const FloatPoint& acceleration) noexcept;
	void setMaxVelocity(const FloatPoint& velocity) noexcept;

	void setAcceleration(const FloatPoint& acceleration) noexcept;
	void setAccelerationX(const float value) noexcept;
	void setAccelerationY(const float value) noexcept;

	void setVelocity(const FloatPoint& velocity) noexcept;
	void setVelocityX(const float value) noexcept;
	void setVelocityY(const float value) noexcept;
	
	void setAreaBoundsVisible(const bool visible) noexcept;
	void setAreaBoundsColor(const sf::Color& color) noexcept;

	void accelerateVelocity(const FloatPoint& acceleration) noexcept;

	void setDirection(const Directions direction) noexcept;
	void turnAround() noexcept;

	void destroy() noexcept;

	void moveLeft() noexcept;
	void moveRight() noexcept;

	void onObjectCollision(GameObject& object) noexcept;

	void update(const sf::Time& frameTime) noexcept;

	GameObjectIdentifiers getIdentifier() const noexcept;

	FloatArea getArea() const noexcept override;

	const FloatPoint& getMaxAcceleration() const noexcept;
	const FloatPoint& getAcceleration() const noexcept;
	const FloatPoint& getMaxVelocity() const noexcept;
	const FloatPoint& getVelocity() const noexcept;

	Directions getDirection() const noexcept;

	bool hasDirection(const Directions direction) const noexcept;
	bool hasIdentifier(const GameObjectIdentifiers identifier) const noexcept;

	bool isAreaBoundsVisible() const noexcept;

	bool isContainsPoint(const FloatPoint& point) const noexcept;
	bool isDestroyed() const noexcept;

private:
	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;
	void drawAreaBounds(sf::RenderTarget& target) const noexcept;

	GameObjectIdentifiers mIdentifier;

	Sprite* mSprite;

	std::unique_ptr<GameObjectState> mState;

	FloatPoint mMaxAcceleration;
	FloatPoint mAcceleration;
	FloatPoint mVelocity;
	FloatPoint mMaxVelocity;

	Directions mDirection;

	sf::Color mAreaBoundsColor;

	bool mAreaBoundsVisible;
	bool mMouseOver;
};
