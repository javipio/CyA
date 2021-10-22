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
   */
  std::string dump();

  //=================
  // GETTERS
  //=================

  /**
   * @brief Returns the type of the occurence.
   */
  Type type();

  /**
   * @brief Returns the info of the occurence.
   */
  std::string info();

  /**
   * @brief Returns the ending_line of the occurence.
   */
  int ending_line();

  //=================
  // SETTERS
  //=================

  /**
   * @brief Updates the value of type_ with the given parameter.
   * @param[in] type Future value for type_.
   */
  void set_type(Type type);

  /**
   * @brief Updates the value of info_ with the given parameter.
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
