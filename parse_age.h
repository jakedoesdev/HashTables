//
//  parse_age.h
//  Project 3
//

#ifndef PARSE_AGE_H
#define PARSE_AGE_H

#include <string>
#include <vector>
#include <tuple>

//This class stores the age table filename, data from the age table,
//and commands pertaining to age data.
class AgeData {
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

#endif // PARSE_AGE_H
