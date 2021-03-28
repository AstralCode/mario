#include "HeroBuilderDirector.hpp"

void HeroBuilderDirector::buildHero(HeroBuilder& builder) noexcept
{
	builder.buildTexture();
	builder.buildComponents();

	builder.buildStandAnimation();
	builder.buildMoveAnimation();
	builder.buildJumpAnimation();
	builder.buildSlideAnimation();
	builder.buildLoseAnimation();

	builder.buildState();
}
