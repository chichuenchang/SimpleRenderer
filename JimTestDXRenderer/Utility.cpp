#include "Utility.h"
#include <limits>
#include <iostream>

UINT Utility::convert_sizet_to_uint(size_t size)
{
	if (size > static_cast<size_t>((std::numeric_limits<unsigned int>::max)())) {
		std::cout << "[ERROR] size_t size greater than UINT to hold" << std::endl;
		return 0;
	}
	else {
		UINT uint_size = static_cast<UINT>(size);
		return uint_size;
	}
}
