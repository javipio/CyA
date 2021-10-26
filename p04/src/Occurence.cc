/**
 * @author Javier Padilla Pío
 * @date 23/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 4 - Expresiones regulares.
 * Email: alu0101410463@ull.edu.es
 * Occurence.cc file: Occurence class is in charge of storing each individual
 *                    piece of information. This file contains the
 *                    implementation of the class.
 * References: Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/20389/mod_assign/introattachment/0/CyA_2021_2022_P04_ExpresionesRegulares.pdf?forcedownload=1
 * Revision history:
 *                23/10/2021 - Creation (first version) of the code
 */

#include "Occurence.h"

Occurence::Occurence() = default;

Occurence::Occurence(int start_line, int end_line)
    : starting_line_(start_line), ending_line_(end_line) {}

Occurence::Occurence(int starting_line, int ending_line, Occurence::Type type,
                     std::string info)
    : starting_line_(starting_line),
      ending_line_(ending_line),
      type_(type),
      info_(info) {}

Occurence::Type Occurence::type() const { return type_; }

std::string Occurence::info() const { return info_; }

int Occurence::ending_line() const { return ending_line_; }

std::string Occurence::dump() const {
  std::string output = "[Line " + std::to_string(starting_line_);

  if (starting_line_ != ending_line_) {
    output += "-" + std::to_string(ending_line_);
  }

  output += "] " + info_;
  return output;
}

void Occurence::set_type(Occurence::Type type) { type_ = type; }

void Occurence::set_info(std::string info) { info_ = info; }
