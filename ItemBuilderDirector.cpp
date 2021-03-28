#include "ItemBuilderDirector.hpp"

void ItemBuilderDirector::buildItem(ItemBuilder& builder) noexcept
{
	builder.buildTexture();
	builder.buildComponents();

	builder.buildActiveAnimation();
	builder.buildPickupAnimation();

	builder.buildState();
}
