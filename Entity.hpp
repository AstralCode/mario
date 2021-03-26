#pragma once

#include "SFML/Graphics/Color.hpp"

#include "Constants.hpp"
#include "GraphicsItem.hpp"
#include "CollisionSideType.hpp"
#include "Tile.hpp"

class Sprite;

class Entity : public GraphicsItem
{
public:
	enum class TraitType
	{
		Hero,
		Enemy,
		Item,
		Movable,
		Mass,
		Transparent
	};

	enum class Directions
	{
		Left,
		Right
	};

	using Traits = Flagset<TraitType, 6u>;

	Entity() noexcept;
	virtual ~Entity() = default;

	static FloatPoint centerOrigin(const Entity& entity) noexcept;

	void setTrait(const TraitType trait) noexcept;
	void unsetTrait(const TraitType trait) noexcept;

	void setTexture(const sf::Texture& texture) noexcept;
	void setSpriteArea(const IntArea& area) noexcept;

	void setBoundsColor(const sf::Color& color) noexcept;
	void setBoundsVisible(const bool visible) noexcept;

	void setDirection(const Directions direction) noexcept;

	void setAccelerationX(const float value) noexcept;
	void setAccelerationY(const float value) noexcept;

	void setVelocityX(const float value) noexcept;
	void setVelocityY(const float value) noexcept;

	void destroy() noexcept;

	virtual void update(const sf::Time& dt) noexcept = 0;

	virtual void tileCollision(const Tile& tile, const CollisionSideType side) noexcept = 0;
	virtual void entityCollision(const Entity& entity, const CollisionSideType side) noexcept = 0;

	virtual void falling() noexcept = 0;

	bool hasTrait(const TraitType trait) const noexcept;

	const Traits& getAttrubutes() const noexcept;

	const Directions& getDirection() const noexcept;

	const FloatPoint& getAcceleration() const noexcept;
	const FloatPoint& getVelocity() const noexcept;

	FloatArea getLocalArea() const noexcept override;

	bool hasDirection(const Directions direction) const noexcept;

	bool isBoundsVisible() const noexcept;

	virtual bool isJumping() const noexcept = 0;
	virtual bool isFalling() const noexcept = 0;

	bool isDestroyed() const noexcept;

private:
	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;
	void drawAreaBounds(sf::RenderTarget& target) const noexcept;

	Traits mTraits;

	Sprite* mSprite;

	FloatPoint mAcceleration;
	FloatPoint mVelocity;

	Directions mDirection;

	sf::Color mBoundsColor;

	bool mIsBoundsVisible;
	bool mIsDestroyed;
};
