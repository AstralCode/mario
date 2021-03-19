#pragma once

#include "GameObjectState.hpp"
#include "Animation.hpp"

class CreatureMoveState final : public GameObjectState
{
public:
	CreatureMoveState(const SpritesetRegion& moveSpritesetRegion) noexcept;

	void onSet(GameObject& object) noexcept override;
	void update(GameObject& object, const sf::Time& dt) noexcept override;

	void onTileLeftCollision(GameObject& object, const Tile& tile) noexcept override;
	void onTileRightCollision(GameObject& object, const Tile& tile) noexcept override;

	void onObjectCollision(GameObject& objectA, GameObject& objectB) noexcept override;
	void onFalling(GameObject& object) noexcept override;

	bool isJumping() const noexcept override;
	bool isFalling() const noexcept override;

private:
	Animation mMoveAnimation;
};
