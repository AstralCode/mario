#pragma once

#include "GameObjectState.hpp"
#include "Spriteset.hpp"
#include "SpritesetRegions.hpp"

class MarioJumpState final : public GameObjectState
{
public:
	MarioJumpState(const Spriteset<MarioSpritesetRegions>& spriteset) noexcept;

	void onSet(GameObject& object) noexcept override;
	void update(GameObject& object, const sf::Time& fixedFrameTime) noexcept override;

	void onTileTopCollision(GameObject& object, const Tile& tile) noexcept override;

	void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept override;

	bool isJumping() const noexcept override;

private:
	const Spriteset<MarioSpritesetRegions>& mSpriteset;
};
