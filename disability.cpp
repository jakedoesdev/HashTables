//part 4 zachary bender
#include "disability.h"
#include "parse_disability.h"
Disability::Disability()
{
  //head = NULL;
  //tail = NULL;
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    table[i] = nullptr;
  }
}



void Disability::insertData(string data, string tableName)
{
  linklist mylist;
  tableItem* Titems = new tableItem;
  Node* Linkitem = new Node;
  istringstream iss(data);
  

  vector <string> result;

  string temp;
  string token;
  
  while (getline(iss, token, ',')) {

    result.push_back(token);

  }
  temp = result[0] + result[1];
  string split = temp.substr(1);
  string secondsplit = split.substr(0, split.length() - 1);

  
  Titems->geoName = secondsplit;


  Titems->hearingDis = result[2];
  Titems->visionDis = result[3];
  Titems->cognitiveDis = result[4];
  Titems->ambulatoryDis = result[5];
  Titems->selfDis = result[6];
  Titems->indepDis = result[7];
  Titems->next = nullptr;
  
  
  int key = hashFunction(Titems->geoName);
  //cout<<"S  " << Titems->geoName <<"  T"<< endl;
  if (table[key] == nullptr)
  {

    table[key] = Titems;
    //Linkitem->data = Titems;
    //cout << "S  " << Titems->geoName << "  T" << endl;
    mylist.insertNode(Titems);
    //cout << table[key] << endl;
    cout << "Inserted (" << data << ") into disability" << endl;
  }
  
  else if(table[key]->next == nullptr)
  {
    mylist.insertNode(Titems);
    tableItem* walker = new tableItem;
    walker = table[key];

    while (walker->next)
    {
      
        walker = walker->next;
        //Linkitem->data = walker->next;
        

    }
    walker->next = Titems;
    //cout << "New  " << Titems->geoName << "  One" << endl;
    if (walker->geoName == Titems->geoName) {
      cout << "Failed to inserted (" << data << ") into disability" << endl;
    }
    else if (walker->geoName != Titems->geoName) {
      cout << "Inserted (" << data << ") into disability" << endl;
      
    }

  }
  else {
    mylist.insertNode(Titems);
    tableItem* walker2 = new tableItem;
    walker2 = table[key]->next;

    while (walker2->next)
    {

      walker2 = walker2->next;
      //Linkitem->data = walker->next;


    }
    walker2->next = Titems;
    //cout << "New new   " << Titems->geoName << "  One" << endl;
    if (walker2->geoName == Titems->geoName) {
      cout << "Failed to inserted (" << data << ") into disability" << endl;
    }
    else if (walker2->geoName != Titems->geoName) {
      cout << "Inserted (" << data << ") into disability" << endl;

    }
  }


  

}
//hash function that uses multiplicative string hashing had to modify the for loop because some words were to long
int Disability::hashFunction(string word)
{
  
  
  int x = 0;

  for (int i = 0; i < word.length()-5;i++) {
    
    x = (x * 2) + i;
    
  }
  
  
  return x%TABLE_SIZE;
}
/*
select fucntion for the hash table check for * and if it has it it use the linklist way of searching thru the data if
it doesnt then use hashtable
*/

void Disability::selectData(string data, string tableName) {
  //string str = "*";
  if (data.find("*") != string::npos) {
    
    //linklist *temp = linklist::head;

    istringstream iss(data);


    vector <string> fin;
    string tempG;
    string tempP;
    string tempV;
    string tempC;
    string tempA;
    string tempS;
    string tempI;

    string temp;

    string token2;

    while (getline(iss, token2, ',')) {

      fin.push_back(token2);

    }
    temp = fin[0] + fin[1];
    string split = temp.substr(1);
    string secondsplit = split.substr(0, split.length() - 1);
    //cout << secondsplit << endl;
    if (fin[0] == "*") {
      tempG = fin[0];
      tempP = fin[1];
      tempV = fin[2];
      tempC = fin[3];
      tempA = fin[4];
      tempS = fin[5];
      tempI = fin[6];
    }
    else {
      tempG = secondsplit;
      tempP = fin[1];
      tempV = fin[2];
      tempC = fin[3];
      tempA = fin[4];
      tempS = fin[5];
      tempI = fin[6];
    }
    //cout << tempG << " " << tempP << " " << tempV << " " << tempA << " " << tempS << " " << tempI << endl;

    tableItem* delPtr;
    tableItem* p1;
    tableItem* p2;

    for (int i = 0; i < TABLE_SIZE; i++)
    {

      //cout << i << ": ";

      if (table[i] == nullptr)
      {
        //cout << "Not found in hash table" << endl;
      }
      else if (table[i]->geoName == tempG || table[i]->hearingDis == tempP || table[i]->visionDis == tempV || table[i]->cognitiveDis == tempC || table[i]->ambulatoryDis == tempA
        || table[i]->selfDis == tempS || table[i]->indepDis == tempI && table[i]->next == NULL)
      {


        cout << "Found entries" << endl;
        cout << " (" << data << ") in disabilty" << endl;

        

      }
      else if (table[i]->geoName == tempG || table[i]->hearingDis == tempP || table[i]->visionDis == tempV || table[i]->cognitiveDis == tempC || table[i]->ambulatoryDis == tempA
        || table[i]->selfDis == tempS || table[i]->indepDis == tempI)
      {


        
        cout << "Found entries" << endl;
        cout << " (" << data << ") in disabilty" << endl;
      }

      else if (table[i]->next) {
        if (table[i]->next->geoName == tempG || table[i]->next->hearingDis == tempP || table[i]->next->visionDis == tempV || table[i]->next->cognitiveDis == tempC || table[i]->next->ambulatoryDis == tempA
          || table[i]->next->selfDis == tempS || table[i]->next->indepDis == tempI)
        {

          
          cout << "Found entries" << endl;
          cout << " (" << data << ") in disabilty" << endl;
        }
        else if (table[i]->next->next != nullptr) {


          
          cout << "Found entries" << endl;
          cout << " (" << data << ") in disabilty" << endl;

        }

      }
    }
  }
  else {
    tableItem* delPtr;
    tableItem* p1;
    tableItem* p2;

    istringstream iss(data);


    vector <string> result;
    string tempG;
    string tempP;
    string tempV;
    string tempC;
    string tempA;
    string tempS;
    string tempI;

    string temp;

    string token;

    while (getline(iss, token, ',')) {

      result.push_back(token);

    }
    temp = result[0] + result[1];
    string split = temp.substr(1);
    string secondsplit = split.substr(0, split.length() - 1);

    //cout <<secondsplit<< endl;

    tempG = secondsplit;
    tempP = result[2];
    tempV = result[3];
    tempC = result[4];
    tempA = result[5];
    tempS = result[6];
    tempI = result[7];
    //cout <<"s" << tempG << "s"<<endl; //<< tempP << "," << tempV << "," << tempC << "," << tempA << "," << tempS << "," << tempI << endl;

    for (int i = 0; i < TABLE_SIZE; i++)
    {

      //cout << i << ": ";

      if (table[i] == nullptr)
      {
        //cout << "Not found in hash table" << endl;
      }
      else if (table[i]->geoName == tempG || table[i]->hearingDis == tempP || table[i]->visionDis == tempV || table[i]->cognitiveDis == tempC || table[i]->ambulatoryDis == tempA
        || table[i]->selfDis == tempS || table[i]->indepDis == tempI && table[i]->next == NULL)
      {


        cout << "Found (" << data << ") in disabilty" << endl;
        
        

      }
      

      else if (table[i]->next) {
        if (table[i]->next->geoName == tempG || table[i]->next->hearingDis == tempP || table[i]->next->visionDis == tempV || table[i]->next->cognitiveDis == tempC || table[i]->next->ambulatoryDis == tempA
          || table[i]->next->selfDis == tempS || table[i]->next->indepDis == tempI)
        {

          
          
          cout << "Found (" << data << ") in disabilty" << endl;
        }
        else if (table[i]->next->next != nullptr) {


        
          
          cout << "Found (" << data << ") in disabilty" << endl;

        }
        

      }
      
    }
  }


}

void Disability::deleteData(string data, string tableName) {
  //string str = "*";

  if (data.find("*") != string::npos) {
    //cout << "Deleted Entries" << endl;
    //linklist *temp = linklist::head;

    istringstream iss(data);


    vector <string> fin;
    string tempG;
    string tempP;
    string tempV;
    string tempC;
    string tempA;
    string tempS;
    string tempI;

    string temp;

    string token2;

    while (getline(iss, token2, ',')) {

      fin.push_back(token2);

    }
    temp = fin[0] + fin[1];
    string split = temp.substr(1);
    string secondsplit = split.substr(0, split.length() - 1);
    //cout << secondsplit << endl;
    if (fin[0] == "*") {
      tempG = fin[0];
      tempP = fin[1];
      tempV = fin[2];
      tempC = fin[3];
      tempA = fin[4];
      tempS = fin[5];
      tempI = fin[6];
    }
    else {
      tempG = secondsplit;
      tempP = fin[2];
      tempV = fin[3];
      tempC = fin[4];
      tempA = fin[5];
      tempS = fin[6];
      tempI = fin[7];
    }
    linklist linker;
    linker.searchNode(secondsplit);
    //cout << tempG << " " << tempP << " " << tempV << " " << tempA << " " << tempS << " " << tempI << endl;
    

    tableItem* delPtr;
    tableItem* p1;
    tableItem* p2;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
      
      //cout << i << ": ";

      if (table[i] == nullptr)
      {
        //cout << "Not found in hash table" << endl;
      }
      else if (table[i]->geoName == tempG || table[i]->hearingDis == tempP || table[i]->visionDis == tempV || table[i]->cognitiveDis == tempC || table[i]->ambulatoryDis == tempA
        || table[i]->selfDis == tempS || table[i]->indepDis == tempI && table[i]->next == NULL)
      {


        cout << "Deleted (" << data << ") in disabilty" << endl;

        table[i]->geoName = "empty";

        table[i]->hearingDis = "empty";

        table[i]->visionDis = "empty";

        table[i]->cognitiveDis = "empty";

        table[i]->ambulatoryDis = "empty";

        table[i]->selfDis = "empty";

        table[i]->indepDis = "empty";

      }
      
      
      else if (table[i]->next) {
        if (table[i]->next->geoName == tempG || table[i]->next->hearingDis == tempP || table[i]->next->visionDis == tempV || table[i]->next->cognitiveDis == tempC || table[i]->next->ambulatoryDis == tempA
          || table[i]->next->selfDis == tempS || table[i]->next->indepDis == tempI)
        {
          table[i]->next->geoName = "empty";

          table[i]->next->hearingDis = "empty";

          table[i]->next->visionDis = "empty";

          table[i]->next->cognitiveDis = "empty";

          table[i]->next->ambulatoryDis = "empty";

          table[i]->next->selfDis = "empty";

          table[i]->next->indepDis = "empty";


          //tableItem* walker = new tableItem;

          //delPtr = table[i]->next;
          //walker == nullptr;
          //table[i]->next = walker;
          //delete delPtr;
          cout << "Deleted (" << data << ") in disabilty" << endl;


        }
        
        else if (table[i]->next->next != nullptr) {


          tableItem* walker = new tableItem;

          delPtr = table[i]->next->next;
          walker == nullptr;
          table[i]->next->next = walker;
          delete delPtr;
          cout << "Deleted (" << data << ") in disabilty" << endl;

        }


      }
      else  {
        

      }
    }
  }
  else {
    tableItem* delPtr;
    tableItem* p1;
    tableItem* p2;

    istringstream iss(data);


    vector <string> result;
    string tempG;
    string tempP;
    string tempV;
    string tempC;
    string tempA;
    string tempS;
    string tempI;

    string temp;

    string token;

    while (getline(iss, token, ',')) {

      result.push_back(token);

    }
    temp = result[0] + result[1];
    string split = temp.substr(1);
    string secondsplit = split.substr(0, split.length() - 1);

    //cout <<secondsplit<< endl;

    tempG = secondsplit;
    tempP = result[2];
    tempV = result[3];
    tempC = result[4];
    tempA = result[5];
    tempS = result[6];
    tempI = result[7];
    //cout <<"s" << tempG << "s"<<endl; //<< tempP << "," << tempV << "," << tempC << "," << tempA << "," << tempS << "," << tempI << endl;

    for (int i = 0; i < TABLE_SIZE; i++)
    {

      //cout << i << ": ";

      if (table[i] == nullptr)
      {
        //cout << "Not found in hash table" << endl;
      }
      else if (table[i]->geoName == tempG || table[i]->hearingDis == tempP || table[i]->visionDis == tempV || table[i]->cognitiveDis == tempC || table[i]->ambulatoryDis == tempA
        || table[i]->selfDis == tempS || table[i]->indepDis == tempI && table[i]->next == NULL)
      {


        cout << "Deleted (" << data << ") in disabilty" << endl;

        table[i]->geoName = "empty";

        table[i]->hearingDis = "empty";

        table[i]->visionDis = "empty";

        table[i]->cognitiveDis = "empty";

        table[i]->ambulatoryDis = "empty";

        table[i]->selfDis = "empty";

        table[i]->indepDis = "empty";

      }
      else if (table[i]->geoName == tempG || table[i]->hearingDis == tempP || table[i]->visionDis == tempV || table[i]->cognitiveDis == tempC || table[i]->ambulatoryDis == tempA
        || table[i]->selfDis == tempS || table[i]->indepDis == tempI)
      {


        delPtr = table[i];
        table[i] = table[i]->next;
        delete delPtr;
        cout << "Deleted (" << data << ") in disabilty" << endl;

      }

      else if (table[i]->next) {
        if (table[i]->next->geoName == tempG || table[i]->next->hearingDis == tempP || table[i]->next->visionDis == tempV || table[i]->next->cognitiveDis == tempC || table[i]->next->ambulatoryDis == tempA
          || table[i]->next->selfDis == tempS || table[i]->next->indepDis == tempI)
        {
          table[i]->next->geoName = "empty";

          table[i]->next->hearingDis = "empty";

          table[i]->next->visionDis = "empty";

          table[i]->next->cognitiveDis = "empty";

          table[i]->next->ambulatoryDis = "empty";

          table[i]->next->selfDis = "empty";

          table[i]->next->indepDis = "empty";
          cout << "Deleted (" << data << ") in disabilty" << endl;
        }
        else if (table[i]->next->next != nullptr) {


          tableItem* walker = new tableItem;

          delPtr = table[i]->next->next;
          walker == nullptr;
          table[i]->next->next = walker;
          delete delPtr;
          cout << "Deleted (" << data << ") in disabilty" << endl;

        }

      }
    }
  }
}
void Disability::updateData(string data, string tableName)
{

  istringstream iss(data);


  vector <string> result;

  string temp2;
  string token;

  while (getline(iss, token, ',')) {

    result.push_back(token);

  }
  temp2 = result[0] + result[1];
  string spliter = temp2.substr(1);
  string secondsplit = spliter.substr(0, spliter.length() - 1);

  temp2 = secondsplit;

  int key = hashFunction(temp2);
  //cout << temp2 << endl;
  string split = data.substr(1, data.find("\""));
  string temp;

  if (table[key] != nullptr)
  {
    tableItem* walker = new tableItem;
    walker = table[key];

    //temp = (walker->data).substr(1, (walker->data).find("\""));
    temp = walker->geoName;
    while (walker->next && temp != split)
    {
      walker = walker->next;
      //temp = (walker->data).substr(1, (walker->data).find("\""));
      temp = walker->geoName;
    }
  
     if (temp == temp2)
    {
      //walker->data = data;

      istringstream iss(data);
      //Titems.geoName=

      vector <string> result;


      string token;
      //size_t pos = -1;
      //int i;
      while (getline(iss, token, ',')) {
        result.push_back(token);
      }
      //cout << result[0] << result[1] <<endl;


      walker->geoName = temp2;

      //cout << walker->geoName << endl;
      walker->hearingDis = result[2];
      walker->visionDis = result[3];
      walker->cognitiveDis = result[4];
      walker->ambulatoryDis = result[5];
      walker->selfDis = result[6];
      walker->indepDis = result[7];
      cout << "Updated (" << data << ") in disability" << endl;
    }
    
  }
  //else if()
  else {
    cout << "Failed to Updated (" << data << ") in disability" << endl;
  }
}
//need to change this to table format
void Disability::printDisability() {
  //Disability myobj;
  //DisabilityList mylist;
  //Node** myTable = myobj.getTable();

  
  //thelist.insertNode();

  //cout << left << setw(40) << setfill(' ');
  cout << "geo_name";
  cout << "\t\t\t\t";
  //cout << left << setw(15) << setfill(' ');
  cout << "hearing_disability";
  cout << "\t";
  //cout << left << setw(15) << setfill(' ');
  cout << "vision_disability";
  cout << "\t";
  //cout << left << setw(15) << setfill(' ');
  cout << " cognitive_disability";
  cout << "\t ";
  //cout << left << setw(15) << setfill(' ');
  cout << "ambulatory_disability";
  cout << " \t";
  //cout << left << setw(15) << setfill(' ');
  cout << "self_care_disability";
  cout << " \t";
  //cout << left << setw(15) << setfill(' ');
  cout << "independent_living_disability" << std::endl;

  for (int i = 0; i < TABLE_SIZE; i++)
  {
    
    //cout << i << ": ";

    if (table[i] == nullptr || table[i]->hearingDis == "empty" || table[i]->indepDis=="empty")
    {
      //cout << "NULL\n";
    }
    else
    {

      //cout << table[i]->data << "\n";
      cout << left << setw(40) << setfill(' ');
      cout << table[i]->geoName;
      cout << left << setw(25) << setfill(' ');
      cout << table[i]->hearingDis;
      cout << left << setw(25) << setfill(' ');
      cout << table[i]->visionDis;
      cout << left << setw(25) << setfill(' ');
      cout << table[i]->cognitiveDis;
      cout << left << setw(25) << setfill(' ');
      cout << table[i]->ambulatoryDis;
      cout << left << setw(25) << setfill(' ');
      cout << table[i]->selfDis;
      cout << left << setw(25) << setfill(' ');
      cout << table[i]->indepDis;
      cout << "\n";

      if (table[i]->next && table[i]->next->geoName != "empty")
      {
        //cout << table[i]->next->data << "\n";

        cout << left << setw(40) << setfill(' ');
        cout << table[i]->next->geoName;
        cout << left << setw(25) << setfill(' ');
        cout << table[i]->next->hearingDis;
        cout << left << setw(25) << setfill(' ');
        cout << table[i]->next->visionDis;
        cout << left << setw(25) << setfill(' ');
        cout << table[i]->next->cognitiveDis;
        cout << left << setw(25) << setfill(' ');
        cout << table[i]->next->ambulatoryDis;
        cout << left << setw(25) << setfill(' ');
        cout << table[i]->next->selfDis;
        cout << left << setw(25) << setfill(' ');
        cout << table[i]->next->indepDis;
        cout << "\n";

        if(table[i]->next->next != nullptr){
        cout << left << setw(40) << setfill(' ');
        cout << table[i]->next->next->geoName;
        cout << left << setw(25) << setfill(' ');
        cout << table[i]->next->next->hearingDis;
        cout << left << setw(25) << setfill(' ');
        cout << table[i]->next->next->visionDis;
        cout << left << setw(25) << setfill(' ');
        cout << table[i]->next->next->cognitiveDis;
        cout << left << setw(25) << setfill(' ');
        cout << table[i]->next->next->ambulatoryDis;
        cout << left << setw(25) << setfill(' ');
        cout << table[i]->next->next->selfDis;
        cout << left << setw(25) << setfill(' ');
        cout << table[i]->next->next->indepDis;
        cout << "\n";
        }
      }
      
      else
      {
        
        cout << "";
      }

    }
  }



}
void Disability::writeDisability() {
  ofstream myfile;
  myfile.open("disability_save.csv");
  myfile << "geo_name" << endl;
  myfile << "geo_name,hearing_disability,vision_disability,cognitive_disability,ambulatory_disability,self_care_disability,independent_living_disability" << endl;
  for (int i = 0; i < TABLE_SIZE; i++)
  {

    //cout << i << ": ";

    if (table[i] == nullptr || table[i]->hearingDis == "empty" || table[i]->indepDis == "empty")
    {
      //cout << "NULL\n";
    }
    else
    {

      //cout << table[i]->data << "\n";
      
      myfile << table[i]->geoName << ",";
      
      myfile << table[i]->hearingDis << ",";
      
      myfile << table[i]->visionDis << ",";
      
      myfile << table[i]->cognitiveDis << ",";
      
      myfile << table[i]->ambulatoryDis << ",";
      
      myfile << table[i]->selfDis << ",";
      
      myfile << table[i]->indepDis << ",";
      myfile << "\n";

      if (table[i]->next && table[i]->next->geoName != "empty")
      {
        //cout << table[i]->next->data << "\n";

        
        myfile << table[i]->next->geoName << ",";
        
        myfile << table[i]->next->hearingDis << ",";
        
        myfile << table[i]->next->visionDis << ",";
        
        myfile << table[i]->next->cognitiveDis << ",";
        
        myfile << table[i]->next->ambulatoryDis << ",";
        
        myfile << table[i]->next->selfDis << ",";
        
        myfile << table[i]->next->indepDis << ",";
        myfile << "\n";

        if (table[i]->next->next != nullptr) {
          
          myfile << table[i]->next->next->geoName << ",";
        
          myfile << table[i]->next->next->hearingDis << ",";
          
          myfile << table[i]->next->next->visionDis << ",";
          
          myfile << table[i]->next->next->cognitiveDis << ",";
          
          myfile << table[i]->next->next->ambulatoryDis << ",";
          
          myfile << table[i]->next->next->selfDis << ",";
          
          myfile << table[i]->next->next->indepDis << ",";
          myfile << "\n";
        }
        //cout << table[i]->next->next->data << "\n";
      }

      else
      {
        myfile << "";
      }

    }
  }


}
/*
linklist fucntion that is getting passed all the stuf from insert then runs thru the linkm list and sets the
data values for each part
*/
void linklist::insertNode(tableItem* Pointer){

  //Node* Ptr = new Node;
  //head = new tableItem;
  //tail = new tableItem;
  
  while (Pointer != NULL) {
    
    if(head == NULL){
    head = Pointer;
    tail = Pointer;
    Pointer = NULL;
    
    }
    else if (head = Pointer) {
      tail->next = Pointer;
      tail = Pointer;
    }
    }
    size++;
    /*
    

  cout << "hello" << endl;
    
    
    tableItem *temp = new tableItem;
    temp = head;
    while (temp != NULL) {
      cout << head->geoName << " "<< head->hearingDis << " "<<head->visionDis<<"\t"<<endl;
      temp = temp->next;
    }*/
}
      
bool linklist::searchNode(string temp) {
  
  
  tableItem* curr = head;

  for (int i = 0;i < size;i++) {
    

    if (curr[i].geoName == temp) {
      
      return true;
      curr = curr[i].next;
    }
  }
  
  return false;

}
