#include <iostream>
#include <regex>
#include <vector>

#include "Occurence.h"

#ifndef INGEST_H_
#define INGEST_H_

class CppParser {
 public:
  CppParser(std::string filename);

  /**
   * @brief Reads and stores the information from the given c++ file.
   * @return None.
   */
  void read();

  /**
   * @brief Dumps the formated information to the output file.
   * @param[in] output_filename Name of the output file.
   * @return None.
   */
  void write(std::string output_filename);

 private:
  /**
   * @brief Checks if main definition exists in a string.
   * @param[in] line String in where main will be searched.
   * @return If exists.
   */
  bool match_main_(std::string line);

  /**
   * @brief Checks if there is important information (variables, statements or
   * comments) in a string.
   * @param[in] line String in where main will be searched.
   * @param[in] start_line Index of the starting line.
   * @param[in] start_line Index of the ending line.
   * @return Returns an instance of Occurence with all the information of the
   * match.
   */
  Occurence match_(std::string line, int start_line, int ending_line);

  /**
   * @brief Converts all occurences of a given type to a human readable string
   * ir order to dump it to an output file.
   * @param[in] type type of the occurences to dump.
   * @return Container with the extracted information.
   */
  std::string dump_occurences_(Occurence::Type type);

  /**
   * @brief Converts a string to upper case.
   * @param[in] string Lower case string to convert.
   * @return Processed string.
   */
  std::string to_upper_case_(std::string string);

  std::string filename_;
  bool description_;
  std::vector<std::vector<Occurence>> occurences_;
  /**
   * occurences_ positions:
   *     - Occurence::Type::variable(0) -> variables
   *     - Occurence::Type::statements(1) -> statements
   *     - Occurence::Type::comments(2) -> comments
   */
  bool main_;
};
#endif
