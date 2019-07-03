#ifndef HARPOCRATES_H
#define HARPOCRATES_H

#include <string>
#include <cstdint>
#include <vector>

namespace harpocrates
{
    void encrypt(std::vector<uint8_t>& data, const std::string& key);
    void decrypt(std::vector<uint8_t>& data, const std::string& key);     
}
#endif /* HARPOCRATES_H */ 

