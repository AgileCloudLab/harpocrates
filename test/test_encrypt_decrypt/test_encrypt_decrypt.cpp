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
    std::vector<uint8_t> temp(data); 

    EXPECT_EQ(data, temp);
    
    std::string key = "WAPFZ52K0446FPJ32OU5";

    harpocrates::encrypt(data, key);
    EXPECT_NE(data, temp); 
    
    // auto config = test_configuration();

    // minerva::minerva m(config);

    // std::string fileout = config["fileout_path"].get<std::string>();
    // std::string indexing =
    //     (config["indexing_config"].get<nlohmann::json>())["indexing_path"].get<std::string>();

    
    // EXPECT_TRUE(std::filesystem::exists(fileout));
    // EXPECT_TRUE(std::filesystem::exists(indexing));

    // std::filesystem::remove(fileout);
    // std::filesystem::remove(indexing);

    // EXPECT_FALSE(std::filesystem::exists(fileout));
    // EXPECT_FALSE(std::filesystem::exists(indexing));    

                
    // std::string config_path = "./config_files/test_minerva_config.json";
    // auto config = tartarus::readers::json_reader(config_path);
    // EXPECT_EQ(config["file_format"].get<minerva::file_format>(), 1);
    // auto minerva = minerva::minerva(config);
    // EXPECT_EQ("./test_register/", minerva.register_path());
    // EXPECT_EQ("./test_storage/", minerva.out_path());
    // EXPECT_EQ("./test_base_storage/", minerva.base_register_path());

    // std::filesystem::remove(minerva.register_path());
    // std::filesystem::remove(minerva.out_path());
    // std::filesystem::remove(minerva.base_register_path()); 
    
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
