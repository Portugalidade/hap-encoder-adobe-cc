#pragma once

#include <string>
#include <type_traits>

namespace SDKStringConvert {
    using uint16_based_type = uint16_t;
	std::wstring to_wstring(const std::string& str);
	std::wstring to_wstring(const uint16_based_type* str);
    // For Windows where wchar_t is 16 bits wide
    template <class T, typename std::enable_if<sizeof(T) == sizeof(uint16_based_type) && std::is_same<T, wchar_t>::value, T>::type=0>
	std::wstring to_wstring(const T* str) {
        return std::wstring(str);
    }
	std::string to_string(const std::wstring& fromUTF16);
	std::string to_string(const uint16_based_type* str);
    // For Windows where wchar_t is 16 bits wide
    template <class T, typename std::enable_if<sizeof(T) == sizeof(uint16_based_type) && std::is_same<T, wchar_t>::value, T>::type=0>
	std::string to_string(const T* str) {
        return to_string(std::wstring(str));
    }

#ifdef _WIN32
	void to_buffer(const std::string& str, wchar_t* dst, size_t dstSizeInChars);
#else
	void to_buffer(const std::string& str, uint16_based_type* dst, size_t dstSizeInChars);
#endif
	template <class T, size_t size>
	void to_buffer(const std::string& str, T(&dst)[size]) {
		to_buffer(str, dst, size);
	}

#ifdef _WIN32
	void to_buffer(const std::wstring& str, wchar_t* dst, size_t dstSizeInChars);
#else
	void to_buffer(const std::wstring& str, uint16_based_type* dst, size_t dstSizeInChars);
#endif
	template <class T, size_t size>
	void to_buffer(const std::wstring& str, T(&dst)[size]) {
		to_buffer(str, dst, size);
	}

	void to_buffer(const std::string& str, char* dst, size_t dstSizeInChars);
	template <size_t size>
	void to_buffer(const std::string& str, char(&dst)[size]) {
		to_buffer(str, dst, size);
	}
}
