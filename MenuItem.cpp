#include <iostream>
#include <vector>

using namespace std;

class MenuItem
{
public:
string Name;
double ItemCost;
string Description;
char AddLetter;
char RemoveLetter;
int Count;

MenuItem(){}

MenuItem(string name, double itemCost, char addLetter, char removeLetter)
  {
    Name = name;
    ItemCost = itemCost;
    AddLetter = addLetter;
    RemoveLetter = removeLetter;
    Description = "delicious";
    Count = 0;  
  }
};

void populateMenu(vector <MenuItem> &);
void showMenu(vector<MenuItem> &);
void acceptOrder(vector<MenuItem> &);
void printReceipt(vector<MenuItem> &, double, double, double, double);
