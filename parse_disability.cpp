//
//  parse_disability.cpp
//  Project 3
//

#include "parse_disability.h"

//  MUTATORS
void DisabilityData::setFilename(std::string t_filename) {
  this->m_filename = t_filename;
}
//  ACCESSORS
std::string DisabilityData::getFilename() const {
  return this->m_filename;
}
std::vector<std::string>& DisabilityData::getData() {
  return this->m_data;
}
std::vector<std::tuple<std::string, std::string>>&
DisabilityData::getCommands() {
  return this->m_commands;
}
