#include "harpocrates.hpp"

#include <openssl/aes.h>

#include <cstdint>
#include <string>
#include <vector>

#include <algorithm>
#include <ctime>

namespace harpocrates
{

    // Standard AES key size for CBC std is 128bit 
    const size_t HARPOCRATES_AES_KEY_SIZE = 16;

    /// Generates a random sequence of size bytes, which is used for the randomised IV
    /// @param size is the size of the randomise vector in bytes
    /// @return a vector of bytes
    std::vector<uint8_t> generate_iv(size_t size)
    {
        srand(static_cast<uint32_t>(time(0)));
        std::vector<uint8_t> data(size);
        std::generate(data.begin(), data.end(), rand);
        return data; 
    }

    /// Encryptes the data based on the provided key.
    /// If the key is longer than 16Bytes no problem we cut it off 
    /// @param key is a string containing the key used for the AES CBC encryption
    /// @param data is the data to be encrypt and will contain the encrypted data
    /// @param random_iv determines if we use a random IV. If set to false we will use an all 0 IV. If true we have appended the IV to the data
    void encrypt(const std::string& key, std::vector<uint8_t>& data, bool random_iv)
    {
        if (key.size() < HARPOCRATES_AES_KEY_SIZE)
        {
            // TODO throw error
        }

        unsigned char ukey[HARPOCRATES_AES_KEY_SIZE];
        
        for (uint32_t i = 0; i < HARPOCRATES_AES_KEY_SIZE; ++i)
        {
            ukey[i] = (unsigned char) key[i];
        }

        std::vector<uint8_t> iv;
        
        if (random_iv)
        {
            iv = generate_iv(AES_BLOCK_SIZE); 
        }
        else
        {
            iv = std::vector<uint8_t>(AES_BLOCK_SIZE, 0);
        }

        // The openSSL encryption alters the IV and
        // therefore we use it this persistent iv
        const std::vector<uint8_t> persistent_iv = iv;

        std::vector<uint8_t> cipher(data.size());

        AES_KEY encryption_key;
        AES_set_encrypt_key(ukey, HARPOCRATES_AES_KEY_SIZE * 8, &encryption_key);
        AES_cbc_encrypt(data.data(), cipher.data(), data.size(), &encryption_key, iv.data(), AES_ENCRYPT);

        if (!random_iv)
        {
            data = cipher;
            return;
        }
        
        std::move(persistent_iv.begin(), persistent_iv.end(), std::back_inserter(cipher));
        data = cipher;
    }

    /// Encryptes the data based on the provided key.
    /// If the key is longer than 16Bytes no problem we cut it off 
    /// @param key is a string containing the key used for the AES CBC decryption
    /// @param data is the data to be decrypted and will contain the decrypted data
    /// @param random_iv determines if a random IV was used for encryption. If set to false we will use an all 0 IV    
    void decrypt(const std::string& key, std::vector<uint8_t>& data, bool random_iv)
    {
        if (key.size() < HARPOCRATES_AES_KEY_SIZE)
        {
            // TODO throw error
        }
        
        unsigned char ukey[HARPOCRATES_AES_KEY_SIZE];

        for (uint32_t i = 0; i < HARPOCRATES_AES_KEY_SIZE; ++i)
        {
            ukey[i] = (unsigned char) key[i];
        }


        std::vector<uint8_t> cipher;
        std::vector<uint8_t> iv;
        
        if (random_iv)
        {
            std::vector<uint8_t>::const_iterator cipher_start = data.begin();
            std::vector<uint8_t>::const_iterator cipher_end = data.begin() + (data.size() - HARPOCRATES_AES_KEY_SIZE);
            std::vector<uint8_t>::const_iterator iv_start = data.begin() + (data.size()  - HARPOCRATES_AES_KEY_SIZE);
            std::vector<uint8_t>::const_iterator iv_end = data.end();

            cipher = std::vector<uint8_t>(cipher_start, cipher_end);
            iv = std::vector<uint8_t>(iv_start, iv_end);            
        }
        else
        {
            cipher = data; 
            iv = std::vector<uint8_t>(HARPOCRATES_AES_KEY_SIZE, 0);             
        }

        std::vector<uint8_t> decrypted(cipher.size()); 

        AES_KEY decrypt_key;
        AES_set_decrypt_key(ukey, HARPOCRATES_AES_KEY_SIZE * 8, &decrypt_key);
        AES_cbc_encrypt(cipher.data(), decrypted.data(), cipher.size(), &decrypt_key,iv.data(), AES_DECRYPT);
        data = decrypted; 
    }
}
