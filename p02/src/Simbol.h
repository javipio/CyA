/**
 * @author Javier Padilla Pío
 * @date 09/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 2 - Símbolos alfabetos y cadenas.
 * Email: alu0101410463@ull.edu.es
 * Simbol.h file: Simbol class is the atomic element of a chain or alfabet.
 *                 This file contains the interface of the class.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/19541/mod_assign/introattachment/0/CyA_2021_2022_P2_Cadenas.pdf?forcedownload=1
 * Revision history:
 *                09/10/2021 - Creation (first version) of the code
 */

#include <iostream>

#ifndef SIMBOL_H
#define SIMBOL_H
class Simbol {
 public:
  Simbol(std::string value);
  Simbol(char value);
  const std::string get() const;

 private:
  std::string value_;
};
#endif
