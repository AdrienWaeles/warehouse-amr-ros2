#include <iostream>

#include "amr_core/version.hpp"

int main() {
  std::cout << "AMR simulation v" << amr_core::version() << '\n';
  return 0;
}
