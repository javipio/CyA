#include <fstream>
#include <iostream>

#include "KP.h"

int main(int argc, char* argv[]) {
  if (argc < 3) {
    return 1;
  }

  bool bounded = true;
  float max_weight;
  std::string filename;

  if (argc == 4 && std::string(argv[1]) == "-u") {
    bounded = false;
    max_weight = atoi(argv[2]);
    filename = argv[3];
  } else {
    max_weight = atoi(argv[1]);
    filename = argv[2];
  }

  std::ifstream config_file(filename);
  KP solver(max_weight, config_file);

  if (bounded) {
    std::cout << "Bounded:\n";
    solver.SolveBounded();
  } else {
    std::cout << "Unbounded:\n";
    solver.SolveUnBounded();
  }
  return 0;
}
