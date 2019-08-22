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
    std::vector<uint8_t> data = random_data(1024);
    std::vector<uint8_t> validation_data = data;

    std::string key = "WAPFZ52K0446FPJ32OU5";
    harpocrates::encrypt(key, data);

    if (data == validation_data)
    {
        std::cout << "Something is wrong please report a bug" << std::endl;
    }
    else
    {
        std::cout << "Data is encrypted" << std::endl; 
    }

    harpocrates::decrypt(key, data);
    
    if (data == validation_data)
    {
        std::cout << "Data is decrypted" << std::endl;
    }
    else
    {
        std::cout << "Something is wrong please report a bug" << std::endl;     
    }


    // Example for Randomized IV
    data = validation_data;

    harpocrates::encrypt(key, data, true);

    if (data == validation_data)
    {
        std::cout << "Something is wrong please report a bug" << std::endl;
    }
    else
    {
        std::cout << "Data is encrypted" << std::endl; 
    }

    harpocrates::decrypt(key, data, true);
    
    if (data == validation_data)
    {
        std::cout << "Data is decrypted" << std::endl;
    }
    else
    {
        std::cout << "Something is wrong please report a bug" << std::endl;     
    }

    return 0; 
}
