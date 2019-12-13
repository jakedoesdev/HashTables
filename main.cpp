//
//  main.cpp
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

int main() {
  //Objects for parsing declaration
  Input input;
  AgeData age_data;
  DisabilityData disability_data;
  GeographyData geog_data;
  
  //Table declaration
  ageTable aT;
  geoTable gT;
  Disability dT;
  
  input.readFile(age_data, disability_data, geog_data, aT, dT, gT);
  std::cout << "Processing complete!" << std::endl;
  

  return 0;
}
