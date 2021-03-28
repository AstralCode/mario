#pragma once

#include "ItemBuilder.hpp"

class ItemBuilderDirector final
{
public:
	void buildItem(ItemBuilder& builder) noexcept;
};
