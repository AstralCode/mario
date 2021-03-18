#pragma once

#include "GameObjectState.hpp"
#include "Animation.hpp"

class CreatureMoveState final : public GameObjectState
{
public:
	CreatureMoveState(const SpritesetRegion& moveSpritesetRegion, const SpritesetRegion& deadSpritesetRegion) noexcept;

	void onSet(GameObject& object) noexcept override;
	void update(GameObject& object, const sf::Time& fixedFrameTime) noexcept override;

	void onTileLeftCollision(GameObject& object, const Tile& tile) noexcept override;
	void onTileRightCollision(GameObject& object, const Tile& tile) noexcept override;

	void onObjectCollision(GameObject& objectA, GameObject& objectB) noexcept override;

private:
	const SpritesetRegion& mDeadSpritesetRegion;

	Animation mMoveAnimation;
};
