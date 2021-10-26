/**
 * @author Javier Padilla Pío
 * @date 23/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 4 - Expresiones regulares.
 * Email: alu0101410463@ull.edu.es
 * CppParser.h file: Occurence class is in charge of storing each individual
 *                   piece of information. This file contains the
 *                   implementation of the class.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/20389/mod_assign/introattachment/0/CyA_2021_2022_P04_ExpresionesRegulares.pdf?forcedownload=1
 * Revision history:
 *                23/10/2021 - Creation (first version) of the code
 */

#include <iostream>

#ifndef OCCURENCE_H_
#define OCCURENCE_H_

class Occurence {
 public:
  enum Type {
    variable,
    statement,
    comment,
    multiline_comment,
    include,
    noneType
  };

  Occurence();
  Occurence(int starting_line, int ending_line);
  Occurence(int starting_line, int ending_line, Type type, std::string info);

  /**
   * @brief Returns the content of the occurence as a string following the
   * structure:
   *     - [Line 0-10] info
   * In case the starting_line and ending_line are equal, only one will be
   * displayed in the form:
   *     - [Line 0] info
   * @return Parsed string with all the information.
   */
  std::string dump() const;

  //=================
  // GETTERS
  //=================

  /**
   * @brief Simple type getter.
   * @return The type of the occurence.
   */
  Type type() const;

  /**
   * @brief Simple info getter.
   * @return The info of the occurence.
   */
  std::string info() const;

  /**
   * @brief Simple ending_line getter.
   * @return The ending_line of the occurence.
   */
  int ending_line() const;

  //=================
  // SETTERS
  //=================

  /**
   * @brief Simple type setter.
   * @param[in] type Future value for type_.
   * @return None.
   */
  void set_type(Type type);

  /**
   * @brief Simple info setter.
   * @param[in] info Future value for info_.
   * @return None.
   */
  void set_info(std::string info);

 private:
  int starting_line_;
  int ending_line_;
  Type type_;
  std::string info_;
};
#endif
