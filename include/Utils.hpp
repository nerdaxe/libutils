#ifndef UTILS_HPP
#define UTILS_HPP
#include <type_traits>
#include <etl/vector.h>


namespace libutils {

	bool ToLittleEndian(void* buffer, uint16_t length);
	bool ToLittleEndian(const void* buffer, uint16_t length, void *output, uint16_t max_length);

	bool HexdecimalToBinary(char *str, uint16_t length);
	bool HexdecimalToBinary(const char* str, uint16_t length, uint8_t*output, uint16_t max_length);

	bool BinaryToHexdecimal(uint8_t *output, uint16_t length, const uint8_t* input, uint16_t input_length);
	bool BinaryToHexdecimal(uint8_t* output, uint16_t length, const etl::ivector<uint8_t>& vec);


	bool HexdecimalToBinary(const char* str, uint16_t length, etl::ivector<uint8_t>& vec);
	bool HexdecimalToBinaryAppend(const char* str, uint16_t length, etl::ivector<uint8_t>& vec);
}

#endif // !UTILS_HPP
