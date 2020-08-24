# Change log for Harpocrates


# Latest: 3.2.0

- Minor: Added a function to convert a hash type to a string 
- Bug fix: CRC was appending data to end of vector instead of replacing. 

# 3.0.0

- Major: Splitting functions in the hashing name space into two sub-namespaces. One for vectors and one for pointers

# 2.5.2

- Major: Releasing Harpocrates to the public 

# 2.5.1

- Major: We now officially support SHA-1, SHA-256, and SHA-512 hashing of both `std::vector<uint8_t>` and `uint8_t *`
- Minor: We fixed a bug in hashing that resulted in the last byte of a vector not being hashed 


## 2.0.0 
- Minor: We have stopped using Crypto++ for AES encryption
- Minor: We have moved to using OpenSSL for AES encryption 
- Major: We have swapped the `key` and `data` parameter for both decrypt and encrypt 
- Major: We have added a parameter `random_iv` for enabling generating random IV 
- Minor: We have added the self contained capability of generating random IV
- Minor: We have added Doxygen documentation 
- Major: We have have moved to MIT License 
