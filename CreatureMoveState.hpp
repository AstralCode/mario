#pragma once

#include "GameObjectState.hpp"
#include "Spriteset.hpp"
#include "SpritesetRegions.hpp"

class CreatureMoveState final : public GameObjectState
{
public:
	CreatureMoveState(const Spriteset<Enemy>& spriteset) noexcept;

	void onSet(GameObject& object) noexcept override;
	void update(GameObject& object, const sf::Time& fixedFrameTime) noexcept override;

	void onKeyPressed(GameObject& object, const sf::Event::KeyEvent& keyEvent) noexcept override;

private:
	const Spriteset<MarioSpritesetRegions>& mSpriteset;
};
