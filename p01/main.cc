#include <iostream>
#include "erathostenes.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Faltan parámetros" << std::endl;
        return 1;
    }

    Erathostenes erathostenes(std::atoi(argv[1]));
    erathostenes.Sieve();
    erathostenes.Clean();
    erathostenes.Info();

    return 0;
}
