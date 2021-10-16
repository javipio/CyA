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

class Language {
 public:
  Language();
  Language(std::vector<Chain> raw_language);
  int length() const;
  const Chain& operator[](int index) const;

 private:
  std::vector<Chain> language_;
};

std::ostream& operator<<(std::ostream& output_stream, const Language& language);
