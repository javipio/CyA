#include <fstream>
#include <iostream>

#include "Grammar.h"

int main(int argc, char* argv[]) {
  if (argc < 4) {
    std::cout << "a" << std::endl;
    return 1;
  }

  std::string def = argv[1];
  std::string drv = argv[2];
  std::string out = argv[3];

  Grammar gra = Grammar(std::ifstream(def));
  gra.proccess_derivation_file(std::ifstream(drv), std::ofstream(out));

  return 0;
}