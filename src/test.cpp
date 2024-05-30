#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include "URI.tpp"


using namespace libutils;

std::ostream& operator<<(std::ostream& os, const etl::string_view& c)
{
	std::string str(c.data(), c.length());
	return os << str;
}
template <> struct fmt::formatter<etl::string_view> : fmt::ostream_formatter {};

int main(int argc, char* argv[]) {
	spdlog::set_level(spdlog::level::debug);


	SPDLOG_DEBUG("TEST URI:");
	{
		URI<false> url("stratum+tcp://127.0.0.1:3333");

		SPDLOG_DEBUG("URI:");
		SPDLOG_DEBUG("Scheme: {}", url.Scheme());
		SPDLOG_DEBUG("Username: {}", url.Username());
		SPDLOG_DEBUG("Password: {}", url.Password());
		SPDLOG_DEBUG("Url: {}", url.Url());
		SPDLOG_DEBUG("Port: {}", url.Port());
		SPDLOG_DEBUG("Path: {}", url.Path());
		SPDLOG_DEBUG("Valid: {}", url.Valid());
	}
	{
		URI<false> url("stratum+tcp://username:password@127.0.0.1:3333");

		SPDLOG_DEBUG("URI:");
		SPDLOG_DEBUG("Scheme: {}", url.Scheme());
		SPDLOG_DEBUG("Username: {}", url.Username());
		SPDLOG_DEBUG("Password: {}", url.Password());
		SPDLOG_DEBUG("Url: {}", url.Url());
		SPDLOG_DEBUG("Port: {}", url.Port());
		SPDLOG_DEBUG("Path: {}", url.Path());
		SPDLOG_DEBUG("Valid: {}", url.Valid());
	}
	{
		URI<false> url("stratum+tcp://username:password@127.0.0.1:3333/path");

		SPDLOG_DEBUG("URI:");
		SPDLOG_DEBUG("Scheme: {}", url.Scheme());
		SPDLOG_DEBUG("Username: {}", url.Username());
		SPDLOG_DEBUG("Password: {}", url.Password());
		SPDLOG_DEBUG("Url: {}", url.Url());
		SPDLOG_DEBUG("Port: {}", url.Port());
		SPDLOG_DEBUG("Path: {}", url.Path());
		SPDLOG_DEBUG("Valid: {}", url.Valid());
	} 
	{
		URI<false> url("stratum+tcp://username:password@127.0.0.1/path");

		SPDLOG_DEBUG("URI:");
		SPDLOG_DEBUG("Scheme: {}", url.Scheme());
		SPDLOG_DEBUG("Username: {}", url.Username());
		SPDLOG_DEBUG("Password: {}", url.Password());
		SPDLOG_DEBUG("Url: {}", url.Url());
		SPDLOG_DEBUG("Port: {}", url.Port());
		SPDLOG_DEBUG("Path: {}", url.Path());
		SPDLOG_DEBUG("Valid: {}", url.Valid());
	}
	{
		URI<false> url("stratum+tcp://127.0.0.1/path");

		SPDLOG_DEBUG("URI:");
		SPDLOG_DEBUG("Scheme: {}", url.Scheme());
		SPDLOG_DEBUG("Username: {}", url.Username());
		SPDLOG_DEBUG("Password: {}", url.Password());
		SPDLOG_DEBUG("Url: {}", url.Url());
		SPDLOG_DEBUG("Port: {}", url.Port());
		SPDLOG_DEBUG("Path: {}", url.Path());
		SPDLOG_DEBUG("Valid: {}", url.Valid());
	}


	return 0;
}