#include <harpocrates/harpocrates.hpp>

#include <cstdint>
#include <vector>

#include <ctime>
#include <algorithm>

#include <iostream>

std::vector<uint8_t> random_data(size_t size)
{
    srand(static_cast<uint32_t>(time(0)));
    std::vector<uint8_t> data(size);
    std::generate(data.begin(), data.end(), rand);
    return data; 
}

int main(void)
{
    // Generate a 1kB data vector
    std::vector<uint8_t> data = random_data(1042);
    std::vector<uint8_t> validation_data = data;

    std::string key = "WAPFZ52K0446FPJ32OU5";

    // Here we encrypt a byte vector with an all 0 IV
    // The result:
    // | orignal size | Encrypted data |
    // Orignal size is the orignal data size as we may need
    // padding and it takes up 8 bytes
    harpocrates::encrypt(key, data);

    if (data == validation_data)
    {
        std::cout << "Something went wrong during encrypt, please report a bug" << std::endl;
    }
    else
    {
        std::cout << "Data is encrypted" << std::endl; 
    }

    harpocrates::decrypt(key, data);
    
    if (data == validation_data)
    {
        std::cout << "Data decrypted successfully" << std::endl;
    }
    else
    {
        std::cout << "Something went wrong during decrypt, please report a bug" << std::endl;     
    }


    // Example for Randomized IV
    // The result:
    // | orignal size | Encrypted data | RANDOM IV |
    // Original size is the orignal data size as we may need
    // patting and it takes up size_t bytes
    std::vector<uint8_t> data_2 = validation_data;

    harpocrates::encrypt(key, data_2, true);

    if (data_2 == validation_data)
    {
        std::cout << "Something went wrong during encrypt, please report a bug" << std::endl;
    }
    else
    {
        std::cout << "Data is encrypted" << std::endl; 
    }

    harpocrates::decrypt(key, data_2, true);
    
    if (data_2 == validation_data)
    {
        std::cout << "Data decrypted successfully" << std::endl;
    }
    else
    {
        std::cout << "Something went wrong during decrypt, please report a bug" << std::endl;     
    }

    return 0; 
}
