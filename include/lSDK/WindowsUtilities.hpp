#ifndef lSDK_WindowsUtilities_HeaderPlusPlus
#define lSDK_WindowsUtilities_HeaderPlusPlus

#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>

#include "lSDK/UnicodeUtilities.hpp"

#include <Windows.h>

namespace lSDK
{
	template<typename Handle, typename R, typename Arg, R (WINAPI &Func)(Arg)>
	struct HandleDeleter final
	{
		using pointer = Handle;

		void operator()(Handle handle) const noexcept
		{
			Func(reinterpret_cast<Arg>(handle));
		}
	};
	template<typename Handle, typename R, typename Arg, R (WINAPI &Func)(Arg)>
	using unique_handle = std::unique_ptr<Handle, HandleDeleter<Handle, R, Arg, Func>>;

	inline auto get_windows_error_message(DWORD const error)
	-> string_t
	{
		TCHAR *buffer = nullptr;
		SetLastError(ERROR_SUCCESS);
		auto const length = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, 0, reinterpret_cast<LPTSTR>(&buffer), 0, NULL);
		DWORD const format_message_error = GetLastError();
		unique_handle<TCHAR *, HLOCAL, HLOCAL, LocalFree> buffer_freer {buffer};
		if(format_message_error != ERROR_SUCCESS)
		{
			return TSL("(error ") + string_t_from_numeric(format_message_error) + TSL(" while generating error message for error code ") + string_t_from_numeric(error) + TSL(")");
		}
		if(length <= 0 || !buffer)
		{
			return TSL("(unknown error while generating error message for error code ") + string_t_from_numeric(error) + TSL(")");
		}
		return {buffer, static_cast<std::size_t>(length)};
	}

	struct WindowsError final
	: std::runtime_error
	{
		DWORD error;
		WindowsError(DWORD const error, string_view_t const &message)
		: std::runtime_error{narrow_from(string_t_from(message) + TSL(": ") + string_t_from_numeric(error) + TSL("\r\n") + get_windows_error_message(error))}
		, error{error}
		{
		}
	};

	template<typename R, typename... Args>
	auto call_winapi_any(string_view_t const &fail_message, R (WINAPI &func)(Args ...), std::common_type_t<Args>... args)
	-> R
	{
		DWORD error = ERROR_SUCCESS;
		SetLastError(ERROR_SUCCESS);
		if constexpr(!std::is_void_v<R>)
		{
			auto r = func(args...);
			error = GetLastError();
			if(error == ERROR_SUCCESS)
			{
				return r;
			}
		}
		else if constexpr(true)
		{
			func(args...);
			error = GetLastError();
			if(error == ERROR_SUCCESS)
			{
				return;
			}
		}
		throw WindowsError{error, fail_message};
	}
	template<typename R, typename... Args>
	void call_winapi_zero(string_view_t const &fail_message, R (WINAPI &func)(Args ...), std::common_type_t<Args>... args)
	{
		if(call_winapi_any<R, Args...>(fail_message, func, args...) != 0)
		{
			throw std::runtime_error{narrow_from(string_t_from(fail_message)+TSL(": expected return value of 0, but return value was nonzero and GetLastError() returned ERROR_SUCCESS"))};
		}
	}
	template<typename R, typename... Args>
	auto call_winapi_nonzero(string_view_t const &fail_message, R (WINAPI &func)(Args ...), std::common_type_t<Args>... args)
	-> R
	{
		if(R r = call_winapi_any<R, Args...>(fail_message, func, args...); r != 0)
		{
			return r;
		}
		throw std::runtime_error{narrow_from(string_t_from(fail_message)+TSL(": expected nonzero return value, but return value was 0 and GetLastError() returned ERROR_SUCCESS"))};
	}
	template<typename R, typename... Args>
	auto call_winapi_nonnegative(string_view_t const &fail_message, R (WINAPI &func)(Args ...), std::common_type_t<Args>... args)
	-> std::make_unsigned_t<R>
	{
		if(R r = call_winapi_any<R, Args...>(fail_message, func, args...); r >= 0)
		{
			return static_cast<std::make_unsigned_t<R>>(r);
		}
		throw std::runtime_error{narrow_from(string_t_from(fail_message)+TSL(": expected nonnegative return value, but return value was negative and GetLastError() returned ERROR_SUCCESS"))};
	}
	template<typename R, typename... Args>
	auto call_winapi_positive(string_view_t const &fail_message, R (WINAPI &func)(Args ...), std::common_type_t<Args>... args)
	-> std::make_unsigned_t<R>
	{
		if(R r = call_winapi_any<R, Args...>(fail_message, func, args...); r > 0)
		{
			return static_cast<std::make_unsigned_t<R>>(r);
		}
		throw std::runtime_error{narrow_from(string_t_from(fail_message)+TSL(": expected positive return value, but return value was nonpositive and GetLastError() returned ERROR_SUCCESS"))};
	}
	template<typename R, typename... Args>
	auto call_winapi_notnull(string_view_t const &fail_message, R (WINAPI &func)(Args ...), std::common_type_t<Args>... args)
	-> R
	{
		if(R r = call_winapi_any<R, Args...>(fail_message, func, args...); r != NULL)
		{
			return r;
		}
		throw std::runtime_error{narrow_from(string_t_from(fail_message)+TSL(": return value was null and GetLastError() returned ERROR_SUCCESS"))};
	}

	inline auto load_resource(HINSTANCE const instance, TCHAR const *const name, TCHAR const *const type)
	-> string_view8_t
	{
		auto const find_resource_result = call_winapi_notnull(TSL("FindResource() failed"), FindResource, instance, name, type);
		auto const load_resource_result = call_winapi_notnull(TSL("LoadResource() failed"), LoadResource, instance, find_resource_result);
		auto const resource_data = call_winapi_notnull(TSL("LockResource() failed"), LockResource, load_resource_result);
		auto const resource_size = call_winapi_positive(TSL("SizeofResource() failed"), SizeofResource, instance, find_resource_result);
		return {reinterpret_cast<string_view8_t::const_pointer>(resource_data), static_cast<std::size_t>(resource_size)};
	}
}

#define LSDK_CALL_WINAPI_ANY(func, ...)         ::lSDK::call_winapi_any        (TSL(#func) TSL("(") ## #__VA_ARGS__ TSL(") failed"), func, ##__VA_ARGS__)
#define LSDK_CALL_WINAPI_ZERO(func, ...)        ::lSDK::call_winapi_zero       (TSL(#func) TSL("(") ## #__VA_ARGS__ TSL(") failed"), func, ##__VA_ARGS__)
#define LSDK_CALL_WINAPI_NONZERO(func, ...)     ::lSDK::call_winapi_nonzero    (TSL(#func) TSL("(") ## #__VA_ARGS__ TSL(") failed"), func, ##__VA_ARGS__)
#define LSDK_CALL_WINAPI_NONNEGATIVE(func, ...) ::lSDK::call_winapi_nonnegative(TSL(#func) TSL("(") ## #__VA_ARGS__ TSL(") failed"), func, ##__VA_ARGS__)
#define LSDK_CALL_WINAPI_POSITIVE(func, ...)    ::lSDK::call_winapi_positive   (TSL(#func) TSL("(") ## #__VA_ARGS__ TSL(") failed"), func, ##__VA_ARGS__)
#define LSDK_CALL_WINAPI_NOTNULL(func, ...)     ::lSDK::call_winapi_notnull    (TSL(#func) TSL("(") ## #__VA_ARGS__ TSL(") failed"), func, ##__VA_ARGS__)

#endif
