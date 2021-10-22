#include "CppParser.h"

int main(int argc, char* argv[]) {
  if (argc == 2 && (argv[1] == "--help" | argv[1] == "-h")) {
    return 0;
  }

  if (argc < 3) {
    return 1;
  }

  CppParser parser(argv[1]);
  parser.read();
  parser.write(argv[2]);

  return 0;
}