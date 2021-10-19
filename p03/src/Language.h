/**
 * @author Javier Padilla Pío
 * @date 16/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 3 - Operaciones con cadenas y lenguajes.
 * Email: alu0101410463@ull.edu.es
 * Language.cc file: Language class contains the logic to operate with a
 * language. This file contains the interface of the class. References: Practice
 * statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/19541/mod_assign/introattachment/0/CyA_2021_2022_P2_Cadenas.pdf?forcedownload=1
 * Revision history:
 *                16/10/2021 - Creation (first version) of the code
 */

#include "Chain.h"

#ifndef LANGUAGE_H_
#define LANGUAGE_H_
class Language {
 public:
  Language();
  Language(std::vector<Chain> raw_language);
  /**
   * @brief Returns the length of the language.
   */
  int length() const;

  /**
   * @brief Operator to access individual chains of the language.
   */
  const Chain& operator[](int index) const;

  /**
   * @brief Appends a chain to the end of the language.
   */
  void push_back(Chain chain);

 private:
  std::vector<Chain> language_;
};

/**
 * @brief Operator to output to a stream.
 */
std::ostream& operator<<(std::ostream& output_stream, const Language& language);
#endif
