#pragma once

#include "GameObjectState.hpp"
#include "Spriteset.hpp"
#include "SpritesetRegions.hpp"

class MarioStandState final : public GameObjectState
{
public:
	MarioStandState(const Spriteset<MarioSpritesetRegions>& spriteset) noexcept;

	void onSet(GameObject& object) noexcept override;
	void update(GameObject& object, const sf::Time& fixedFrameTime) noexcept override;

	void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept override;

private:
	const Spriteset<MarioSpritesetRegions>& mSpriteset;
};
