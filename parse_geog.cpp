//
//  parse_geog.cpp
//  Project 3
//

#include "parse_geog.h"

//  MUTATORS
void GeographyData::setFilename(std::string t_filename) {
  this->m_filename = t_filename;
}
//  ACCESSORS
std::string GeographyData::getFilename() const {
  return this->m_filename;
}
std::vector<std::string>& GeographyData::getData() {
  return this->m_data;
}
std::vector<std::tuple<std::string, std::string>>& GeographyData::getCommands() {
  return this->m_commands;
}
