#include "hashing.hpp"
#include <openssl/sha.h>
namespace harpocrates
{
namespace hashing
{
    void hash(const std::vector<uint8_t>& data, std::vector<uint8_t>& hash, hash_type type)
    {
        switch(type)
        {
        case hash_type::SHA1:
            sha1_hash(data, hash);
            break;
        case hash_type::SHA256:
            sha256_hash(data, hash);
            break;
        case hash_type::SHA512:
            sha512_hash(data, hash);
            break;
        default:
            sha1_hash(data, hash);
            break;            
        }
    }

    void sha1_hash(const std::vector<uint8_t>& data, std::vector<uint8_t>& hash)
    {
        unsigned char digest[SHA_DIGEST_LENGTH];
        
        SHA_CTX shactx;
    
        SHA1_Init(&shactx);
        SHA1_Update(&shactx, data.data(), data.size() - 1);
        SHA1_Final(digest, &shactx);

        hash = std::vector<uint8_t>(SHA_DIGEST_LENGTH);
        for (uint32_t i = 0; i < SHA_DIGEST_LENGTH; ++i)
        {
            hash.at(i) = (uint8_t) digest[i]; 
        }
    }

    void sha256_hash(const std::vector<uint8_t>& data, std::vector<uint8_t>& hash)
    {
        unsigned char digest[SHA256_DIGEST_LENGTH];
        
        SHA256_CTX shactx;
    
        SHA256_Init(&shactx);
        SHA256_Update(&shactx, data.data(), data.size() - 1);
        SHA256_Final(digest, &shactx);

        hash = std::vector<uint8_t>(SHA256_DIGEST_LENGTH);
        for (uint32_t i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        {
            hash.at(i) = (uint8_t) digest[i]; 
        }
    }

    void sha512_hash(const std::vector<uint8_t>& data, std::vector<uint8_t>& hash)
    {
        unsigned char digest[SHA512_DIGEST_LENGTH];
        
        SHA512_CTX shactx;
    
        SHA512_Init(&shactx);
        SHA512_Update(&shactx, data.data(), data.size() - 1);
        SHA512_Final(digest, &shactx);

        hash = std::vector<uint8_t>(SHA512_DIGEST_LENGTH);
        for (uint32_t i = 0; i < SHA512_DIGEST_LENGTH; ++i)
        {
            hash.at(i) = (uint8_t) digest[i]; 
        }
    }

    
}
}
