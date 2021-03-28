#pragma once

class Hero;

class HeroBuilder
{
public:
	virtual ~HeroBuilder() = default;

	virtual void buildTexture() noexcept = 0;
	virtual void buildComponents() noexcept = 0;

	virtual void buildStandAnimation() noexcept = 0;
	virtual void buildMoveAnimation() noexcept = 0;
	virtual void buildJumpAnimation() noexcept = 0;
	virtual void buildSlideAnimation() noexcept = 0;
	virtual void buildLoseAnimation() noexcept = 0;

	virtual void buildStates() noexcept = 0;
};
