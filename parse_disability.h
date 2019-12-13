//
//  parse_disability.h
//  Project 3
//

#ifndef PARSE_DISABILITY_H
#define PARSE_DISABILITY_H

#include <string>
#include <vector>
#include <tuple>

//This class stores the disability table filename, data from the disability table,
//and commands pertaining to disability data.
class DisabilityData {
 private:
  std::string m_filename; //stores filename for the geography table
  std::vector<std::string> m_data;  //stores data from the geography table
  std::vector<std::tuple<std::string, std::string>> m_commands; //stores commands from the input file
 public:
  //  MUTATORS
  void setFilename(std::string t_filename);
  //  ACCESSORS
  std::string getFilename() const;
  std::vector<std::string>& getData();
  std::vector<std::tuple<std::string, std::string>>& getCommands();
};

#endif  // PARSE_DISABILITY_H
