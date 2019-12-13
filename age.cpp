#include <iostream>
#include <iomanip>
#include <regex>
#include <string>
#include <math.h>
#include "age.h"

long long int ageTable::ageHash(std::string key)//mid square
{
  std::string shortKey=key.substr(7);
  int intKey=stoi(shortKey);
  std::string tempInt=std::to_string(intKey*intKey);
  std::string tempStri=tempInt.substr(tempInt.size()/2,4);
  int final=stoi(tempStri)%10;
  return final;

}
bool ageTable::keyExists(std::string key)//function that determines if the key exists at a point
{
  bool exists = false;
  for (auto it = this->ageTable.begin(); it != this->ageTable.end(); it++)
  {
    if (key == it->ageID)
    {
      exists = true;
    }
  }
  return exists;
}
std::regex ageTable::getQueryPattern()//gets the regex for select/delete allows for *s
{
  return this->queryPattern;
}
std::regex ageTable::getInsertPattern()//gets the regex for insert doesnt allow for *s
{
  return this->insertPattern;
}
void ageTable::insertAge(std::string data, std::string table)//inserts an ageLine, to the AgeTable and the Age Linked List
{
  if (table != "age")
  {
    std::cout << "Error, you have attempted to insert non-age data into the age table." << std::endl;
  }
  else
  {
    std::smatch matcher;
    int index = 0;
    int probe = 0;
    bool done = false;

    ageLine aL;
    ageLine *aP = new ageLine;
    std::regex_search(data, matcher, this->getInsertPattern());
    
    aL.ageID = matcher[1].str();////////////
    aL.UnderFive = stoi(matcher[2].str());////////////
    aL.UnderEightTeen = stoi(matcher[3].str());////////////
    aL.OverSixtyFive = stoi(matcher[4].str());///////////

    index = this->ageHash(aL.ageID);/////////////
    if (!(this->keyExists(aL.ageID)))
    {//////////////////////////
      while (!done)
      {
        index = index+probe;
        
        if (this->ageTable[index].ageID == "Empty")
        {
          this->ageTable[index] = aL;
          aP = &this->ageTable[index];
          this->ageList.addNode(aP);
          done = true;
          std::cout << "Inserted  " << data << "  into " << table << std::endl;
        }
        else
        {
          probe++;
          index = (this->ageHash(aL.ageID)+(probe*probe))%table.size();/////////////////
        }
      }
    }
    else
    {
      std::cout << "Failed to insert (" << data << ") into " << table << std::endl;
    }
  }
}
void ageTable::deleteAge(std::string data, std::string table)//Deletes a member from the age table and replaces it, also removes it from the linked list
{
  std::smatch matcher;
  bool found = false;

  std::regex_search(data, matcher, this->getQueryPattern());

  if (matcher[1].str() == "*")
  {

    std::cout << "Deleted entries:\n";
    for (int i = 0; i < this->ageList.size; i++)
    {
      this->ageList.removeNode(matcher);
    }
  }
  else
  {
    for (auto it = this->ageTable.begin(); it != this->ageTable.end(); it++)
    {
      if (it->ageID == matcher[1].str())
      {
        it->ageID = "Empty";
        it->UnderFive = -1;
        it->UnderEightTeen = -1;
        it->OverSixtyFive = -1;

        std::cout << "Deleted (" << data << ") in " << table << std::endl;
        found=true;
      }
    }
    if (!found)
    {
      std::cout << "Failed to delete (" << data << ") in " << table << std::endl;
    }
  }
}
void ageTable::updateAge(std::string data, std::string table)//updates info inside the ageTable and linked list
{
  if (table != "age")
  {
    std::cout << "Error, you have attempted to update non-age data to the age table." << std::endl;
  }
  else
  {
    std::smatch matcher;
    int index;
    bool done = false;
    std::regex_search(data, matcher, this->getInsertPattern());
    
    for (int i = 0; i < this->ageTable.size(); i++)
    {
      if (this->ageTable[i].ageID == matcher[1].str())
      {
        this->ageTable[i].UnderFive = stoi(matcher[2].str());////////////
        this->ageTable[i].UnderEightTeen = stoi(matcher[3].str());/////////
        this->ageTable[i].OverSixtyFive = stoi(matcher[4].str());////////////

        done = true;
        std::cout << "Updated (" << data << ") in " << table << std::endl;
      }
    }
    
    if (!done)
    {
      std::cout << "Failed to update (" << data << ") in " << table << std::endl;
    }
  }
}
void ageTable::selectAge(std::string data, std::string table)//Selects a matching function and returns if it is found or not
{
  std::smatch matcher;
  bool found = false;
  
  std::regex_search(data, matcher, this->getQueryPattern());
  
  if (matcher[1].str() == "*")
  {
    std::cout << "Found entries:\n";
    this->ageList.selectNode(matcher);
  }
  else
  {
    for (auto it = this->ageTable.begin(); it != this->ageTable.end(); it++)
    {
      if (it->ageID == matcher[1].str())
      {
        std::cout << "Found (" << data << ") in " << table << std::endl;
        found = true;
      }
    }
    if (!found)
    {
      std::cout << "No entries match (" << data << ") in " << table << std::endl;
    }
  }
  
}
void ageTable::displayAge()
{
  std::cout << std::left << std::setw(20) << "Age ID" << std::setw(20) << "Under Five" << std::setw(20) << "Under EightTeen" << std::setw(20) << "Over SixtyFive"<< std::endl;
  for (auto it = this->ageTable.begin(); it != this->ageTable.end(); it++)
  {
    if (it->ageID != "Empty")
    {
      it->displayLine();
    }
  }
}
void ageLine::displayLine()//displays the ageline that is called
{
  std::cout << std::left << std::setw(20) << this->ageID << std::setw(20) << this->UnderFive << std::setw(20) << this->UnderEightTeen << std::setw(20) << this->OverSixtyFive << std::endl;
}
std::vector<ageLine> ageTable::getAgeTable()
{
  std::vector<ageLine> aT;
  ageLine tmpAL;
  for (int i = 0; i < ageTable.size(); i++)
  {
    if (ageTable[i].ageID != "Empty")
    {
      tmpAL.ageID = ageTable[i].ageID;
      tmpAL.UnderFive = ageTable[i].UnderFive;
      tmpAL.UnderEightTeen = ageTable[i].UnderEightTeen;
      tmpAL.OverSixtyFive = ageTable[i].OverSixtyFive;
      aT.push_back(tmpAL);
    }
  }
  return aT;
}
void ageTable::List::displayList()//displays all the nodes in the linked list in order
{
  std::cout << std::left << std::setw(20) << "Age ID" << std::setw(20) << "Under Five" << std::setw(20) << "Under EightTeen" << std::setw(20) << "Over SixtyFive"<< std::endl;
  Node* curr = head;
  while (curr != NULL)
  {
    if (curr->data->ageID != "Empty")
    {
      std::cout << std::left << std::setw(20) << curr->data->ageID << std::setw(20) << curr->data->UnderFive << std::setw(20) << curr->data->UnderEightTeen << std::setw(20) << curr->data->OverSixtyFive << std::endl;
    }

    curr = curr->next;
  }
}
void ageTable::List::addNode(ageLine* data)//adds node to the linked list
{
  Node* n = new Node;
  n->data = data;
  n->next = NULL;
  if (head == NULL)
  {
    head = n;
    tail = head;
  }
  else
  {

    tail->next = n;
    tail = tail->next;

  }
  size++;
}
void ageTable::List::removeNode(std::smatch deleteme)//removes node from the linked list
{
  Node* curr = head;
  while (curr != NULL)
  {
    bool found = false;
    for (int i = 1; i < deleteme.size(); i++)
    {
      if (deleteme[i].str() != "*" && curr->data->ageID != "Empty")
      {
        switch(i) {
          case 2:
            if (stoi(deleteme[i].str()) == curr->data->UnderFive)
            {/////////////////
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          case 3:
            if (stoi(deleteme[i].str()) == curr->data->UnderEightTeen)
            {///////////////
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          case 4:
            if (stoi(deleteme[i].str()) == curr->data->OverSixtyFive)
            {///////////////
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
    if (found||deleteme[0].str() != "*")
    {
      if(curr->data->ageID != "Empty")
      {
      std::cout << "(" << curr->data->ageID << "," << curr->data->UnderFive << "," << curr->data->UnderEightTeen << "," << curr->data->OverSixtyFive << ") in age\n";
      }
      curr->data->ageID = "Empty";
      curr->data->UnderFive = -1;
      curr->data->UnderEightTeen = -1;
      curr->data->OverSixtyFive = -1;
    }
    curr = curr->next;
  }

}
void ageTable::List::selectNode(std::smatch findme)//selects a node from the linked list that matches if they meet the qualifications
{
  
  Node* curr = head;
  bool output = false;
  while (curr != NULL)
  {
    bool found = false;
    for (int i = 1; i < findme.size(); i++)
    {
      if (findme[i].str() != "*" && curr->data->ageID != "Empty")
      {
        switch(i) {
          case 2:
            if (stoi(findme[i].str()) == curr->data->UnderFive)
            {/////////////////////////
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          case 3:
            if (stoi(findme[i].str()) == curr->data->UnderEightTeen)
            {//////////////
              found = true;
            }
            else
            {
              found = false;
            }
            break;
          case 4:
            if (stoi(findme[i].str()) == curr->data->OverSixtyFive)
            {//////////////////
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
  
    if (found||findme[0].str() != "*")
    {
      if(curr->data->ageID != "Empty")
      {
        std::cout << "(" << curr->data->ageID << "," << curr->data->UnderFive << "," << curr->data->UnderEightTeen << "," << curr->data->OverSixtyFive << ") in age\n";
      }
      output = true;
    }

    curr = curr->next;
  }

  if (!output)
  {
    std::cout << "No entries matching (" << findme[0].str() << ") found in age\n";
  }
}

