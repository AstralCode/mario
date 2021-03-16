#pragma once

#include "SFML/Graphics/Color.hpp"

#include "Constants.hpp"
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
	void setTextureArea(const IntArea& area) noexcept;

	void setMaxVelocity( const FloatPoint& velocity ) noexcept;

	void setAcceleration(const FloatPoint& acceleration) noexcept;
	void setAccelerationX(const float value) noexcept;
	void setAccelerationY(const float value) noexcept;

	void setVelocity(const FloatPoint& velocity) noexcept;
	void setVelocityX(const float value) noexcept;
	void setVelocityY(const float value) noexcept;

	void setAreaBoundsVisible(const bool visible) noexcept;
	void setAreaBoundsColor(const sf::Color& color) noexcept;

	void accelerateVelocity(const FloatPoint& acceleration) noexcept;
	void accelerateVelocityX(const float acceleration) noexcept;
	void accelerateVelocityY(const float acceleration) noexcept;

	void setDirection(const Directions direction) noexcept;
	void turnAround() noexcept;

	void destroy() noexcept;

	void moveLeft() noexcept;
	void moveRight() noexcept;

	void onTileTopCollision(const TileIndex& tileIndex) noexcept;
	void onTileBottomCollision(const TileIndex& tileIndex) noexcept;
	void onTileLeftCollision(const TileIndex& tileIndex) noexcept;
	void onTileRightCollision(const TileIndex& tileIndex) noexcept;

	void onObjectCollision(GameObject& object) noexcept;

	void update(const sf::Time& fixedFrameTime) noexcept;

	FloatArea getLocalArea() const noexcept override;

	GameObjectIdentifiers getIdentifier() const noexcept;

	const FloatPoint& getAcceleration() const noexcept;
	const FloatPoint& getMaxVelocity() const noexcept;
	const FloatPoint& getVelocity() const noexcept;

	Directions getDirection() const noexcept;

	bool hasDirection(const Directions direction) const noexcept;
	bool hasIdentifier(const GameObjectIdentifiers identifier) const noexcept;

	bool isMoving() const noexcept;
	bool isMovingLeft() const noexcept;
	bool isMovingRight() const noexcept;

	bool isJumping() const noexcept;

	bool isAreaBoundsVisible() const noexcept;

	bool isContainsPoint(const FloatPoint& point) const noexcept;
	bool isDestroyed() const noexcept;

private:
	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;
	void receiveEventsSelf(const sf::Event& event) noexcept override;

	void drawAreaBounds(sf::RenderTarget& target) const noexcept;

	GameObjectIdentifiers mIdentifier;

	Sprite* mSprite;

	std::unique_ptr<GameObjectState> mState;

	FloatPoint mAcceleration;
	FloatPoint mVelocity;
	FloatPoint mMaxVelocity;

	Directions mDirection;

	sf::Color mAreaBoundsColor;

	bool mAreaBoundsVisible;
	bool mMouseOver;
};
