//
//  parse_geog.h
//  Project 3
//

#ifndef PARSE_GEOG_H
#define PARSE_GEOG_H

#include <string>
#include <vector>
#include <tuple>

//This class stores the geography table filename, data from the geography table,
//and commands pertaining to geography data.
class GeographyData {
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

#endif  // PARSE_GEOG_H
