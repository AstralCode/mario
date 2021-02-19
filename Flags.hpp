#pragma once

#include <type_traits>
#include <initializer_list>

template <typename TEnum>
class Flags
{
public:
	Flags() noexcept;
	Flags(std::initializer_list<TEnum> flags) noexcept;

	void set(const TEnum flag) noexcept;
	void set(std::initializer_list<TEnum> flags) noexcept;

	void unset(const TEnum flag) noexcept;
	void unset(std::initializer_list<TEnum> flags) noexcept;

	void reset() noexcept;

	bool isSet(const TEnum flag) const noexcept;

	bool isSetAnyOf(const Flags& flags) const noexcept;
	bool isSetAllOf(const Flags& flags) const noexcept;
	bool isSetNoneOf(const Flags& flags) const noexcept;

private:
	using UnderlyingType = std::underlying_type_t<TEnum>;

	UnderlyingType mFlags;
};

template<typename TEnum>
inline Flags<TEnum>::Flags() noexcept :
	mFlags{0}
{

}

template<typename TEnum>
inline Flags<TEnum>::Flags(std::initializer_list<TEnum> flags) noexcept :
	mFlags{0}
{
	set(flags);
}

template<typename TEnum>
inline void Flags<TEnum>::set(const TEnum flag) noexcept
{
	mFlags |= static_cast<UnderlyingType>(flag);
}

template<typename TEnum>
inline void Flags<TEnum>::set(std::initializer_list<TEnum> flags) noexcept
{
	for (auto flag : flags)
	{
		set(flag);
	}
}

template<typename TEnum>
inline void Flags<TEnum>::unset(const TEnum flag) noexcept
{
	mFlags &= ~static_cast<UnderlyingType>(flag);
}

template<typename TEnum>
inline void Flags<TEnum>::unset(std::initializer_list<TEnum> flags) noexcept
{
	for (auto flag : flags)
	{
		unset(flag);
	}
}

template<typename TEnum>
inline void Flags<TEnum>::reset() noexcept
{
	mFlags = 0;
}

template<typename TEnum>
inline bool Flags<TEnum>::isSet(const TEnum flag) const noexcept
{
	return (mFlags & static_cast<UnderlyingType>(flag)) == static_cast<UnderlyingType>(flag);
}

template<typename TEnum>
inline bool Flags<TEnum>::isSetAnyOf(const Flags& flags) const noexcept
{
	return (mFlags & flags.mFlags) > 0;
}

template<typename TEnum>
inline bool Flags<TEnum>::isSetAllOf(const Flags& flags) const noexcept
{
	return (mFlags & flags.mFlags) == flags.mFlags;
}

template<typename TEnum>
inline bool Flags<TEnum>::isSetNoneOf(const Flags& flags) const noexcept
{
	return !isSetAnyOf(flags);
}
