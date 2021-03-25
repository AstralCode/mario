#include "TypeIdGenerator.hpp"

TypeId::Type TypeIdGenerator::mCurrentId{0};

TypeId::TypeId() noexcept :
    mId{0}
{

};

TypeId::TypeId(const Type id) noexcept :
    mId{id}
{

};

bool operator<(const TypeId& left, const TypeId& right) noexcept
{
    return left.mId < right.mId;
};
