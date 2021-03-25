#pragma once

class TypeId
{
public:
    using Type = unsigned int;

    TypeId() noexcept;
    TypeId(const Type id) noexcept;

    friend bool operator<(const TypeId& left, const TypeId& right) noexcept;

private:
    Type mId;
};

class TypeIdGenerator
{
public:
    template <typename TType>
    static TypeId next() noexcept
    {
        static TypeId generatedId{mCurrentId++};
        return generatedId;
    }

private:
    static TypeId::Type mCurrentId;
};
