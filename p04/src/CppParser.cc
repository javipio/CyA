#include "CppParser.h"

#include <fstream>

std::string kProgramNameLabel = "PROGRAM: ";
std::string kDescriptionLabel = "DESCRIPTION:\n";
std::string kDescriptionInfo = "DESCRIPTION";
std::string kVariablesLabel = "\nVARIABLES:\n";
std::string kStatementsLabel = "\nSTATEMENTS:\n";
std::string kMainLabel = "\nMAIN:\n";
std::string kCommentsLabel = "\nCOMMENTS:\n";

CppParser::CppParser(std::string filename) : filename_(filename) {
  occurences_.reserve(4);
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
      // A multiline comment has been detected, so the starting line index will
      // be stored as well as the preceding lines.
      starting_line_number = line_number;
      lines_acumulated = line + "\n";
      if (line_number == 0) description_ = true;
    } else if (std::regex_search(line, comment_end) ||
               lines_acumulated.length() == 0) {
      // For every occurence that isn't multiline the starting line is reseted.
      if (lines_acumulated.length() == 0) starting_line_number = line_number;

      auto type = match_(lines_acumulated + line);
      has_main = match_main_(line);

      if (has_main) {
        main_ = true;
      } else if (type != Occurence::Type::noneType) {  // Match
        std::string info = extract_info(lines_acumulated + line, type);
        Occurence occurence(starting_line_number, line_number, type, info);
        occurences_[type].push_back(occurence);
      }

      lines_acumulated = "";
    } else if (lines_acumulated.length()) {
      // Keep storing lines as the termination of the multiline comment hasn't
      // been found yet.
      lines_acumulated += line + "\n";
    }

    line_number++;
  }
}

void CppParser::write(std::ostream& output_stream) const {
  output_stream << kProgramNameLabel << filename_ << std::endl;

  if (description_) {
    const auto kDescription = occurences_[Occurence::Type::multiline_comment];
    output_stream << kDescriptionLabel << kDescription[0].info() << std::endl;
  }

  output_stream << kVariablesLabel
                << dump_occurences_(Occurence::Type::variable);
  output_stream << kStatementsLabel
                << dump_occurences_(Occurence::Type::statement);
  output_stream << kMainLabel << (main_ ? "True" : "False") << std::endl;
  output_stream << kCommentsLabel
                << dump_occurences_(Occurence::Type::multiline_comment)
                << dump_occurences_(Occurence::Type::comment);
}

bool CppParser::match_main_(std::string line) const {
  std::regex expression(R"(int main\(([^)]+)?\))");
  return std::regex_search(line, expression);
}

Occurence::Type CppParser::match_(std::string line) const {
  std::regex variable(R"(^[ ]*?((int)|(double)) [^=]+( =[^;]+)?;)");
  std::regex for_loop(R"(for \([^)]+\))");
  std::regex while_loop(R"(while \([^)]+\))");
  std::regex single_line_comment(R"(\/\/.*)");
  std::regex multi_line_comment(R"(\/\*)");

  if (std::regex_search(line, multi_line_comment)) {
    return Occurence::Type::multiline_comment;
  } else if (std::regex_search(line, variable)) {
    return Occurence::Type::variable;
  } else if (std::regex_search(line, for_loop)) {
    return Occurence::Type::statement;
  } else if (std::regex_search(line, while_loop)) {
    return Occurence::Type::statement;
  } else if (std::regex_search(line, single_line_comment)) {
    return Occurence::Type::comment;
  }

  return Occurence::Type::noneType;
}

std::string CppParser::extract_info(std::string line,
                                    Occurence::Type type) const {
  switch (type) {
    case Occurence::Type::variable: {
      // The type of the variable is extracted and stored in var_type to convert
      // it to upper case.
      std::regex var_type_regex("((int)|(double))");
      std::smatch var_type;
      std::regex_search(line, var_type, var_type_regex);

      // The definition or instantiation is also extracted, and appended to the
      // type.
      std::regex regex(R"(([ ]*?((int)|double) )|;)");
      std::string info = to_upper_case_(var_type[0].str()) + ": " +
                         std::regex_replace(line, regex, "");
      return info;
    }
    case Occurence::Type::comment:
      return line.substr(line.find("//"));
    case Occurence::Type::multiline_comment:
      return line;
    case Occurence::Type::statement: {
      if (line.find("while") != std::string::npos) {
        return "LOOP: while";
      }
      return "LOOP: for";
    }
    default:
      throw std::invalid_argument("WTF");
  }
}

std::string CppParser::dump_occurences_(Occurence::Type type) const {
  std::string output;

  int i = 0;

  for (auto const& occurence : occurences_[type]) {
    if (type == Occurence::Type::multiline_comment && description_ && i == 0) {
      std::string temp = occurence.dump();
      output += "[Line 1-" + std::to_string(occurence.ending_line()) + "] " +
                kDescriptionInfo + "\n";
    } else {
      output += occurence.dump() + "\n";
    }
    i++;
  }

  return output;
}

std::string CppParser::to_upper_case_(std::string string) const {
  std::string output;
  for (auto const& character : string) {
    output += toupper(character);
  }

  return output;
}
