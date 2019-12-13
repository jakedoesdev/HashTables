/*


*/

#include <cstdlib>
#include <regex>

/*
Geoline struct contains variables to hold the information from one line of geography table data.
*/
struct geoLine {
  int replanID = -2;
  std::string geoName;
  std::string geoStateAbb;
  int geoSumLev;
  int geoState;
  int geoCounty;
  std::string geoID;
  int geoPop;
  
  geoLine() {};
  
  void displayLine();
  //std::string getCSVData();
};

/*
geoTable class has vector variable geoTable which is the hash table. geoTable also holds the regex patterns needed to parse inserts and queries.

Regex by group:
insertPattern allows:
(^[0-9]+),
Group 1 (replanID): 1 or more digits at the beginning of the string and the following comma
(?:\")?((?:[A-Z][a-z]+|[A-Z][a-z]{1,2}\\.)(?: [A-Z][a-z]+)+, (?:[A-Z][a-z]+)(?: [A-Z][a-z]+)?)(?:\")?,
Group 2 (geoName):   Capital word or abbreviation followed by a space and capital word, followed by a comma, space, and 1 or more capital words. All surrounded by optional quotes and followed by a comma
([a-z]{2}),
Group 3 (geoStateAbb): Two lowercase characters
([0-9]+),
Group 4-6 (geoSumLev/State/County): One or more digiits followed by a comma
([0-9]{5}US[0-9]{5}),
Group 7 (geoID): 5 digits, followed by "US", followed by 5 digits and a comma.
([0-9]+)
Group 8 (geoPop): One or more digits.

queryPattern allows the same as insertPattern or "*" for all variables.
*/
class geoTable {
  private:
    //std::vector<std::vector<geoLine>> geoTable {1000};
    std::vector<geoLine> geoTable {1000};
    std::regex queryPattern {("(^[0-9]+|\\*),(?:\")?((?:[A-Z][a-z]+|[A-Z][a-z]{1,2}\\.)(?: [A-Z][a-z]+)+, (?:[A-Z][a-z]+)(?: [A-Z][a-z]+)?|\\*)(?:\")?,([a-z]{2}|\\*),([0-9]+|\\*),([0-9]+|\\*),([0-9]+|\\*),([0-9]{5}US[0-9]{5}|\\*),([0-9]+|\\*)")};
    std::regex insertPattern {("(^[0-9]+),(?:\")?((?:[A-Z][a-z]+|[A-Z][a-z]{1,2}\\.)(?: [A-Z][a-z]+)+, (?:[A-Z][a-z]+)(?: [A-Z][a-z]+)?)(?:\")?,([a-z]{2}),([0-9]+),([0-9]+),([0-9]+),([0-9]{5}US[0-9]{5}),([0-9]+)")};
  public:
    void insertGeo(std::string data, std::string table);
    void updateGeo(std::string data, std::string table);
    void selectGeo(std::string data, std::string table); //can access list (i.e. data can have * as values)
    void deleteGeo(std::string data, std::string table); //can access list (i.e. data can have * as values)
    void displayGeo();
    int geoHash(int key);
    std::vector<geoLine> getGeoTable();
    std::regex getQueryPattern();
    std::regex getInsertPattern();
    bool keyExists(int key);
    
  
    //node of secondary index
    struct Node {
      geoLine* data;
      Node* next;
    } geoNode;

    //secondary index
    struct List {
      int size;
      Node *head, *tail;
      
      List() {size=0; head=NULL; tail=NULL;}
      ~List(){};
      
      void selectNode(std::smatch findme);
      void addNode(geoLine* data);
      Node* findNode(std::string key, int findType);
      void removeNode(std::smatch deleteme);
      //void insertAt(Node** curr, int pos, geoLine* data);
      void displayList();
    } geoList;
    
};

//********************************************************LIST******************************************************************

//node of secondary index
// struct Node {
  // geoLine* data;
  // Node* next;
// };

// //secondary index
// struct List {
  // int size;
  // Node *head, *tail;
  
  // List() {size=0; head=NULL; tail=NULL;}
  // ~List(){};
  
  // void insert(geoLine* data);
  // Node* getNode(geoLine* data);
  // void remove();
  // void insertAt(Node** curr, int pos, geoLine* data);
  // void displayList(Node* head);
  // //void displayList();
  // void removeAt(Node* h, Node *n);
// };
