//
//  read_input.h
//  Project 3
//

#ifndef READ_INPUT_H
#define READ_INPUT_H

#include <string>
#include <vector>
#include <regex>

//FORWARD DECLARATIONS
class AgeData;
class DisabilityData;
class GeographyData;
class ageTable;
class geoTable;
class Disability;

//This class contains all the data and functions that parse data from the tables, parse data ffrom the input files,
//printing data to the console, and writing processed data to new files.
class Input {
 private:
  //stores all of the regular expression patterns needed to parse data from input files and table files
  std::vector<std::regex> m_patterns {
    std::regex("age$"), std::regex("disability$"), std::regex("geography$"),
    std::regex("(INSERT|UPDATE|SELECT|DELETE)\\(\\((.+)\\),(age)\\)"),
    std::regex("(INSERT|UPDATE|SELECT|DELETE)\\(\\((.+)\\),(disability)\\)"),
    std::regex("(INSERT|UPDATE|SELECT|DELETE)\\(\\((.+)\\),(geography)\\)"),
    std::regex("DISPLAY\\(\\)"), std::regex("WRITE\\(\\)")
  };
 public:
  //  ACCESSORS
  std::vector<std::regex>& getPatterns();
  //  FUNCTIONS
  //reads the input file and passes each line to its appropriate function to be processed
  void readFile(AgeData& t_age_data, DisabilityData& t_disability_data, GeographyData& t_geog_data,
                ageTable& t_aT, Disability& t_dT, geoTable& t_gT);
  //matches commands from the input file to a regular expression. These commands are then passed to their relevant
  //functions.
  void distributeData(AgeData& t_age_data, DisabilityData& t_disability_data, GeographyData& t_geog_data,
                      ageTable& t_aT, Disability& t_dT, geoTable& t_gT,
                      std::string);
  //inserts data from table files into their corresponding hash tables
  void readTables(AgeData& t_age_data, DisabilityData& t_disability_data, GeographyData& t_geog_data,
                  ageTable& t_aT, Disability& t_dT, geoTable& t_gT);
  //calls commands from the input file for each hash table
  void executeCommands(ageTable& t_aT, Disability& t_dT, geoTable& t_gT,
                       std::string t_command, std::string t_data, std::string t_table);
  //prints data from all hash tables to the console
  void display(ageTable& t_aT, Disability& t_dT, geoTable& t_gT);
  //saves a new table file from the data in each hash table
  void write(ageTable& t_aT, Disability& t_dT, geoTable& t_gT);
};

#endif  // READ_INPUT_H
