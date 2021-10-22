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
  void write(std::ostream& output_stream) const;

 private:
  /**
   * @brief Checks if main definition exists in a string.
   * @param[in] line String in where main will be searched.
   * @return If exists.
   */
  bool match_main_(std::string line) const;

  /**
   * @brief Checks if there is important information (variables, statements or
   * comments) in a string.
   * @param[in] line String in where main will be searched.
   * @return Returns the type of whatever it found or Occurence::Type::noneType.
   */
  Occurence::Type match_(std::string line) const;

  /**
   * @brief Retrieves the information of a string knowing the type.
   * @param[in] line String in which it will search.
   * @param[in] type Information type.
   */
  std::string extract_info(std::string line, Occurence::Type type) const;

  /**
   * @brief Converts all occurences of a given type to a human readable string
   * ir order to dump it to an output file.
   * @param[in] type type of the occurences to dump.
   * @return Container with the extracted information.
   */
  std::string dump_occurences_(Occurence::Type type) const;

  /**
   * @brief Converts a string to upper case.
   * @param[in] string Lower case string to convert.
   * @return Processed string.
   */
  std::string to_upper_case_(std::string string) const;

  int variables_length() const;

  int statements_length() const;

  int comments_length() const;

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
