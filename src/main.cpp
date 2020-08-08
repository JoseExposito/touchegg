#include <iostream>

#include "config/config.h"

int main(/* int, char ** */) {
  std::cout << "Hello, world!\n";
  Config config;
  config.loadConfig();
}
