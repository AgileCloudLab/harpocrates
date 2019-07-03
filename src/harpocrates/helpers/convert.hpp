#ifndef HARPOCRATES_CONVERT_H
#define HARPOCRATES_CONVERT_H
#include <string>
#include <cstdint>

#include <vector>

namespace harpocrates
{
namespace helpers
{
namespace convert
{
    std::string vector_to_string(const std::vector<uint8_t>& data);
    std::vector<uint8_t> string_to_vector(const std::string& data);
}
}
}

#endif /*HARPOCRATES_CONVERT_H*/
