#include <fstream>

#include "CppParser.h"

int main(int argc, char* argv[]) {
  if (argc == 2) {
    std::string input_file = argv[1];

    if (input_file == "--help" || input_file == "-h") {
      std::cout << "Usage: " << argv[0] << "SOURCE DEST\n";
      std::cout
          << "Reads a '.cc' or '.cpp' file (SOURCE), extracts some useful "
             "information and stores it to DEST"
          << std::endl;
      return 0;
    }
  }

  if (argc < 3) {
    std::cout << argv[0] << ": missing file operand\n";
    std::cout << "Try '" << argv[0] << " --help' for mor information."
              << std::endl;
    return 1;
  }

  CppParser parser(argv[1]);
  parser.read();

  std::ofstream output_file(argv[2]);
  parser.write(output_file);
  output_file.close();

  return 0;
}
