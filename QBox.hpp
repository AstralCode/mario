#pragma once

#include "EntityStateMachine.hpp"
#include "Animation.hpp"

class QBox final : public Entity
{
public:
	QBox(World& world) noexcept;

	template <typename TState>
	void setState();

	void playShineAnimation() noexcept;
	void updateShineAnimation(const sf::Time& dt) noexcept;

	void update(const sf::Time& dt) noexcept override;

	void collision(const Tile& tile, const CollisionSideType side) noexcept override;
	void collision(const Entity& collider, const CollisionSideType side) noexcept override;

	void falling() noexcept override;

private:
	Animation mShineAnimation;

	EntityStateMachine<QBox> mStates;
};

template <typename TState>
void QBox::setState()
{
	mStates.setState<TState>(*this);
}
