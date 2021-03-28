#pragma once

#include "HeroBuilder.hpp"

class HeroBuilderDirector final
{
public:
	void buildHero(HeroBuilder& builder) noexcept;
};
