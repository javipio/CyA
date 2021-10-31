
#include <fstream>
#include <iostream>

#include "Dfa.h"
int main(int argc, char* argv[]) {
  if (argc == 2) {
    std::string input_file = argv[1];

    if (input_file == "--help" || input_file == "-h") {
      std::cout << "Usage: " << argv[0] << "DEFINITION CHAIN DEST\n";
      std::cout << "Reads a file containing the formal definition of the DFA "
                   "from DEFINITION, then cheks for subsequences in CHAIN and "
                   "stores them in DEST"
                << std::endl;
      return 0;
    }
  }

  if (argc < 4) {
    std::cout << argv[0] << ": missing operand\n";
    std::cout << "Try '" << argv[0] << " --help' for mor information."
              << std::endl;
    return 1;
  }

  std::string input_filename = argv[1];
  std::string pattern = argv[2];
  std::string output_filename = argv[3];
  std::ifstream input_file(input_filename);

  Dfa dfa(input_file);
  input_file.close();
  dfa.run(pattern);

  std::ofstream output_file(output_filename);
  output_file << dfa.dump();
  output_file.close();

  return 0;
}