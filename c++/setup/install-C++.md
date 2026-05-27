# Install C++ on Ubuntu
## 1. Install the C++ Compiler (g++)
```sh
sudo apt update
sudo apt install build-essential gdb -y

g++ --version
```

## 2. Install Visual Studio Code and Extensions

```sh
# Download the .deb package for Ubuntu/Debian.
sudo dpkg -i <path-to-downloaded-file>.deb
```

## 3. Write and Compile Your First Program
```cpp
#include <iostream>

int main() {
    std::cout << "Hello, DSA on Ubuntu! 😄" << std::endl;
    return 0;
}
```

```sh
g++ hello.cpp -o hello
./hello
```

## 4. Enable extension on vscode or cursor
 - make sure after installation g++ and not gcc is selected
 - run the same test script