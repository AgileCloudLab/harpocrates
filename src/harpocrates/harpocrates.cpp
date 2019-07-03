#include "harpocrates.hpp"
#include "helpers/convert.hpp"

#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/cryptlib.h>

namespace harpocrates
{    
    void encrypt(std::vector<uint8_t>& data, const std::string& key)
    {
        std::string crypto_key = key.substr(0, CryptoPP::AES::DEFAULT_KEYLENGTH);
        std::string data_str = helpers::convert::vector_to_string(data);
        std::string cipher_text; 
        CryptoPP::byte ckey[ CryptoPP::AES::DEFAULT_KEYLENGTH ];

        for (uint32_t i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; ++i)
        {
            ckey[i] = static_cast<CryptoPP::byte>(crypto_key[i]);
        }

        CryptoPP::byte iv[ CryptoPP::AES::BLOCKSIZE ];
        
        memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

        CryptoPP::AES::Encryption aes_encryption(ckey, CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Encryption cbc_encryption( aes_encryption, iv );

        CryptoPP::StreamTransformationFilter stf_encryptor(cbc_encryption, new CryptoPP::StringSink( cipher_text ) );
        stf_encryptor.Put( reinterpret_cast<const unsigned char*>( data_str.c_str() ), data_str.size() );
        stf_encryptor.MessageEnd();

        std::vector<uint8_t> encrypted_data = helpers::convert::string_to_vector(cipher_text);

        data = encrypted_data; 
    }
    

    
    void decrypt(std::vector<uint8_t>& data, const std::string& key)
    {
        std::string crypto_key = key.substr(0, CryptoPP::AES::DEFAULT_KEYLENGTH);
        std::string cipher_text = helpers::convert::vector_to_string(data);

        CryptoPP::byte ckey[ CryptoPP::AES::DEFAULT_KEYLENGTH ];
        for (uint32_t i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; ++i)
        {
            ckey[i] = static_cast<CryptoPP::byte>(crypto_key[i]);
        }
        
        CryptoPP::byte iv[ CryptoPP::AES::BLOCKSIZE ];

        CryptoPP::AES::Decryption aes_decryption(ckey, CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aes_decryption, iv );

        std::string decrypted_text;
        CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decrypted_text ) );
        stfDecryptor.Put( reinterpret_cast<const unsigned char*>( cipher_text.c_str() ), cipher_text.size() );
        stfDecryptor.MessageEnd();
        
    }
}
