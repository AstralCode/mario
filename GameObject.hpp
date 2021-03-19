#pragma once

#include "SFML/Graphics/Color.hpp"

#include "Constants.hpp"
#include "GraphicsItem.hpp"
#include "GameObjectIdentifiers.hpp"
#include "GameObjectState.hpp"
#include "GameObjectDirections.hpp"

class Sprite;

class GameObject final : public GraphicsItem
{
public:
	GameObject(const GameObjectIdentifiers identifier) noexcept;

	template <typename TState, typename... TArgs>
	void setState(TArgs&&... args) noexcept;

	void setTexture(const sf::Texture& texture) noexcept;
	void setSpriteArea(const IntArea& area) noexcept;
	
	void setAreaBoundsVisible(const bool visible) noexcept;
	void setAreaBoundsColor(const sf::Color& color) noexcept;

	void setAccelerationX(const float value) noexcept;
	void setAccelerationY(const float value) noexcept;

	void setVelocityX(const float value) noexcept;
	void setVelocityY(const float value) noexcept;

	void setMaxVelocityX(const float value) noexcept;
	void setMaxVelocityY(const float value) noexcept;

	void setDirection(const GameObjectDirections direction) noexcept;

	void destroy() noexcept;

	void onTileTopCollision(const Tile& tile) noexcept;
	void onTileBottomCollision(const Tile& tile) noexcept;
	void onTileLeftCollision(const Tile& tile) noexcept;
	void onTileRightCollision(const Tile& tile) noexcept;

	void onObjectCollision(GameObject& object) noexcept;

	virtual void onFalling() noexcept;

	void update(const sf::Time& dt) noexcept;

	GameObjectIdentifiers getIdentifier() const noexcept;

	const FloatPoint& getAcceleration() const noexcept;
	const FloatPoint& getMaxVelocity() const noexcept;
	const FloatPoint& getVelocity() const noexcept;

	FloatArea getLocalArea() const noexcept override;

	GameObjectDirections getDirection() const noexcept;

	bool hasDirection(const GameObjectDirections direction) const noexcept;
	bool hasIdentifier(const GameObjectIdentifiers identifier) const noexcept;

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

	GameObjectDirections mDirection;

	sf::Color mAreaBoundsColor;

	bool mAreaBoundsVisible;
	bool mMouseOver;
};

template <typename TState, typename ...TArgs>
inline void GameObject::setState(TArgs&& ...args) noexcept
{
	mState = std::move(std::make_unique<TState>(std::forward<TArgs&&>(args)...));
	mState->onSet(*this);
}
