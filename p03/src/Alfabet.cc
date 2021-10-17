/**
 * @author Javier Padilla Pío
 * @date 16/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 3 - Operaciones con cadenas y lenguajes.
 * Email: alu0101410463@ull.edu.es
 * Alfabet.cc file: Alfabet class is the data structure used to store all the
 *                 simbols of an alfabet.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/19541/mod_assign/introattachment/0/CyA_2021_2022_P2_Cadenas.pdf?forcedownload=1
 * Revision history:
 *                16/10/2021 - Creation (first version) of the code
 */

#include "Alfabet.h"

Alfabet::Alfabet(std::vector<std::string> raw_alfabet) {
  for (const auto simbol : raw_alfabet) {
    alfabet_.insert(Simbol(simbol));
  }
}

bool Alfabet::simbol_exists(const Simbol& needle) {
  for (const auto simbol : alfabet_) {
    if (simbol.get() == needle.get()) return true;
  }
  return false;
}
