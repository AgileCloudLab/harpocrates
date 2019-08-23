# Harpocrates

Harpocrates is a library for easy AES CBC encryption/decryption of `std::vector<uint8_t>` in C++.

Harpocrates is developed at Aarhus University, Department of Engineering in the Group for Network Computing, Communications and Storage. 

## License 

Harpocrates is available under the MIT software license, see the License file for more information 

## Dependencies 

This library depends on [*openSSL*](https://www.openssl.org/), where the developer version must be installed to compile. 

| Platform | Command                           |
|----------|-----------------------------------|
| Ubuntu   | `sudo apt-get install openssl-dev`|
| Fedora   | `sudo dnf install openssl-devel`  |
| MacOS    | `brew install openssl`            |

For building Harpocrates we use the waf build system [*WAF*](https://waf.io/), which requires *python v2.7+*, but not 3. 

We have made the restriction that Harpocrates can only be build using `clang++` so you will need that. This will change later. 

## Build 

To build Harpocrates you must first configure the project, in the root folder of the project run the command: 

```bash 
    python waf configure 
```

Next to build, from the root folder of the project run the command: 

```bash 
    python waf build 
```

In the build folder you will find the `.a` file and in `src/harpocrates` you will find the Harpocrates header. 

## Documentation 

For documentation we use [*doxygen*](http://doxygen.nl/) to build documentation, in the root folder run the command:

```bash 
    python waf doc
```

This will generate the documentation in the `build/doc` folder. 

## Example 

**Example with all 0 IV**

```C++
    #include <harpocrates/harpocrates.hpp>
    
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
```

**Example with random IV**

```c++
    #include <harpocrates/harpocrates.hpp>
    
    std::vector<uint8_t> data = random_data(1024);
    std::vector<uint8_t> validation_data = data;
    std::string key = "WAPFZ52K0446FPJ32OU5";
    harpocrates::encrypt(key, data);
    
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
    
```

**Example helper function**

```c++
std::vector<uint8_t> random_data(size_t size)
{
    srand(static_cast<uint32_t>(time(0)));
    std::vector<uint8_t> data(size);
    std::generate(data.begin(), data.end(), rand);
    return data; 
}
```

## Contributions 

**List of contributors**

| Contributor   | Contact           | Contribution                                                |
|---------------|-------------------|-------------------------------------------------------------|
| Marton Sipsos | siposm@aut.bme.hu | Added benchmarks to Harpocrates                             |
| Lars Nielsen  | lani@eng.au.dk    | Maintainer, initial development, documentation, and testing |
 


## Acknowledgement 


<center>
<a href="http://www.au.dk/"><img width="250" src="https://github.com/AgileCloudLab/harpocrates/blob/master/graphics/aulogo_uk_var1_blue.png" alt="au-logo"/></a>
<a href="http://eng.au.dk/en/research/electrical-and-computer-engineering/communications-and-networks/network-computing-communications-and-storage/"><img width="250" src="https://github.com/AgileCloudLab/harpocrates/blob/master/graphics/Scale_IoT_Logo.png" alt="au-logo"/></a>
</center>
