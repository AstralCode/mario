#pragma once

#include "EnemyBuilder.hpp"

class ResourceContainer;
class SpritesetContainer;
class EntityContainer;

class GoombaBuilder final : public EnemyBuilder
{
public:
	GoombaBuilder(const ResourceContainer& resources, const SpritesetContainer& spritesets) noexcept;

	void create(EntityContainer& enemies) noexcept;

	void buildTexture() noexcept override;
	void buildComponents() noexcept override;

	void buildMoveAnimation() noexcept override;
	void buildLoseAnimation() noexcept override;

	void buildState() noexcept override;

	Enemy* getEnemy() const noexcept;

private:
	const ResourceContainer& mResources;
	const SpritesetContainer& mSpritesets;

	Enemy* mEnemy;
};

