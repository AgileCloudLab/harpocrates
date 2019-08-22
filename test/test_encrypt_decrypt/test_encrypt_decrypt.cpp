#include <harpocrates/harpocrates.hpp>

#include <gtest/gtest.h>

#include <string>
#include <cstdint>
#include <vector>

#include <ctime>
#include <algorithm>

std::vector<uint8_t> generate_data(size_t size)
{
    srand(static_cast<uint32_t>(time(0)));

    std::vector<uint8_t> data(size);
    std::generate(data.begin(), data.end(), rand);
    return data; 
}

TEST(test_encrypt_decrypt, test_encrypt_decrypt_1kb)
{

    std::vector<uint8_t> data = generate_data(1024);
    std::vector<uint8_t> temp = data; 

    EXPECT_EQ(data, temp);
    
    std::string key = "WAPFZ52K0446FPJ32OU5";

    harpocrates::encrypt(key, data);
    EXPECT_NE(data, temp);

    std::vector<uint8_t> temp_crypt(data);
    EXPECT_EQ(data, temp_crypt);

    harpocrates::decrypt(key, data);
    EXPECT_NE(data, temp_crypt);
    EXPECT_EQ(data, temp); 
    
}

TEST(test_encrypt_decrypt, test_encrypt_decrypt_with_random_iv_1kb)
{

    std::vector<uint8_t> data = generate_data(1024);
    std::vector<uint8_t> temp = data; 

    EXPECT_EQ(data, temp);
    
    std::string key = "WAPFZ52K0446FPJ32OU5";

    harpocrates::encrypt(key, data, true);
    EXPECT_NE(data, temp);

    std::vector<uint8_t> temp_crypt(data);
    EXPECT_EQ(data, temp_crypt);

    harpocrates::decrypt(key, data, true);
    EXPECT_NE(data, temp_crypt);
    EXPECT_EQ(data, temp); 
    
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
