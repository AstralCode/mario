#pragma once

#include "SFML/Graphics/Color.hpp"

#include "Constants.hpp"
#include "GraphicsItem.hpp"
#include "Tile.hpp"

class Sprite;

class Entity : public GraphicsItem
{
public:
	enum class Direction
	{
		Left, Right
	};

	virtual ~Entity() = default;

	void setTexture(const sf::Texture& texture) noexcept;
	void setSpriteArea(const IntArea& area) noexcept;

	void setBoundsColor(const sf::Color& color) noexcept;
	void setBoundsVisible(const bool visible) noexcept;

	void setDirection(const Direction direction) noexcept;

	void setAccelerationX(const float value) noexcept;
	void setAccelerationY(const float value) noexcept;

	void setVelocityX(const float value) noexcept;
	void setVelocityY(const float value) noexcept;

	void destroy() noexcept;

	virtual void update(const sf::Time& dt) noexcept = 0;

	virtual void tileCollision(const Tile& tile, const Tile::Sides side) noexcept = 0;
	virtual void entityCollision(Entity& entity) noexcept = 0;

	virtual void falling() noexcept = 0;

	const Direction& getDirection() const noexcept;

	const FloatPoint& getAcceleration() const noexcept;
	const FloatPoint& getVelocity() const noexcept;

	FloatArea getLocalArea() const noexcept override;

	bool hasDirection(const Direction direction) const noexcept;

	bool isBoundsVisible() const noexcept;

	virtual bool isJumping() const noexcept = 0;
	virtual bool isFalling() const noexcept = 0;

	bool isDestroyed() const noexcept;

private:
	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;
	void drawAreaBounds(sf::RenderTarget& target) const noexcept;

	Sprite* mSprite{addItem<Sprite>()};

	FloatPoint mAcceleration;
	FloatPoint mVelocity;

	Direction mDirection{Direction::Right};

	sf::Color mBoundsColor{sf::Color::Transparent};

	bool mIsBoundsVisible{false};
	bool mIsDestroyed{false};
};
