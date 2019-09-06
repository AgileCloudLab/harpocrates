#include "harpocrates.hpp"

#include <openssl/aes.h>

#include <string.h>
#include <cstdint>
#include <string>
#include <vector>

#include <algorithm>
#include <ctime>

#include <iostream>
namespace harpocrates
{

    /// Converts a size_t (unsigned int) to a byte vector
    /// @param size_t to be converted
    /// @return a byte vector representation of the size_t
    std::vector<uint8_t> size_to_vector(size_t size)
    {
        std::vector<uint8_t> _size(sizeof(size_t));


        for (uint8_t i = 0; i < sizeof(size_t); ++i)
        {
            _size.at(i) = 0xFF & (size >> (i * 8));
        }
        
        return _size;
    }

    /// Converts a byte vector to a size_t (unsigned int)
    /// @param a byte vector to be converted
    /// @return a size_t 
    size_t vector_to_size(std::vector<uint8_t> size)
    {
        
        size_t _size = 0;

        for (uint8_t i = 0; i < size.size(); ++i)
        {
            _size ^=  (((uint64_t)size.at(i)) << (i * 8));
        }

        return _size; 
    }
    
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

       	// Set up the key, convert it to the format required by OpenSSLs
        unsigned char ukey[HARPOCRATES_AES_KEY_SIZE];        
        for (uint32_t i = 0; i < HARPOCRATES_AES_KEY_SIZE; ++i)
        {
            ukey[i] = (unsigned char) key[i];
        }
	AES_KEY encryption_key;
        AES_set_encrypt_key(ukey, HARPOCRATES_AES_KEY_SIZE * 8, &encryption_key); //key size in bits rather than bytes

	// If necessary, pad the cleartext to have a size that is a multiple of AES_BLOCK_SIZE
	size_t cleartext_size = data.size();
	size_t padded_size = cleartext_size;
	
	if(cleartext_size % AES_BLOCK_SIZE != 0)
	{
	    padded_size += AES_BLOCK_SIZE - cleartext_size % AES_BLOCK_SIZE;
	    data.resize(padded_size);
	}

	size_t ciphertext_size = padded_size;
	
	// Generate the initialization vector, either randomly or by chosing an all-0 vector
        std::vector<uint8_t> iv;        
        if (random_iv)
        {
            iv = generate_iv(AES_BLOCK_SIZE);
	    ciphertext_size += AES_BLOCK_SIZE;
        }
        else
        {
            iv = std::vector<uint8_t>(AES_BLOCK_SIZE, 0);
        }

	//Generate a vector representing the original cleartext_size
	std::vector<uint8_t> cleartext_size_vectorized = size_to_vector(cleartext_size);
	size_t size_vec_size = cleartext_size_vectorized.size();
	ciphertext_size += size_vec_size;

	//Create the vector that will hold the ciphertext and emplace the metadata to its end
	//Format: {SIZE_OF_CLEARTEXT | PADDED_CIPHERTEXT | IV(OPTIONAL)} 
	std::vector<uint8_t> ciphertext(ciphertext_size);       
	memcpy(ciphertext.data(), cleartext_size_vectorized.data(), size_vec_size);
	if(random_iv)
	{
	    memcpy(ciphertext.data() + size_vec_size + padded_size, iv.data(), AES_BLOCK_SIZE);
	}
		
	//Do the actual encryption
	AES_cbc_encrypt(data.data(), ciphertext.data() + size_vec_size, padded_size, &encryption_key, iv.data(), AES_ENCRYPT);

	//Save result
	data = ciphertext;
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
        
        std::vector<uint8_t>::const_iterator size_start = data.begin();
        std::vector<uint8_t>::const_iterator size_end = data.begin() + 8;
        std::vector<uint8_t>::const_iterator cipher_start = data.begin() + 8;
        std::vector<uint8_t>::const_iterator cipher_end;

        if (random_iv)
        {
            cipher_end = data.begin() + (data.size() - HARPOCRATES_AES_KEY_SIZE);
        }
        else
        {
            cipher_end = data.end();
        }

        

        std::vector<uint8_t> cleartext_size_vec = std::vector<uint8_t>(size_start, size_end);
        std::vector<uint8_t> cipher = std::vector<uint8_t>(cipher_start, cipher_end);        
        
        std::vector<uint8_t> iv;
        
        if (random_iv)
        {
            std::vector<uint8_t>::const_iterator iv_start = data.begin() + (data.size() - HARPOCRATES_AES_KEY_SIZE);
            std::vector<uint8_t>::const_iterator iv_end = data.end();
            
            iv = std::vector<uint8_t>(iv_start, iv_end);            
        }
        else
        {
            iv = std::vector<uint8_t>(HARPOCRATES_AES_KEY_SIZE, 0);             
        }

        size_t cleartext_size = vector_to_size(cleartext_size_vec);
        std::vector<uint8_t> decrypted(cipher.size());

        if ( cleartext_size < (AES_BLOCK_SIZE * 8))
        {
            std::vector<uint8_t>::const_iterator data_start = decrypted.begin();
            std::vector<uint8_t>::const_iterator data_end = decrypted.begin() + cleartext_size;
            std::vector<uint8_t> temp_decrypted = std::vector<uint8_t>(data_start, data_end);
            decrypted = temp_decrypted; 
        }

        AES_KEY decrypt_key;
        AES_set_decrypt_key(ukey, HARPOCRATES_AES_KEY_SIZE * 8, &decrypt_key);
        AES_cbc_encrypt(cipher.data(), decrypted.data(), cipher.size(), &decrypt_key,iv.data(), AES_DECRYPT);
        // data.assign(decrypted.begin(), decrypted.end());


        if (cleartext_size > (AES_BLOCK_SIZE * 8) && cleartext_size % (AES_BLOCK_SIZE * 8) != 0)
        {
            std::vector<uint8_t>::const_iterator data_start = decrypted.begin();
            std::vector<uint8_t>::const_iterator data_end = decrypted.begin() + cleartext_size;
            std::vector<uint8_t> temp_decrypted = std::vector<uint8_t>(data_start, data_end);
            decrypted = temp_decrypted; 
        }
        data = decrypted; 
    }
}

