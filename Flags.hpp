#pragma once

#include <bitset>
#include <type_traits>
#include <initializer_list>

template <typename TEnum, size_t TEnumSize>
class Flags
{
public:
	Flags() = default;
	Flags(std::initializer_list<TEnum> flags) noexcept;

	void set(const TEnum flag) noexcept;
	void set(std::initializer_list<TEnum> flags) noexcept;
	void set(const Flags& flags) noexcept;

	void unset(const TEnum flag) noexcept;
	void unset(std::initializer_list<TEnum> flags) noexcept;
	void unset(const Flags& flags) noexcept;

	void reset() noexcept;

	bool isSet(const TEnum flag) const noexcept;

	bool isSetAnyOf(const Flags& flags) const noexcept;
	bool isSetAllOf(const Flags& flags) const noexcept;
	bool isSetNoneOf(const Flags& flags) const noexcept;

	bool isEmpty() const noexcept;

private:
	std::bitset<TEnumSize> mFlags;
};

template <typename TEnum, size_t TEnumSize>
inline Flags<TEnum, TEnumSize>::Flags(std::initializer_list<TEnum> flags) noexcept
{
	set(flags);
}

template <typename TEnum, size_t TEnumSize>
inline void Flags<TEnum, TEnumSize>::set(const TEnum flag) noexcept
{
	mFlags.set(static_cast<int>(flag));
}

template <typename TEnum, size_t TEnumSize>
inline void Flags<TEnum, TEnumSize>::set(std::initializer_list<TEnum> flags) noexcept
{
	for (auto flag : flags)
	{
		set(flag);
	}
}

template <typename TEnum, size_t TEnumSize>
inline void Flags<TEnum, TEnumSize>::set(const Flags& flags) noexcept
{
	mFlags |= flags.mFlags;
}

template <typename TEnum, size_t TEnumSize>
inline void Flags<TEnum, TEnumSize>::unset(const TEnum flag) noexcept
{
	mFlags.set(static_cast<int>(flag), false);
}

template <typename TEnum, size_t TEnumSize>
inline void Flags<TEnum, TEnumSize>::unset(std::initializer_list<TEnum> flags) noexcept
{
	for (auto flag : flags)
	{
		unset(flag);
	}
}

template <typename TEnum, size_t TEnumSize>
inline void Flags<TEnum, TEnumSize>::unset(const Flags& flags) noexcept
{
	mFlags |= ~flags.mFlags;
}

template <typename TEnum, size_t TEnumSize>
inline void Flags<TEnum, TEnumSize>::reset() noexcept
{
	mFlags.reset();
}

template <typename TEnum, size_t TEnumSize>
inline bool Flags<TEnum, TEnumSize>::isSet(const TEnum flag) const noexcept
{
	return mFlags.test(static_cast<int>(flag));
}

template <typename TEnum, size_t TEnumSize>
inline bool Flags<TEnum, TEnumSize>::isSetAnyOf(const Flags& flags) const noexcept
{
	return (mFlags & flags.mFlags) > 0;
}

template <typename TEnum, size_t TEnumSize>
inline bool Flags<TEnum, TEnumSize>::isSetAllOf(const Flags& flags) const noexcept
{
	return (mFlags & flags.mFlags) == flags.mFlags;
}

template <typename TEnum, size_t TEnumSize>
inline bool Flags<TEnum, TEnumSize>::isSetNoneOf(const Flags& flags) const noexcept
{
	return !isSetAnyOf(flags);
}

template <typename TEnum, size_t TEnumSize>
inline bool Flags<TEnum, TEnumSize>::isEmpty() const noexcept
{
	return mFlags.count() == 0u;
}
