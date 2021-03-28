#include "EnemyBuilderDirector.hpp"

void EnemyBuilderDirector::buildEnemy(EnemyBuilder& builder) noexcept
{
	builder.buildTexture();
	builder.buildComponents();

	builder.buildMoveAnimation();
	builder.buildLoseAnimation();

	builder.buildState();
}
