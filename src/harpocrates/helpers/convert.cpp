#include "convert.hpp"

#include <sstream>

#include <algorithm>
#include <iterator>


namespace harpocrates
{
namespace helpers
{
namespace convert
{
    std::string vector_to_string(const std::vector<uint8_t>& data)
    {
        std::string res((char*) data.data(), data.size());
        return res; 
    }

    
    std::vector<uint8_t> string_to_vector(const std::string& data)
    {
        return std::vector<uint8_t>(data.begin(), data.end()); 
    }
}
}
}
