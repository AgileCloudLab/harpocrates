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

    void hash(const uint8_t* data, const size_t size, uint8_t* hash, hash_type type)
    {
        switch(type)
        {
        case hash_type::SHA1:
            sha1_hash(data, size, hash);
            break;
	case hash_type::SHA256:
            sha256_hash(data, size, hash);
            break;
        case hash_type::SHA512:
            sha512_hash(data, size, hash);
            break;
        default:
            sha1_hash(data, size, hash);
            break;
        }
    }

    void sha1_hash(const std::vector<uint8_t>& data, std::vector<uint8_t>& hash)
    {
        unsigned char digest[SHA_DIGEST_LENGTH];

        SHA_CTX shactx;

        SHA1_Init(&shactx);
        SHA1_Update(&shactx, data.data(), data.size());
        SHA1_Final(digest, &shactx);

        hash = std::vector<uint8_t>(SHA_DIGEST_LENGTH);
        for (uint32_t i = 0; i < SHA_DIGEST_LENGTH; ++i)
        {
            hash.at(i) = (uint8_t) digest[i]; 
        }
    }

    void sha1_hash(const uint8_t* data, const size_t size, uint8_t* hash)
    {
        SHA_CTX shactx;

        SHA1_Init(&shactx);
        SHA1_Update(&shactx, data, size);
        SHA1_Final(hash, &shactx);
    }

    void sha256_hash(const std::vector<uint8_t>& data, std::vector<uint8_t>& hash)
    {
        unsigned char digest[SHA256_DIGEST_LENGTH];
        
        SHA256_CTX shactx;
    
        SHA256_Init(&shactx);
        SHA256_Update(&shactx, data.data(), data.size());
        SHA256_Final(digest, &shactx);

        hash = std::vector<uint8_t>(SHA256_DIGEST_LENGTH);
        for (uint32_t i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        {
            hash.at(i) = (uint8_t) digest[i]; 
        }
    }

    void sha256_hash(const uint8_t* data, const size_t size, uint8_t* hash)
    {
	SHA256_CTX shactx;

        SHA256_Init(&shactx);
        SHA256_Update(&shactx, data, size);
        SHA256_Final(hash, &shactx);
    }

    void sha512_hash(const std::vector<uint8_t>& data, std::vector<uint8_t>& hash)
    {
        unsigned char digest[SHA512_DIGEST_LENGTH];

        SHA512_CTX shactx;

        SHA512_Init(&shactx);
        SHA512_Update(&shactx, data.data(), data.size());
        SHA512_Final(digest, &shactx);

        hash = std::vector<uint8_t>(SHA512_DIGEST_LENGTH);
        for (uint32_t i = 0; i < SHA512_DIGEST_LENGTH; ++i)
        {
            hash.at(i) = (uint8_t) digest[i]; 
        }
    }

    void sha512_hash(const uint8_t* data, const size_t size, uint8_t* hash)
    {
	SHA512_CTX shactx;

	SHA512_Init(&shactx);
	SHA512_Update(&shactx, data, size);
	SHA512_Final(hash, &shactx);
    }

    size_t get_digest_length(hash_type type)
    {
	switch(type)
        {
        case hash_type::SHA1:
            return SHA_DIGEST_LENGTH;
	case hash_type::SHA256:
	    return SHA256_DIGEST_LENGTH;
        case hash_type::SHA512:
            return SHA512_DIGEST_LENGTH;
        default:
            return SHA_DIGEST_LENGTH;
        }
     }

    
}
}
