#include <harpocrates/hashing.hpp>

#include <gtest/gtest.h>

#include <string>
#include <cstdint>
#include <vector>

#include <ctime>
#include <algorithm>

#include <utility>
#include <sstream>

void print_hex(const std::vector<uint8_t>& data)
{
    std::stringstream ss;
    for (const auto& elm : data)
    {
        ss << std::hex << (int) elm; 
    }

    std::cout << ss.str() << std::endl; 
}

std::vector<uint8_t> generate_data(size_t size)
{
    std::vector<uint8_t> data(size);
    std::generate(data.begin(), data.end(), rand);
    return data; 
}


TEST(test_hashing, test_sha1_hashing_1kb)
{

    std::vector<uint8_t> data = generate_data(1024);
    std::vector<uint8_t> data1 = data;
    std::vector<uint8_t> data2 = generate_data(1024);
    
    EXPECT_EQ(data, data1);
    EXPECT_NE(data, data2);

    std::vector<uint8_t> hash1;
    std::vector<uint8_t> hash2;
    std::vector<uint8_t> hash3;    
    
    harpocrates::hashing::sha1_hash(data, hash1);
    harpocrates::hashing::sha1_hash(data1, hash2);
    harpocrates::hashing::sha1_hash(data2, hash3);        

    EXPECT_EQ(hash1, hash2);
    EXPECT_NE(hash1, hash3);    
}

TEST(test_hashing, test_sha1_hashing_4kb)
{

    std::vector<uint8_t> data = generate_data(4096);
    std::vector<uint8_t> data1 = data;
    std::vector<uint8_t> data2 = generate_data(4096);
    
    EXPECT_EQ(data, data1);
    EXPECT_NE(data, data2);

    std::vector<uint8_t> hash1;
    std::vector<uint8_t> hash2;
    std::vector<uint8_t> hash3;    
    
    harpocrates::hashing::sha1_hash(data, hash1);
    harpocrates::hashing::sha1_hash(data1, hash2);
    harpocrates::hashing::sha1_hash(data2, hash3);        

    EXPECT_EQ(hash1, hash2);
    EXPECT_NE(hash1, hash3);    
}

TEST(test_hashing, test_sha256_hashing_1kb)
{

    std::vector<uint8_t> data = generate_data(1024);
    std::vector<uint8_t> data1 = data;
    std::vector<uint8_t> data2 = generate_data(1024);
    
    EXPECT_EQ(data, data1);
    EXPECT_NE(data, data2);

    std::vector<uint8_t> hash1;
    std::vector<uint8_t> hash2;
    std::vector<uint8_t> hash3;    
    
    harpocrates::hashing::sha256_hash(data, hash1);
    harpocrates::hashing::sha256_hash(data1, hash2);
    harpocrates::hashing::sha256_hash(data2, hash3);        

    EXPECT_EQ(hash1, hash2);
    EXPECT_NE(hash1, hash3);    
}

TEST(test_hashing, test_sha256_hashing_4kb)
{

    std::vector<uint8_t> data = generate_data(4096);
    std::vector<uint8_t> data1 = data;
    std::vector<uint8_t> data2 = generate_data(4096);
    
    EXPECT_EQ(data, data1);
    EXPECT_NE(data, data2);

    std::vector<uint8_t> hash1;
    std::vector<uint8_t> hash2;
    std::vector<uint8_t> hash3;    
    
    harpocrates::hashing::sha256_hash(data, hash1);
    harpocrates::hashing::sha256_hash(data1, hash2);
    harpocrates::hashing::sha256_hash(data2, hash3);        

    EXPECT_EQ(hash1, hash2);
    EXPECT_NE(hash1, hash3);    
}

TEST(test_hashing, test_sha512_hashing_1kb)
{

    std::vector<uint8_t> data = generate_data(1024);
    std::vector<uint8_t> data1 = data;
    std::vector<uint8_t> data2 = generate_data(1024);
    
    EXPECT_EQ(data, data1);
    EXPECT_NE(data, data2);

    std::vector<uint8_t> hash1;
    std::vector<uint8_t> hash2;
    std::vector<uint8_t> hash3;    
    
    harpocrates::hashing::sha512_hash(data, hash1);
    harpocrates::hashing::sha512_hash(data1, hash2);
    harpocrates::hashing::sha512_hash(data2, hash3);        

    EXPECT_EQ(hash1, hash2);
    EXPECT_NE(hash1, hash3);    
}

TEST(test_hashing, test_sha512_hashing_4kb)
{

    std::vector<uint8_t> data = generate_data(4096);
    std::vector<uint8_t> data1 = data;
    std::vector<uint8_t> data2 = generate_data(4096);
    
    EXPECT_EQ(data, data1);
    EXPECT_NE(data, data2);

    std::vector<uint8_t> hash1;
    std::vector<uint8_t> hash2;
    std::vector<uint8_t> hash3;    
    
    harpocrates::hashing::sha512_hash(data, hash1);
    harpocrates::hashing::sha512_hash(data1, hash2);
    harpocrates::hashing::sha512_hash(data2, hash3);        

    EXPECT_EQ(hash1, hash2);
    EXPECT_NE(hash1, hash3);    
}

int main(int argc, char **argv) {

    srand(static_cast<uint32_t>(time(0)));
        
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
