#include <iostream>
#include <iomanip>
#include <regex>
#include "geoTable.h"

std::regex geoTable::getQueryPattern()
{
  return this->queryPattern;
}

std::regex geoTable::getInsertPattern()
{
  return this->insertPattern;
}

/*
geoHash - modulo hashing
Given an integer key value, geoHash will return (key mod table size).
*/
int geoTable::geoHash(int key)
{
  int size = geoTable.size();
  return key % size;
}

/*
Given a comma delimited string representing data to be inserted and the string "geography",
insertGeo() will parse data with regex into groups, then store those groups in the corresponding geoLine variable
geoHash is called on the key (replanID), then the table is linearly probed until an empty index location is found
*/
void geoTable::insertGeo(std::string data, std::string table)
{
  if (table != "geography")
  {
    std::cout << "Error, you have attempted to insert non-geography data into geography table." << std::endl;
  }
  else
  {
    std::smatch matcher;
    int index = 0;
    int probe = 0;
    bool done = false;
    geoLine gL;
    
    geoLine *gP = new geoLine;
    
    //parse string data tuple
    std::regex_search(data, matcher, this->getInsertPattern());
    
    //set all values for geoLine object from regex matcher groups
    gL.replanID = stoi(matcher[1].str());
    gL.geoName = matcher[2].str();
    gL.geoStateAbb = matcher[3].str();
    gL.geoSumLev = stoi(matcher[4].str());
    gL.geoState = stoi(matcher[5].str());
    gL.geoCounty = stoi(matcher[6].str());
    gL.geoID = matcher[7].str();
    gL.geoPop = stoi(matcher[8].str());
    
    //call hash function on replanID key and store in index
    index = this->geoHash(gL.replanID);
    
    //while not inserted
    //add the number of times probed to index
    //if the location's replanID still has its initialized value (-2), insert to that location
    //else increment probe, add to index, and repeat
    if (!(this->keyExists(gL.replanID)))
    {
      while (!done)
      {
        index = index+probe;
        
        if (this->geoTable[index].replanID == -2)
        {
          //std::cout << "Found open bucket." << std::endl;
          
          this->geoTable[index] = gL;
          
          //add pointer to this geoLine object to secondary index
          //*gP = gL;
          gP = &this->geoTable[index];
          this->geoList.addNode(gP);
          
          
          done = true;
          std::cout << "Inserted (" << data << ") into " << table << std::endl;
        }
        else
        {
          //std::cout << "COLLISION!!!!!!!!!!\n";
          probe++;
        }
      }
    }
    else
    {
      std::cout << "Failed to insert (" << data << ") into " << table << std::endl;
    }
  }
}

/*
Given a comma delimited string of data and "geography" table name, updateGeo will parse data with regex,
store the return groups in a geoLine object, check for the existence of the key in the table,
then update the data and output the information to the user.
If no matching key is found, will output that info to the user.
*/
void geoTable::updateGeo(std::string data, std::string table)
{
  if (table != "geography")
  {
    std::cout << "Error, you have attempted to update non-geography data with a geography table function." << std::endl;
  }
  else
  {
    std::smatch matcher;
    int index;
    bool done = false;
    //geoLine gL;
    

    //parse data
    std::regex_search(data, matcher, this->getInsertPattern());
  
    //iterate through table
    //if key is found, update data
    for (int i = 0; i < this->geoTable.size(); i++)
    {
      if (this->geoTable[i].replanID == stoi(matcher[1].str()))
      {
        this->geoTable[i].geoName = matcher[2].str();
        this->geoTable[i].geoStateAbb = matcher[3].str();
        this->geoTable[i].geoSumLev = stoi(matcher[4].str());
        this->geoTable[i].geoState = stoi(matcher[5].str());
        this->geoTable[i].geoCounty = stoi(matcher[6].str());
        this->geoTable[i].geoID = matcher[7].str();
        this->geoTable[i].geoPop = stoi(matcher[8].str());
        
        done = true;
        std::cout << "Updated (" << data << ") in " << table << std::endl;
      }
    }
    
    //if no matching key was found
    if (!done)
    {
      std::cout << "Failed to update (" << data << ") in " << table << std::endl;
    }
  }
}

//**********************************************************************************************FIXME
void geoTable::selectGeo(std::string data, std::string table)
{
  std::smatch matcher;
  bool found = false;
  
  std::regex_search(data, matcher, this->getQueryPattern());
  
  if (matcher[1].str() == "*")
  {
      
    std::cout << "Found entries:\n";
    this->geoList.selectNode(matcher);
      
  }
  else
  {
    for (auto it = this->geoTable.begin(); it != this->geoTable.end(); it++)
    {
      if (it->replanID == stoi(matcher[1].str()))
      {
        std::cout << "Found (" << data << ") in " << table << std::endl;
        found = true;
      }
    }
    if (!found)
    {
      std::cout << "No entries match query (" << data << ") in " << table << std::endl;
    }
  }
  
}



void geoTable::deleteGeo(std::string data, std::string table)
{
  std::smatch matcher;
  bool found = false;
  
  std::regex_search(data, matcher, this->getQueryPattern());
  
  if (matcher[1].str() == "*")
  {
      
    std::cout << "Deleted entries:\n";
    
    for (int i = 0; i < this->geoList.size; i++)
    {
      this->geoList.removeNode(matcher);

    }
  }
  else
  {
    for (auto it = this->geoTable.begin(); it != this->geoTable.end(); it++)
    {
      if (it->replanID == stoi(matcher[1].str()))
      {
        it->replanID = -1;
        it->geoName = "";
        it->geoStateAbb = "";
        it->geoSumLev = 0;
        it->geoState = 0;
        it->geoCounty = 0;
        it->geoID = "";
        it->geoPop = 0;
        
        std::cout << "Deleted (" << data << ") in " << table << std::endl;
      }
    }
    if (!found)
    {
      std::cout << "Failed to delete (" << data << ") in " << table << std::endl;
    }
  }
}



/*
displayGeo() outputs the schema for the geography data, then calls displayLine() for each table index that contains data
*/
void geoTable::displayGeo()
{
  std::cout << std::left << std::setw(10) << "replan_id" << std::setw(45) << "geo_name" << std::setw(11) << "geo_stusab" << std::setw(11) << "geo_sumlev" << std::setw(10) << "geo_state" << std::setw(11) << "geo_county" << std::setw(13) << "geo_geoid" << std::setw(10) << "population" << std::endl;
  
  for (auto it = this->geoTable.begin(); it != this->geoTable.end(); it++)
  {
    //replanID is initialized to -2, and set to -1 as a tombstone value
    if (it->replanID != -1 && it->replanID != -2)
    {
      it->displayLine();
    }
  }
}

/*
displayLine() outputs one line of geoTable data, formatted to match the geography schema
*/
void geoLine::displayLine()
{
  std::cout << std::left << std::setw(10) << this->replanID << std::setw(45) << this->geoName << std::setw(11) << this->geoStateAbb << std::setw(11) << this->geoSumLev << std::setw(10) << this->geoState << std::setw(11) << this->geoCounty << std::setw(13) << this->geoID << std::setw(10) << this->geoPop << std::endl;
}

/*
Given a key (replanID), keyExists iterates through the table and return true if a matching ID is found
used by insert function to prevent insertion of duplicate data
*/
bool geoTable::keyExists(int key)
{
  bool exists = false;
  
  for (auto it = this->geoTable.begin(); it != this->geoTable.end(); it++)
  {
    if (key == it->replanID)
    {
      exists = true;
    }
  }
  
  return exists;
}

//Returns a vector of geoLine structs to be used for write function
std::vector<geoLine> geoTable::getGeoTable()
{
  std::vector<geoLine> gT;
  geoLine tmpGL;
  for (int i = 0; i < geoTable.size(); i++)
  {
    if (geoTable[i].replanID != -2 && geoTable[i].replanID != -1)
    {
      tmpGL.replanID = geoTable[i].replanID;
      tmpGL.geoName = geoTable[i].geoName;
      tmpGL.geoStateAbb = geoTable[i].geoStateAbb;
      tmpGL.geoSumLev = geoTable[i].geoSumLev;
      tmpGL.geoState = geoTable[i].geoState;
      tmpGL.geoCounty = geoTable[i].geoCounty;
      tmpGL.geoID = geoTable[i].geoID;
      tmpGL.geoPop = geoTable[i].geoPop;
      gT.push_back(tmpGL);
    }
  }
  return gT;
}

//********************************************************LIST******************************************************************

void geoTable::List::selectNode(std::smatch findme)
{
  
  Node* curr = head;
  bool output = false;
  
  while (curr != NULL)
  {
    bool found = false;
    
    for (int i = 1; i < findme.size(); i++)
    {
      if (findme[i].str() != "*" && curr->data->replanID != -1)
      {
        switch(i) {
          case 2:
            if (findme[i].str() == curr->data->geoName)
            {
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          case 3:
            if (findme[i].str() == curr->data->geoStateAbb)
            {
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          case 4:
            if (stoi(findme[i].str()) == curr->data->geoSumLev)
            {
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          case 5:
            if (stoi(findme[i].str()) == curr->data->geoState)
            {
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          case 6:
            if (stoi(findme[i].str()) == curr->data->geoCounty)
            {
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          case 7:
            if (findme[i].str() == curr->data->geoID)
            {
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          case 8:
            if (stoi(findme[i].str()) == curr->data->geoPop)
            {
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          default:
            break;
      
        }
      }
    }
  
    if (found)
    {
      std::cout << "(" << curr->data->replanID << "," << curr->data->geoName << "," << curr->data->geoStateAbb << "," << curr->data->geoSumLev << "," << curr->data->geoState
      << "," << curr->data->geoCounty << "," << curr->data->geoID << "," << curr->data->geoPop << ") in geography\n";
      output = true;
    }
    
    curr = curr->next;
  }
  
  if (!output)
  {
    std::cout << "No entries matching (" << findme[0].str() << ") found in geography\n";
  }
}

//
void geoTable::List::addNode(geoLine* data)
//void geoTable::insert(geoLine* data)
{
  //std::cout << "inserting: " << data->replanID << std::endl;
  
  Node* n = new Node;  //new node
  n->data = data;        //set new node data member equal to geoLine* data parameter
  //n->next = this->head;  //set next for this node equal to head for this node
  n->next = NULL;
  
  //std::cout << n->data->replanID << std::endl;
  
  // if (head != NULL)
  // {
    // std::cout << "head is " << head->data->replanID << std::endl;
    // std::cout << "tail is " << tail->data->replanID << std::endl;
  // }
  if (head == NULL)
  {
    //std::cout << "head is NULL" << std::endl;
    head = n;
    tail = head;
    //head->next = tail;
  }
  else
  {
    //n->next = NULL;
    tail->next = n;
    tail = tail->next;
    //tail = n;
    
    //std::cout << "head is " << head->data->replanID << std::endl;
  }
  
  size++;
  
}

void geoTable::List::displayList()
{
  std::cout << std::left << std::setw(10) << "replan_id" << std::setw(45) << "geo_name" << std::setw(11) << "geo_stusab" << std::setw(11) << "geo_sumlev"
  << std::setw(10) << "geo_state" << std::setw(11) << "geo_county" << std::setw(13) << "geo_geoid" << std::setw(10) << "population" << std::endl;

  Node* curr = head;
  while (curr != NULL)
  {
    if (curr->data->replanID != -1)
    {
      std::cout << std::left << std::setw(10) << curr->data->replanID << std::setw(45) << curr->data->geoName << std::setw(11) << curr->data->geoStateAbb << std::setw(11) << curr->data->geoSumLev
      << std::setw(10) << curr->data->geoState << std::setw(11)<< curr->data->geoCounty << std::setw(13) << curr->data->geoID << std::setw(10) << curr->data->geoPop << std::endl;
    }
    //next node
    curr = curr->next;
  }
}

void geoTable::List::removeNode(std::smatch deleteme)
{
  Node* curr = head;
  
  while (curr != NULL)
  {
    bool found = false;
    
    for (int i = 1; i < deleteme.size(); i++)
    {
      if (deleteme[i].str() != "*" && curr->data->replanID != -1)
      {
        switch(i) {
          case 2:
            if (deleteme[i].str() == curr->data->geoName)
            {
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          case 3:
            if (deleteme[i].str() == curr->data->geoStateAbb)
            {
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          case 4:
            if (stoi(deleteme[i].str()) == curr->data->geoSumLev)
            {
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          case 5:
            if (stoi(deleteme[i].str()) == curr->data->geoState)
            {
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          case 6:
            if (stoi(deleteme[i].str()) == curr->data->geoCounty)
            {
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          case 7:
            if (deleteme[i].str() == curr->data->geoID)
            {
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          case 8:
            if (stoi(deleteme[i].str()) == curr->data->geoPop)
            {
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          default:
            break;
      
        }
      }
    }
  
    if (found)
    {
      
      std::cout << "(" << curr->data->replanID << "," << curr->data->geoName << "," << curr->data->geoStateAbb << "," << curr->data->geoSumLev << "," << curr->data->geoState
      << "," << curr->data->geoCounty << "," << curr->data->geoID << "," << curr->data->geoPop << ") in geography\n";
      
      curr->data->replanID = -1;
      curr->data->geoName = "";
      curr->data->geoStateAbb = "";
      curr->data->geoSumLev = 0;
      curr->data->geoState = 0;
      curr->data->geoCounty = 0;
      curr->data->geoID = "";
      curr->data->geoPop = 0;

    }
    
    
    //if (curr->next == NULL)
    // if (!found)
    // {
      // std::cout << "No more matching entries found." << std::endl;
    // }
    curr = curr->next;
  }

}
