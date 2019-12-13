#include <cstdlib>
#include <regex>
#include <string>
//also throw in a using namespace std and conver that
//BE CAREFUL OF CONVERTING THE ID INTO AN INT LOOK AT THAT LATER
struct ageLine //Holds each unit of information for the hashtable
{
  std::string ageID="Empty";
  int UnderFive;
  int UnderEightTeen;
  int OverSixtyFive;

  ageLine() {};
  void displayLine();

};

class ageTable //Age table also has a struct housing the linked list
{
  private:
    std::vector<ageLine> ageTable {500};
    std::regex queryPattern {("([0-9]{5}US[0-9]{5}|\\*),([0-9]+|\\*),([0-9]+|\\*),([0-9]+|\\*)")};
    std::regex insertPattern {("([0-9]{5}US[0-9]{5}),([0-9]+),([0-9]+),([0-9]+)")};
  public:
    std::vector<ageLine> getAgeTable();
    std::regex getQueryPattern();
    std::regex getInsertPattern();
    long long int ageHash(std::string key);
    bool keyExists(std::string key);

    void insertAge(std::string data, std::string table);
    void updateAge(std::string data, std::string table);
    void selectAge(std::string data, std::string table);
    void deleteAge(std::string data, std::string table);
    void displayAge();

    struct Node
    {
      ageLine* data;
      Node* next;


    } ageNode;

    struct List
    {
      int size;
      Node *head;
      Node *tail;


      List()
      {
        size=0;
        head=NULL;
        tail=NULL;
      }~List(){};

      void selectNode(std::smatch findme);
      void addNode(ageLine* data);
      Node* findNode(std::string key, int findType);
      void removeNode(std::smatch deleteme);
      void displayList();
    } ageList;
};

