#ifndef SPDLOG_HPP
#define SPDLOG_HPP
#include <etl/string_view.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

std::ostream& operator<<(std::ostream& os, const etl::string_view& c)
{
	std::string str(c.data(), c.length());
	return os << str;
}
template <> struct fmt::formatter<etl::string_view> : fmt::ostream_formatter {};

#endif