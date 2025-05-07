#ifndef FLX_TYPES_HPP
#define FLX_TYPES_HPP

#include <cassert>

#ifdef FLX_ALL_MEMBERS_ARE_PUBLIC
#define flx_public public
#define flx_protected public
#define flx_private public
#else
#define flx_public public
#define flx_protected protected
#define flx_private private
#endif // FLX_ALL_MEMBERS_ARE_PUBLIC

namespace flx
{
	using u0	=			void;
	using u00	=			void;

	using b8	=			bool;
	using b08	=			bool;

	using i8	= signed	char;
	using i08	= signed	char;
	using i16	= signed	short;
	using i32	= signed	int;
	using i64	= signed	long long;

	using u8	= unsigned	char;
	using u08	= unsigned	char;
	using u16	= unsigned	short;
	using u32	= unsigned	int;
	using u64	= unsigned	long long;

	using f32	=			float;
	using f64	=			double;
	using f80	=			long double;

	/// <summary>
	/// Same as std::unique_ptr, but with less overhead.
	/// </summary>
	template<typename ty>
	struct unique_ptr
	{
	flx_private:
		ty* owned_ptr = nullptr;

	flx_public:
		explicit constexpr unique_ptr(ty* = nullptr) noexcept;
		constexpr ~unique_ptr() noexcept;
		constexpr unique_ptr(const unique_ptr&) = delete;
		constexpr unique_ptr(unique_ptr&&) noexcept;

		constexpr unique_ptr& operator=(const unique_ptr&) = delete;
		constexpr unique_ptr& operator=(unique_ptr&&) noexcept;

		explicit constexpr operator bool() const noexcept;

		constexpr ty* get() const noexcept;
		constexpr ty& operator*() const noexcept;
		constexpr ty* operator->() const noexcept;

		constexpr ty& operator[](u64);
		constexpr const ty& operator[](u64) const;

		[[nodiscard]] constexpr ty* release() noexcept;
		constexpr void reset(ty* = nullptr) noexcept;

	};

	template<typename ty, typename... Args>
	flx::unique_ptr<ty> make_unique(Args... args);

	template<typename ty>
	constexpr ty&& move(ty& obj) noexcept;
} // namespace flx

namespace flx
{
	template<typename ty>
	inline constexpr unique_ptr<ty>::unique_ptr(ty* ptr) noexcept : owned_ptr(ptr)
	{
	}

	template<typename ty>
	inline constexpr unique_ptr<ty>::unique_ptr(unique_ptr&& other) noexcept : owned_ptr(other.owned_ptr)
	{
		other.owned_ptr = nullptr;
	}

	template<typename ty>
	inline constexpr unique_ptr<ty>::~unique_ptr() noexcept
	{
		delete owned_ptr;
	}

	template<typename ty>
	inline constexpr unique_ptr<ty>& unique_ptr<ty>::operator=(unique_ptr<ty>&& other) noexcept
	{
		assert(this != &other && "flx_types::unique_ptr::operator= assigning to self is forbidden.");

		delete owned_ptr;
		owned_ptr = other.owned_ptr;
		other.owned_ptr = nullptr;
		return *this;
	}

	template<typename ty>
	inline constexpr unique_ptr<ty>::operator bool() const noexcept
	{
		return owned_ptr != nullptr;
	}

	template<typename ty>
	inline constexpr ty* unique_ptr<ty>::get() const noexcept
	{
		return owned_ptr;
	}

	template<typename ty>
	inline constexpr ty& unique_ptr<ty>::operator*() const noexcept
	{
		return *owned_ptr;
	}

	template<typename ty>
	inline constexpr ty* unique_ptr<ty>::operator->() const noexcept
	{
		return owned_ptr;
	}

	template<typename ty>
	inline constexpr ty& unique_ptr<ty>::operator[](u64 pos)
	{
		return owned_ptr[pos];
	}

	template<typename ty>
	inline constexpr const ty& unique_ptr<ty>::operator[](u64 pos) const
	{
		return owned_ptr[pos];
	}

	template<typename ty>
	[[nodiscard]] inline constexpr ty* unique_ptr<ty>::release() noexcept
	{
		ty* ptr = owned_ptr;
		owned_ptr = nullptr;
		return ptr;
	}

	template<typename ty>
	inline constexpr void unique_ptr<ty>::reset(ty* ptr) noexcept
	{
		delete owned_ptr;
		owned_ptr = ptr;
	}

	template<typename ty, typename... Args>
	flx::unique_ptr<ty> make_unique(Args... args)
	{
		return flx::unique_ptr<ty>(new ty(args...));
	}

	template<typename ty>
	constexpr ty&& move(ty& obj) noexcept
	{
		return static_cast<ty&&>(obj);
	}
} // namespace flx

#endif // !FLX_TYPES_HPP