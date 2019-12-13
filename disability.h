/*
This is part 4 Zachary Bender

the hash function i have use is multiplicative stirng hashing where it takes in the geo_id which is the key spot for my data and i have used chaining as my
collsion strategy the colllsion stratgey is implemented in the insert function

I have created a struct called tableitem to hold all the pieces of the data that is coming in from the prase data fucntions
i have then created a class called "DISABILITY" this class will then create the table with a and use the constant table size.
disability will also have functions for the hash table
a function for each of the part that is required

the insert function takes the the data as a string and the table name as a string
it then parses thru the pieces of that function and takes that first part and sends it to the hash function to get the key
the proceeds to set all the amounts in the table to whatever it was sent while it is doing this i also have my linked list class which has a linked list
created and ready to go. in the linked list class we have  created a function called insert node while will take a tableitem pointer so after i have set all of the pieces
i then go thru and set the head a tail created the linked list of pointers to data.

the update function takes the the data as a string and the table name as a string
it then parses thru the pieces of that function and takes that first part and sends it to the hash function to check for the corisponding  key value
then if the first part which is key is equal to something in the hashtable it then goes thru and sets the new vaules for that part.

the select function takes the the data as a string and the table name as a string
it then parses thru the pieces of that function and takes that first part and sends it to the hash function to check for the corisponding  key value
while parsing thru the string it is sent it checks for * and if it has a * it will use the linked list to go thru and check all of the pieces the corrispond
to the data and print of those pieces
if it does not have a * it checks for the actual values instead then prints out those values

the delete function takes the the data as a string and the table name as a string
it then parses thru the pieces of that function and takes that first part and sends it to the hash function to check for the corisponding  key value
while parsing thru the string it is sent it checks for * and if it has a * it will use the linked list to go thru and check all of the pieces the corrispond
to the data and delete all the things that have that data value in common

the print or display function just takes the table and goes thru each part of the table if the table points to null then it does not print if the table points to
something then it prints or if the table points to the next something in the table it prints


*/

#ifndef DISABILITY_H
#define DISABILITY_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <iterator>
#include <fstream>
#include "parse_disability.h"

using namespace std;

const int TABLE_SIZE = 500;


//the hash table items
struct tableItem {
  string geoName;
  string hearingDis;
  string visionDis;
  string cognitiveDis;
  string ambulatoryDis;
  string selfDis;
  string indepDis;

  tableItem* next;
};



//the creation of the hashtable with a size and functions to to deal with the data in the hash table
class Disability
{
private:
  tableItem* table[TABLE_SIZE];
  //tableItem* head;
  //tableItem* tail;
  //vector<tableItem> Disability_items;
public:
  Disability();
  void insertData(string, string);
  void updateData(string, string);
  void selectData(string, string);
  void deleteData(string, string);
  int hashFunction(string);
  void printDisability();
  void writeDisability();
  tableItem** getTable()
  {
    return table;
  }



  
};
//the linklist pointing to the items in the table
  struct Node
  {
    tableItem* data;
    Node* next;
  };
//the creation of the linklist and functions for the linklist
class linklist {
public:
  int size;
  tableItem* head;
  tableItem* tail;

  linklist() { size = 0;head = NULL;tail = NULL; }
  
  void insertNode(tableItem* ptr);
  bool searchNode(string temp);
  
  };
#endif
