#ifndef HARPOCRATES_H
#define HARPOCRATES_H

#include <string>
#include <cstdint>
#include <vector>

namespace harpocrates
{
    // Standard AES key size for CBC std is 128bit
    const size_t HARPOCRATES_AES_KEY_SIZE = 16;

    /* Standard AES key size for CBC std is 128bit
     * The initialization vector (IV) is the same size 
     * The cleartext is padded to a multiple of this.
     */
    const size_t HARPOCRATES_AES_BLOCK_SIZE = 16;

    void encrypt(const std::string& key, std::vector<uint8_t>& data, bool random_iv=false);
    void decrypt(const std::string& key, std::vector<uint8_t>& data, bool random_iv=false);
}
#endif /* HARPOCRATES_H */ 

