/**
 * @author Javier Padilla Pío
 * @date 16/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 3 - Operaciones con cadenas y lenguajes.
 * Email: alu0101410463@ull.edu.es
 * Simbol.h file: Simbol class is the atomic element of a chain or alfabet.
 *                 This file contains the interface of the class.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/19541/mod_assign/introattachment/0/CyA_2021_2022_P2_Cadenas.pdf?forcedownload=1
 * Revision history:
 *                16/10/2021 - Creation (first version) of the code
 */

#include <iostream>

#ifndef SIMBOL_H_
#define SIMBOL_H_
class Simbol {
 public:
  Simbol();
  Simbol(std::string value);
  Simbol(char value);

  /**
   * @brief Returns the value of the simbol.
   */
  const std::string get() const;

 private:
  std::string value_;
};
#endif

/**
 * @brief Operator to compare if simbol_1 is subchain of simbol_2.
 */
bool operator<(Simbol const& simbol_1, Simbol const& simbol_2);

/**
 * @brief Operator to compare if simbol_1 is subchain of simbol_2.
 */
bool operator>(Simbol const& simbol_1, Simbol const& simbol_2);
