#include "CppParser.h"

#include <fstream>

std::string kprogramNameLabel = "PROGRAM: ";
std::string kdescriptionLabel = "DESCRIPTION:\n";
std::string kdescriptionInfo = "DESCRIPTION";
std::string kvariablesLabel = "\nVARIABLES:\n";
std::string kstatementsLabel = "\nSTATEMENTS:\n";
std::string kmainLabel = "\nMAIN:\n";
std::string kcommentsLabel = "\nCOMMENTS:\n";

CppParser::CppParser(std::string filename) : filename_(filename) {
  occurences_.reserve(3);
};

void CppParser::read() {
  std::ifstream input_file(filename_);
  std::string line;

  bool has_main;
  int line_number = 1;
  int starting_line_number;

  std::string lines_acumulated;
  std::regex comment_start(R"(\/\*)");
  std::regex comment_end(R"(\*\/)");

  while (getline(input_file, line)) {
    has_main = false;

    if (std::regex_search(line, comment_start)) {
      starting_line_number = line_number;
      lines_acumulated = line;
      description_ = true;
    } else if (std::regex_search(line, comment_end) ||
               lines_acumulated.length() == 0) {
      // For every occurence that isn't multiline the starting line is reseted.
      if (lines_acumulated.length() == 0) starting_line_number = line_number;

      Occurence occurence = match_(lines_acumulated + "\n" + line,
                                   starting_line_number, line_number);
      has_main = match_main_(line);

      if (has_main) {
        main_ = true;
      } else if (occurence.info().length() > 0) {
        occurences_[occurence.type()].push_back(occurence);
      }

      lines_acumulated = "";
    } else if (lines_acumulated.length()) {
      lines_acumulated += "\n" + line;
    }

    line_number++;
  }
}

void CppParser::write(std::string output_filename) {
  std::ofstream output_file(output_filename);

  output_file << kprogramNameLabel << filename_ << std::endl;
  if (description_) {
    output_file << kdescriptionLabel
                << occurences_[Occurence::Type::comment][0].info() << std::endl;
  }

  output_file << kvariablesLabel << dump_occurences_(Occurence::Type::variable);
  output_file << kstatementsLabel
              << dump_occurences_(Occurence::Type::statement);
  output_file << kmainLabel << (main_ ? "True" : "False") << std::endl;
  output_file << kcommentsLabel << dump_occurences_(Occurence::Type::comment);
}

bool CppParser::match_main_(std::string line) {
  std::regex expression(R"(int main([^)]+))");
  return std::regex_search(line, expression);
}

Occurence CppParser::match_(std::string line, int start_line, int ending_line) {
  Occurence occurence(start_line, ending_line);

  std::regex variable(R"(\n[ ]*?((int)|(double)) [^=]+( =[^;]+)?;)");
  std::regex for_loop(R"(for \([^)]+\))");
  std::regex while_loop(R"(while \([^)]+\))");
  std::regex single_line_comment(R"(\/\/.*)");
  std::regex multi_line_comment(R"(\/\*)");

  if (std::regex_search(line, multi_line_comment)) {
    occurence.set_type(Occurence::Type::comment);
    occurence.set_info(line);
  } else if (std::regex_search(line, variable)) {
    // The type of the variable is extracted and stored in var_type to convert
    // it to upper case.
    std::regex var_type_regex("((int)|(double))");
    std::smatch var_type;
    std::regex_search(line, var_type, var_type_regex);

    // The definition or instantiation is also extracted, and appended to the
    // type.
    std::regex regex(R"((\n[ ]*?((int)|double) )|;)");
    std::string info = to_upper_case_(var_type[0].str()) + ": " +
                       std::regex_replace(line, regex, "");

    occurence.set_type(Occurence::Type::variable);
    occurence.set_info(info);
  } else if (std::regex_search(line, for_loop)) {
    occurence.set_type(Occurence::Type::statement);
    occurence.set_info("LOOP: for");
  } else if (std::regex_search(line, while_loop)) {
    occurence.set_type(Occurence::Type::statement);
    occurence.set_info("LOOP: while");
  } else if (std::regex_search(line, single_line_comment)) {
    occurence.set_type(Occurence::Type::comment);
    // Only will be stored as info what comes after the "//" in case the coment
    // is inline with code.
    occurence.set_info(line.substr(line.find("//")));
  }

  return occurence;
}

std::string CppParser::dump_occurences_(Occurence::Type type) {
  std::string output;

  for (int i = 0; i < occurences_[type].size(); i++) {
    if (type == Occurence::Type::comment && description_ && i == 0) {
      std::string temp = occurences_[type][i].dump();
      output += "[Line 1-" +
                std::to_string(occurences_[type][i].ending_line()) + "] " +
                kdescriptionInfo + "\n";
    } else {
      output += occurences_[type][i].dump() + "\n";
    }
  }

  return output;
}

std::string CppParser::to_upper_case_(std::string string) {
  std::string output;
  for (auto const& character : string) {
    output += toupper(character);
  }

  return output;
}
