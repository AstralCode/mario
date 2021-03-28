#pragma once

#include "EnemyBuilder.hpp"

class EnemyBuilderDirector final
{
public:
	void buildEnemy(EnemyBuilder& builder) noexcept;
};
