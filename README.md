# libcfg
A minimalistic and easy to set up configuration manager for C++ projects.

## How to use

```c++
#include <iostream>
#include "../src/config.h"

int main() {
    // 1. Define a settings vector containing all your settings
    std::vector<std::string> settings = {
            "int",
            "float",
            "string",
            "bool",
            "double"
    };

    // 2. Create a config instance, giving a path to the config file and the settings map
    auto* config = new class config("./config.cfg", settings);

    // 3. Get settings at runtime using the setting identifier
    std::cout << config->get<int>("int") << std::endl;
    std::cout << config->get<float>("float") << std::endl;
    std::cout << config->get<std::string>("string") << std::endl;
    std::cout << config->get<bool>("bool") << std::endl;
    std::cout << config->get<double>("double") << std::endl;

    return 0;
}
```

## Example config file

```cfg
int=1337
float=3.14
string=hello
double=3.14
bool=1
```

## Notes

- The configuration file will be automatically created the first time you start the program.
- Currently supported setting types are listed [here](https://en.cppreference.com/w/cpp/io/basic_ostream/operator_ltlt)
- boolean values need to be written as `0` or `1`

## Coding style

https://lefticus.gitbooks.io/cpp-best-practices/content/ (except for types which are snake_case), put `.cpp` and `.hpp` files next to each other in ./src