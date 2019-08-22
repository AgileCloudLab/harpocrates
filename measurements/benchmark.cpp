#include <harpocrates/harpocrates.hpp>

#include <chrono>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>


int main(int argc, char** argv)
{
    int message_size = 1024;
    int data_size = 1000000000; //~1GB

    //Parse command line arguments
    if(argc > 1)
      {
	int message_size_from_cmd = std::atoi(argv[1]);
	if(message_size_from_cmd)
	  message_size = message_size_from_cmd;
      }

    //Calculate the number of iterations
    int iterations = data_size / message_size;
    if(iterations > 10000)
      iterations = 10000;
    data_size = iterations * message_size;


    // Seed the random number generator and generate random data
    int seed = static_cast<uint32_t>(time(0));
    srand(seed);
    std::vector<std::vector<uint8_t>> data;
    for(int i = 0; i < iterations; i++)
      {
	std::vector<uint8_t> message(message_size);
	std::generate(message.begin(), message.end(), rand);
	data.push_back(message);
      }

    std::string key = "WAPFZ52K0446FPJ32OU5";

    //Encrypt benchmark
    auto t1 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < iterations; i++)
      {
          harpocrates::encrypt(key, data[i]);
      }
    auto t2 = std::chrono::high_resolution_clock::now();

    auto td = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1);
    double encrypt_MBps = data_size/(double)td.count();
    std::cout << "Encryption of " << data_size << " bytes in chunks of "
	      << message_size << " bytes done in " << td.count() << "us\n";
    std::cout << encrypt_MBps << " MB/s" << std::endl;

    //Decrypt benchmark
    t1 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < iterations; i++)
      {
          harpocrates::decrypt(key, data[i]);
      }
    t2 = std::chrono::high_resolution_clock::now();

    td = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1);
    double decrypt_MBps = data_size/(double)td.count();
    std::cout << "Decryption of " << data_size << " bytes in chunks of "
	      << message_size << " bytes done in " << td.count() << "us\n";
    std::cout << decrypt_MBps << " MB/s" << std::endl;
}
