#pragma once

#include "GameObjectState.hpp"

class SpritesetRegion;

class CreatureFallState final : public GameObjectState
{
public:
	CreatureFallState(const SpritesetRegion& moveSpritesetRegion) noexcept;

	void onSet(GameObject& object) noexcept override;
	void update(GameObject& object, const sf::Time& dt) noexcept override;

	void onTileLeftCollision(GameObject& object, const Tile& tile) noexcept override;
	void onTileRightCollision(GameObject& object, const Tile& tile) noexcept override;
	void onTileTopCollision(GameObject& object, const Tile& tile) noexcept override;

	void onObjectCollision(GameObject& objectA, GameObject& objectB) noexcept override;

private:
	const SpritesetRegion& mMoveSpritesetRegion;
};
