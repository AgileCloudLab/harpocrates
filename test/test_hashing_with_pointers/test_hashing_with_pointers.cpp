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


void test_hashing_with_pointers(int data_size, harpocrates::hashing::hash_type hash_type)
{
    size_t digest_size = harpocrates::hashing::get_digest_length(hash_type);
    std::vector<uint8_t> data = generate_data(data_size);
    std::vector<uint8_t> data1 = data;
    std::vector<uint8_t> data2 = generate_data(data_size);
    
    EXPECT_EQ(data, data1);
    EXPECT_NE(data, data2);

    std::vector<uint8_t> hash1(digest_size);
    std::vector<uint8_t> hash2(digest_size);
    std::vector<uint8_t> hash3(digest_size);    
    
    harpocrates::hashing::hash(data.data(), data_size, hash1.data(), hash_type);
    harpocrates::hashing::hash(data1.data(), data_size, hash2.data(), hash_type);
    harpocrates::hashing::hash(data2.data(), data_size, hash3.data(), hash_type);        

    EXPECT_EQ(hash1, hash2);
    EXPECT_NE(hash1, hash3);    
}

TEST(test_hashing_with_pointers, test_sha1_hashing_1kb)
{
    test_hashing_with_pointers(1024, harpocrates::hashing::hash_type::SHA1);
}

TEST(test_hashing_with_pointers, test_sha1_hashing_4kb)
{
    test_hashing_with_pointers(4096, harpocrates::hashing::hash_type::SHA1);
}

TEST(test_hashing_with_pointers, test_sha256_hashing_1kb)
{
    test_hashing_with_pointers(1024, harpocrates::hashing::hash_type::SHA256);
}

TEST(test_hashing_with_pointers, test_sha256_hashing_4kb)
{
    test_hashing_with_pointers(4096, harpocrates::hashing::hash_type::SHA256);
}

TEST(test_hashing_with_pointers, test_sha512_hashing_1kb)
{
    test_hashing_with_pointers(1024, harpocrates::hashing::hash_type::SHA512);
}

TEST(test_hashing_with_pointers, test_sha512_hashing_4kb)
{
    test_hashing_with_pointers(4096, harpocrates::hashing::hash_type::SHA512);
}

int main(int argc, char **argv) {

    srand(static_cast<uint32_t>(time(0)));
        
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
