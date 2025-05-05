#pragma once

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
	template <typename ty>
	struct unique_ptr
	{
	flx_private:
		ty* owned_ptr;

	flx_public:
		explicit unique_ptr(ty* ptr = nullptr) : owned_ptr(ptr)
		{
		}
		~unique_ptr()
		{
			delete owned_ptr;
		}
		unique_ptr(unique_ptr&& other) noexcept : owned_ptr(other.owned_ptr)
		{
			other.owned_ptr = nullptr;
		}
		unique_ptr& operator=(unique_ptr&& other) noexcept
		{
			if (this != &other)
			{
				delete owned_ptr;
				owned_ptr = other.owned_ptr;
				other.owned_ptr = nullptr;
			}
			return *this;
		}
		unique_ptr(const unique_ptr&) = delete;
		unique_ptr& operator=(const unique_ptr&) = delete;

		ty* get() const
		{
			return owned_ptr;
		}
		ty& operator*() const
		{
			return *owned_ptr;
		}
		ty* operator->() const
		{
			return owned_ptr;
		}
		ty& operator[](u16 pos)
		{
			return owned_ptr[pos];
		}
		ty& operator[](i32 pos)
		{
			return owned_ptr[pos];
		}
		ty& operator[](u32 pos)
		{
			return owned_ptr[pos];
		}
		ty& operator[](u64 pos)
		{
			return owned_ptr[pos];
		}
		ty* release()
		{
			ty* ptr = owned_ptr;
			owned_ptr = nullptr;
			return ptr;
		}
		void reset(ty* ptr = nullptr)
		{
			if (owned_ptr)
			{
				delete owned_ptr;
			}
			owned_ptr = ptr;
		}

		template <typename ty, typename... Args>
		flx::unique_ptr<ty> make_unique(Args... args)
		{
			return flx::unique_ptr<ty>(new ty(args...));
		}
	};
} // namespace flx
