#pragma once

#include "GameObjectState.hpp"
#include "GameObjectDirections.hpp"
#include "Spriteset.hpp"
#include "SpritesetRegions.hpp"
#include "Animation.hpp"

class MarioMoveState final : public GameObjectState
{
public:
	MarioMoveState(const Spriteset<MarioSpritesetRegions>& spriteset) noexcept;

	void onSet(GameObject& object) noexcept override;
	void update(GameObject& object, const sf::Time& fixedFrameTime) noexcept override;

	void setDirection(GameObject& object, const GameObjectDirections direction) noexcept;

	void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept override;

private:
	const Spriteset<MarioSpritesetRegions>& mSpriteset;

	Animation mMoveAnimation;
};
