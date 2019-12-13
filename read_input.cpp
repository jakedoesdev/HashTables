//
//  read_input.cpp
//  Project 3
//

#include "read_input.h"
#include "parse_age.h"
#include "parse_disability.h"
#include "parse_geog.h"
#include "age.h"
#include "disability.h"
#include "geoTable.h"
#include <iostream>
#include <fstream>

//  ACCESSORS
std::vector<std::regex>& Input::getPatterns() {
  return this->m_patterns;
}

//  FUNCTIONS
//reads the input file and passes each line to its appropriate function to be processed
void Input::readFile(AgeData& t_age_data, DisabilityData& t_disability_data, GeographyData& t_geog_data,
                     ageTable& t_aT, Disability& t_dT, geoTable& t_gT) {
  std::ifstream infile; //processes filenames
  std::ifstream infile2;  //processes commands
  std::string filename; //stores the user-entered filename
  std::string temp; //stores contents of the file, line by line
  std::regex pattern; //stores patterns to match table names
  std::smatch matches;  //stores relevant matches from pattern
  
  std::cout << "Enter the input file name" << std::endl;
  std::cin >> filename;
  //both ifstreams open the same file, as it cannot be processed twice. During the first read, this function gets
  //table filenames. During the second read, it gets commands.
  infile.open(filename);
  infile2.open(filename);
  if(infile.is_open()) {
    //Gets filenames
    while(getline(infile, temp)) {
      if(std::regex_search(temp, matches, this->getPatterns()[0])) {
        temp = temp.substr(0, temp.find(" "));
        t_age_data.setFilename(temp);
      }
      if(std::regex_search(temp, matches, this->getPatterns()[1])) {
        temp = temp.substr(0, temp.find(" "));
        t_disability_data.setFilename(temp);
      }
      if(std::regex_search(temp, matches, this->getPatterns()[2])) {
        temp = temp.substr(0, temp.find(" "));
        t_geog_data.setFilename(temp);
      }
    }
    //the program then adds all of the data from the tables to each hash table
    this->readTables(t_age_data, t_disability_data, t_geog_data, t_aT, t_dT, t_gT);
    //gets commands from input file
    while(getline(infile2, temp)) {
      this->distributeData(t_age_data, t_disability_data, t_geog_data, t_aT, t_dT, t_gT, temp);
    }
  }
  else {
    std::cout << "Unable to open file" << std::endl;
  }
  infile.close();
  infile2.close();
} // readFile
//matches commands from the input file to a regular expression. These commands are then passed to their relevant
//functions.
void Input::distributeData(AgeData& t_age_data, DisabilityData& t_disability_data, GeographyData& t_geog_data,
                           ageTable& t_aT, Disability& t_dT, geoTable& t_gT,
                           std::string t_str) {
  std::regex pattern; //stores patterns to match commands
  std::smatch matches;  //stores relevent matches from pattern
  std::string command;  //stores a matched pattern
  std::string temp; //stores a matched pattern
  std::string table;  //stores a matched pattern
  
  //this loop cycles through every command pattern
  for(int i = 3; i < this->getPatterns().size(); i++) {
    pattern = this->getPatterns()[i]; //assigns pattern to patterns defined in the header file
    if(std::regex_search(t_str, matches, pattern)) {
      switch(i) {
        //cases 3-5 pass data to executeCommands, case 6 performs a print, and case 7 performs a write.
        case 3:
        {
          command = matches[1];
          temp = matches[2];
          table = matches[3];
          this->executeCommands(t_aT, t_dT, t_gT, command, temp, table);
          break;
        }
        case 4:
        {
          command = matches[1];
          temp = matches[2];
          table = matches[3];
          this->executeCommands(t_aT, t_dT, t_gT, command, temp, table);
          break;
        }
        case 5:
        {
          command = matches[1];
          temp = matches[2];
          table = matches[3];
          this->executeCommands(t_aT, t_dT, t_gT, command, temp, table);
          break;
        }
        case 6:
          this->display(t_aT, t_dT, t_gT);
          break;
        case 7:
          this->write(t_aT, t_dT, t_gT);
        default:
          break;
      }
    }
  }
} // distributeData
//inserts data from table files into their corresponding hash tables
void Input::readTables(AgeData& t_age_data, DisabilityData& t_disability_data, GeographyData& t_geog_data,
                       ageTable& t_aT, Disability& t_dT, geoTable& t_gT){
  std::string data; //stores data from table files
  std::ifstream infile; //processes the table file
  
  infile.open(t_age_data.getFilename());
  if(infile.is_open()) {
    //ignores first two lines
    getline(infile, data);
    getline(infile, data);
    //inserts all other lines into age hash table
    while(getline(infile, data)) {
      t_aT.insertAge(data, "age");
    }
  }
  else {
    std::cout << "Age data file not found" << std::endl;
  }
  infile.close();
  
  infile.open(t_disability_data.getFilename());
  if(infile.is_open()) {
    //ignores first two lines
    getline(infile, data);
    getline(infile, data);
    //inserts all other lines into disability hash table
    while(getline(infile, data)) {
      t_dT.insertData(data, "disability");
    }
  }
  else {
    std::cout << "Disability data file not found" << std::endl;
  }
  infile.close();
  
  infile.open(t_geog_data.getFilename());
  if(infile.is_open()) {
    //ignores first two lines
    getline(infile, data);
    getline(infile, data);
	
	std::cout << t_geog_data.getFilename() << " geography\n";
	
	std::cout << "Processing geography table.\n";
    //inserts all other lines into geography hash table
    while(getline(infile, data)) {
      t_gT.insertGeo(data, "geography");
    }
  }
  else {
    std::cout << "Geography data file not found" << std::endl;
  }
  infile.close();
} // readTables
//calls commands from the input file for each hash table
void Input::executeCommands(ageTable& t_aT, Disability& t_dT, geoTable& t_gT,
                            std::string t_command, std::string t_data, std::string t_table) {
  //AGE COMMANDS
  if(t_command == "INSERT" && t_table == "age") {t_aT.insertAge(t_data, t_table);}
  if(t_command == "UPDATE" && t_table == "age") {t_aT.updateAge(t_data, t_table);}
  if(t_command == "SELECT" && t_table == "age") {t_aT.selectAge(t_data, t_table);}
  if(t_command == "DELETE" && t_table == "age") {t_aT.deleteAge(t_data, t_table);}
  //DISABILITY COMMANDS
  if(t_command == "INSERT" && t_table == "disability") {t_dT.insertData(t_data, t_table);}
  if(t_command == "UPDATE" && t_table == "disability") {t_dT.updateData(t_data, t_table);}
  if(t_command == "SELECT" && t_table == "disability") {t_dT.selectData(t_data, t_table);}
  if(t_command == "DELETE" && t_table == "disability") {t_dT.deleteData(t_data, t_table);}
  //GEOGRAPHY COMMANDS
  if(t_command == "INSERT" && t_table == "geography") {t_gT.insertGeo(t_data, t_table);}
  if(t_command == "UPDATE" && t_table == "geography") {t_gT.updateGeo(t_data, t_table);}
  if(t_command == "SELECT" && t_table == "geography") {t_gT.selectGeo(t_data, t_table);}
  if(t_command == "DELETE" && t_table == "geography") {t_gT.deleteGeo(t_data, t_table);}
} // executeCommands
//prints data from all hash tables to the console
void Input::display(ageTable& t_aT, Disability& t_dT, geoTable& t_gT) {
  std::cout << "\nAge Data:\n";
  t_aT.displayAge();
  std::cout << "\nDisability Data:\n";
  t_dT.printDisability();
  std::cout << "\nGeography Data:\n";
  t_gT.displayGeo();
  std::cout << std::endl;
} // display
//saves a new table file from the data in each hash table
void Input::write(ageTable& t_aT, Disability& t_dT, geoTable& t_gT) {
  //Please heed this warning
  std::cout << "Saving data. Please do not remove disc or memory card, or progress may be lost.\n";
  
  std::ofstream age_out("age_save.csv");  //new file to store age data
  std::ofstream geog_out("geog_save.csv");  //new file to store geography data
  
  std::vector<ageLine> tmpAge = t_aT.getAgeTable(); //assigns tmpAge to a vector storing all age data
  age_out << "geo_geoid\n";
  age_out << "geo_geoid,under_5,under_18,over_65\n";
  //writes all data to age file
  for(int i = 0; i < tmpAge.size(); i++) {
    age_out << tmpAge[i].ageID << "," << tmpAge[i].UnderFive << "," << tmpAge[i].UnderEightTeen << "," <<
               tmpAge[i].OverSixtyFive << "\n";
  }
  
  t_dT.writeDisability(); //Zac made his own write function
  
  std::vector<geoLine> tmpGeo = t_gT.getGeoTable(); //assigns tmpGeo to a vector storing all geography data
  geog_out << "replan_id\n";
  geog_out << "replan_id,geo_name,geo_stusab,geo_sumlev,geo_state,geo_county,geo_geoid,population\n";
  //writes all data to geography file
  for (int i = 0; i < tmpGeo.size(); i++) {
    geog_out << tmpGeo[i].replanID << ",\"" << tmpGeo[i].geoName << "\"," << tmpGeo[i].geoStateAbb << "," <<
                tmpGeo[i].geoSumLev << "," << tmpGeo[i].geoState << "," << tmpGeo[i].geoCounty << "," <<
                tmpGeo[i].geoID << "," << tmpGeo[i].geoPop << "\n";
  }
  std::cout << "Save successful!\n";
}
