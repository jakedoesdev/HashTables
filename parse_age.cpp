//
//  parse.cpp
//  Project 3
//

#include "parse_age.h"

//  MUTATORS
void AgeData::setFilename(std::string t_filename) {
  this->m_filename = t_filename;
}
//  ACCESSORS
std::string AgeData::getFilename() const {
  return this->m_filename;
}
std::vector<std::string>& AgeData::getData() {
  return this->m_data;
}
std::vector<std::tuple<std::string, std::string>>& AgeData::getCommands() {
  return this->m_commands;
}
