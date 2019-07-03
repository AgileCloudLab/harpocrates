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

        std::ostringstream oss;

        if (!data.empty())
        {
            std::copy(data.begin(), data.end(), std::ostream_iterator<uint8_t>(oss, ""));
        }

        return oss.str();
    }

    
    std::vector<uint8_t> string_to_vector(const std::string& data)
    {
        return std::vector<uint8_t>(data.begin(), data.end()); 
    }
}
}
}
