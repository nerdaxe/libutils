#ifndef HELPER_TPP
#define HELPER_TPP

namespace libutils {
	template <typename T>
	constexpr auto type_name() -> std::string_view
	{
		constexpr auto prefix = std::string_view{ "[with T = " };
		constexpr auto suffix = std::string_view{ ";" };
		constexpr auto function = std::string_view{ __PRETTY_FUNCTION__ };

		constexpr auto start = function.find(prefix) + prefix.size();
		constexpr auto end = function.rfind(suffix);

		static_assert(start < end);

		constexpr auto result = function.substr(start, (end - start));

		return result;
	}

}

#endif