#include <iostream>

#ifndef OCCURENCE_H_
#define OCCURENCE_H_

class Occurence {
 public:
  enum Type { variable, statement, comment };

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
  std::string dump();

  //=================
  // GETTERS
  //=================

  /**
   * @brief Simple type getter.
   * @return The type of the occurence.
   */
  Type type();

  /**
   * @brief Simple info getter.
   * @return The info of the occurence.
   */
  std::string info();

  /**
   * @brief Simple ending_line getter.
   * @return The ending_line of the occurence.
   */
  int ending_line();

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
