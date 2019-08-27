#ifndef HARPOCRATES_H
#define HARPOCRATES_H

#include <string>
#include <cstdint>
#include <vector>

namespace harpocrates
{
    std::vector<uint8_t> size_to_vector(size_t size);
    size_t vector_to_size(std::vector<uint8_t> size);
        
    void encrypt(const std::string& key, std::vector<uint8_t>& data, bool random_iv=false);
    void decrypt(const std::string& key, std::vector<uint8_t>& data, bool random_iv=false);
}
#endif /* HARPOCRATES_H */ 

