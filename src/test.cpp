#include <iostream>
#include "Utils.hpp"
#include "URI.hpp"
#include "Spdlog.hpp"


using namespace libutils;


int main(int argc, char* argv[]) {
	spdlog::set_level(spdlog::level::debug);


	SPDLOG_DEBUG("TEST URI:");
	{
		URI url("stratum+tcp://127.0.0.1:3333");

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
		URI url("stratum+tcp://username:password@127.0.0.1:3333");

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
		URI url("stratum+tcp://username:password@127.0.0.1:3333/path");

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
		URI url("stratum+tcp://username:password@127.0.0.1/path");

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
		URI url("stratum+tcp://127.0.0.1/path");

		SPDLOG_DEBUG("URI:");
		SPDLOG_DEBUG("Scheme: {}", url.Scheme());
		SPDLOG_DEBUG("Username: {}", url.Username());
		SPDLOG_DEBUG("Password: {}", url.Password());
		SPDLOG_DEBUG("Url: {}", url.Url());
		SPDLOG_DEBUG("Port: {}", url.Port());
		SPDLOG_DEBUG("Path: {}", url.Path());
		SPDLOG_DEBUG("Valid: {}", url.Valid());
	}

	SPDLOG_DEBUG("Hexdecimal to Binary:");
	{
		uint8_t bin[2] = { 0,0 };
		HexdecimalToBinary("fff0", strlen("fff0"), reinterpret_cast<uint8_t*>(&bin[0]), sizeof(bin));
		if (bin[0] != 0xff && bin[1] != 0xf0) {
			SPDLOG_ERROR("Error in HexdecimalToBinary f0 ff != {},{}", bin[0], bin[1]);
			return 0;
		}
		SPDLOG_DEBUG("Result 1: {},{}", bin[0],bin[1]);
		SPDLOG_DEBUG("Result 2: {},{}", strtoul("ff",nullptr,16), strtoul("f0", nullptr, 16));
	}
	{
		uint8_t bin[2] = { 0,0 };
		HexdecimalToBinary("f9f0", strlen("f9f0"), reinterpret_cast<uint8_t*>(&bin[0]), sizeof(bin));
		if (bin[0] != 0xf9 && bin[1] != 0xf0) {
			SPDLOG_ERROR("Error in HexdecimalToBinary 0xf9 0xf0 != {}, {}", bin[0], bin[1]);
			return 0;
		}
		SPDLOG_DEBUG("Result 3: {}, {}", bin[0], bin[1]);
		SPDLOG_DEBUG("Result 4: {}, {}", strtoul("f9", nullptr, 16), strtoul("f0", nullptr, 16));
	}
	{
		uint8_t bin[2] = { 0xf9, 0xf0 };
		char out[9];
		BinaryToHexdecimal(reinterpret_cast<uint8_t*>(&out[0]), sizeof(out), reinterpret_cast<uint8_t*>(&bin), sizeof(bin));
		SPDLOG_DEBUG("Result 3: {}", etl::string_view(out,4));
		SPDLOG_DEBUG("Result 4: {:x},{:x}", bin[0], bin[1]);
	}
	return 0;
}