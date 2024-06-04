#include <spdlog/spdlog.h>
#include <cstdint>
#include <cctype>
#include "Utils.hpp"

namespace libutils {

	bool SwapEndian(void* buffer, uint16_t length) {
		if ((length % 4) == 0) {
			uint32_t* ptr = reinterpret_cast<uint32_t*>(buffer);
			const uint16_t len = length / 4;
			for (uint16_t i = 0; i < len; i++) {
				ptr[i] = _byteswap_ulong(ptr[i]);
			}
			return true;
		} else if ((length % 2) == 0) {
			uint16_t* ptr = reinterpret_cast<uint16_t*>(buffer);
			const uint16_t len = length / 2;
			for (uint16_t i = 0; i < len; i++) {
				ptr[i] = _byteswap_ushort(ptr[i]);
			}
			return true;
		}
		return false;
	}

	bool SwapEndian(const void* buffer, uint16_t length, void* output, uint16_t max_length) {
		if (max_length < length) return false;
		if ((length % 4) == 0) {
			const uint32_t* ptr = reinterpret_cast<const uint32_t*>(buffer);
			uint32_t* ptr_out = reinterpret_cast<uint32_t*>(output);
			const uint16_t len = length / 4;
			for (uint16_t i = 0; i < len; i++) {
				ptr_out[i] = _byteswap_ulong(ptr[i]);
			}
			return true;
		} else if ((length % 2) == 0) {
			const uint16_t* ptr = reinterpret_cast<const uint16_t*>(buffer);
			uint32_t* ptr_out = reinterpret_cast<uint32_t*>(output);
			const uint16_t len = length / 2;
			for (uint16_t i = 0; i < len; i++) {
				ptr_out[i] = _byteswap_ushort(ptr[i]);
			}
			return true;
		}
		return false;
	}


	bool HexdecimalToBinary(char* str, uint16_t length) {
		bool shift = false;
		uint16_t output_offset = 0;
		for (uint16_t i = 0; i < length; i++) {
			if (str[i] >= '0' && str[i] <= '9') {
				if (shift) {
					str[output_offset++] |= ((str[i] - '0') & 0xF) << 4u;
					shift = false;
				} else {
					str[output_offset] |= str[i] & 0xF;
					shift = true;
				}
			}
			else if (std::tolower(str[i]) >= 'a' && std::tolower(str[i]) <= 'f') {
				if (shift) {
					str[output_offset++] |= ((std::tolower(str[i]) - 'a') & 0xF) << 4u;
					shift = false;
				} else {
					str[output_offset] |= std::tolower(str[i]) & 0xF;
					shift = true;
				}
			}
			else return false;
		}
		return true;
	}

	bool HexdecimalToBinary(const char* str, uint16_t length, uint8_t* output, uint16_t max_length) {
		if ((length / 2) > max_length) return false;
		bool add = false;
		uint16_t output_offset = 0;
		for (uint16_t i = 0; i < length; i += 2) {
			if (str[i] >= '0' && str[i] <= '9')  output[output_offset] = (str[i] - '0') << 4;
			else if (str[i] >= 'a' && str[i] <= 'f') output[output_offset] = ((str[i] - 'a') + 10)  << 4;
			else if (str[i] >= 'A' && str[i] <= 'F') output[output_offset] = ((str[i] - 'A') + 10) << 4;
			else return false;

			if (str[i+1] >= '0' && str[i+1] <= '9') output[output_offset++] |= (str[i+1] - '0');
			else if (str[i + 1] >= 'a' && str[i + 1] <= 'f') output[output_offset++] |= ((str[i + 1] - 'a') + 10);
			else if (str[i + 1] >= 'A' && str[i + 1] <= 'F') output[output_offset++] |= ((str[i + 1] - 'A') + 10);
			else return false;
			
		}
		return true;
	}

	bool HexdecimalToBinary(const char* str, uint16_t length, etl::ivector<uint8_t>& vec) {
		if (vec.max_size() > length / 2) {
			vec.resize((length / 2) + (length % 2));
			return HexdecimalToBinary(str, length, reinterpret_cast<uint8_t*>(&vec[0]), static_cast<uint16_t>(vec.size()));
		}
		return false;
	}

	bool HexdecimalToBinaryAppend(const char* str, uint16_t length, etl::ivector<uint8_t>& vec) {
		if ((vec.max_size() - vec.size()) > length / 2) {
			size_t current_size = vec.size();
			vec.resize(vec.size() + (length / 2) + (length % 2));
			return HexdecimalToBinary(str, length, reinterpret_cast<uint8_t*>(&vec[current_size]), static_cast<uint16_t>(vec.size() - current_size));
		}
		return false;
	}


	bool BinaryToHexdecimal(uint8_t* output, uint16_t length, const etl::ivector<uint8_t>& vec) {
		return BinaryToHexdecimal(output, length, &vec[0], static_cast<uint16_t>(vec.size()));
	}

	bool BinaryToHexdecimal(uint8_t* output, uint16_t length, const uint8_t* input, uint16_t input_length) {
		if (length < (input_length * 2) + 1) return false;

		uint16_t current_out_position = 0;

		static const char hex_table[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
		
		for (int32_t i = 0; i < input_length; i++) {
			output[current_out_position++] = hex_table[(input[i] >> 4u) & 0xF]; 
			output[current_out_position++] = hex_table[input[i] & 0xF];
		}
		output[current_out_position] = '\0';

		return true;
	}

	void ReserveBytes(uint8_t* data, uint16_t length) {
		for (uint16_t i = 0; i < length / 2; i++) {
			uint8_t swap = data[i];
			data[i] = data[length - 1 - i];
			data[length - 1 - i] = swap;
		}
	}
}