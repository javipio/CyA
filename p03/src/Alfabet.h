/**
 * @author Javier Padilla Pío
 * @date 16/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 3 - Operaciones con cadenas y lenguajes.
 * Email: alu0101410463@ull.edu.es
 * Alfabet.h file: Alfabet class is the data structure used to store all the
 *                 simbols of an alfabet.
 *                 This file contains the interface of the class.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/19541/mod_assign/introattachment/0/CyA_2021_2022_P2_Cadenas.pdf?forcedownload=1
 * Revision history:
 *                16/10/2021 - Creation (first version) of the code
 */

#include <set>
#include <vector>

#include "Simbol.h"

#ifndef ALFABET_H_
#define ALFABET_H_
class Alfabet {
 public:
  Alfabet() {}
  Alfabet(std::vector<std::string> raw_alfabet);

  /**
   * @brief Checks if a simbol exists in an alfabet.
   */
  bool simbol_exists(const Simbol& needle);

 private:
  std::set<Simbol> alfabet_;
};
#endif
