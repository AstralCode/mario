#pragma once

#include "GameObjectState.hpp"
#include "Spriteset.hpp"
#include "SpritesetRegions.hpp"

class SpritesetRegion;

class MarioFallState final : public GameObjectState
{
public:
	MarioFallState(const Spriteset<MarioSpritesetRegions>& spriteset) noexcept;

	void onSet(GameObject& object) noexcept override;
	void update(GameObject& object, const sf::Time& dt) noexcept override;

	void onTileTopCollision(GameObject& object, const Tile& tile) noexcept override;

	void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept override;

	bool isFalling() const noexcept override;
	bool isJumping() const noexcept override;

private:
	const Spriteset<MarioSpritesetRegions>& mSpriteset;
};
