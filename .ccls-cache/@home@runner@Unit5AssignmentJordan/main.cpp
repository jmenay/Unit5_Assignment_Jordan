//Assignment 5_Jordan
// Teacher: Dr. Tyson McMillion
// Adapted from Dr_T's original code with credit to an anonomious implementation found online.

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "MenuItem.cpp"
#include "Input_Validation.h"


void populateMenu(vector<MenuItem> &entireMenu)
{
  entireMenu.push_back(MenuItem("Green Tea", 1.25, 'A', 'a')); //add to the end of list the Item1
  entireMenu.push_back(MenuItem("Taco", 1.69, 'B', 'b')); //add to the end of list the Item2
  entireMenu.push_back(MenuItem("Burrito", 1.79, 'C', 'c')); //add to the end of list the Item3
  entireMenu.push_back(MenuItem("Enchilada", 3.99, 'D', 'd')); //add to the end of list the Item4
  entireMenu.push_back(MenuItem("Tostada", 2.57, 'E', 'e')); //add to the end of list the Item5
  entireMenu.push_back(MenuItem("Chalupa", 2.89, 'F', 'f')); //add to the end of list the Item6
  entireMenu.push_back(MenuItem("Fajitas", 6.99, 'G', 'g')); //add to the end of list the Item7
  }



void showMenu(vector<MenuItem> &m)
{
  cout << fixed << setprecision(2);//set doubles to 2 decimal places
  cout << "\x1b[92;7mGREEN TEA CAFE MENU\x1b[0m" << endl;
  cout << "ADD  \tNAME \t COST \tREMOVE\tCOUNT\tDESC" << endl;
  
  for (int i = 0; i < m.size(); i++)
  {
    cout << m[i].AddLetter << ")" << setw(10) << m[i].Name
        << setw(5) << "$" << m[i].ItemCost << setw(5) << "(" << m[i].RemoveLetter
        << ")" << setw(7) << m[i].Count << setw(13) << m[i].Description
        << endl;
  }

}

void acceptOrder(vector<MenuItem> &m)
{
  char option = '\0';// the user-selected menu item
  double subtotal = 0.0;
  double tip = 0.0;
  double payment = 0.0;
  bool paymentCredit = false;
  double change = -1.0;
  double newTotal = 0.0; // subtotal + tax (Amount Billed)
  double totalBill = 0.0; // subtotal + tax + tip (Bill with gratuity)
    
  do
  {
    cout << "\nPlease choose an item (x to Exit): ";
    cin >> option;

    for (int i = 0; i < m.size(); i++)
    {
      if (option == m[i].AddLetter)
      {
        cout << "\nMenu Item " << m[i].AddLetter << " selected.";
        m[i].Count++; //increment the count by 1
        
        cout << "\033[2J\033[1;1H"; //clear screen 
        //cout << "\n1 UP on " << m[i].Name << endl;
        
        subtotal += m[i].ItemCost; //increment the subtotal by the cost of the item 
        
        showMenu(m); //show the updated menu
        cout << "\nSubtotal: $" << subtotal << endl;
      }
      else if (option == m[i].RemoveLetter)
      {
        cout << "\nRemove Item " << m[i].RemoveLetter << " selected.";
        
        if (m[i].Count > 0) //subtract if and only if the count is > 0
        {
          m[i].Count--; //decrement the count by 1
            
          cout << "\033[2J\033[1;1H"; //clear screen 
          cout << "\n1 DOWN on " << m[i].Name << endl;
          
          subtotal -= m[i].ItemCost; //decrement the subtotal by the cost of the item
          
          showMenu(m); //show the updated menu
          cout << "\nSubtotal: $" << subtotal << endl;
          
        }
        else //tell user why the item was not removed - human :-) 
        {
          cout << "\nItem count must be > 0 to remove: " << m[i].Name << endl;
        }
      }
      else if 
        (
        option != m[i].AddLetter &&
        option != m[i].RemoveLetter &&
        option != 'x' &&
        option != 'X'
        ) //test for all of my valid inputs
        {
          
          if (i == 0)
            {
            cout << "\nInvalid input (" << option << "). Please try again." << endl;
            }
        }
    }
  } 
  while (option != 'x' && option != 'X');
  newTotal = subtotal + (subtotal*0.0825);
  cout << "\nAmount Billed: $" << newTotal << endl; 
  //handle the tip process here
  cout << fixed << setprecision(2); 
  cout << " \nWould you like to add a tip?\n"; 
  cout << "(15% = $" << (newTotal*0.15) 
       << ", 20% = $" <<(newTotal*0.2) 
       <<", 25% = $" << (newTotal*0.25) << endl;
  cout << "\nTip Amount: " << endl;
  tip = getValidDouble();
  totalBill = newTotal + tip;
  cout << "Total With Tip: $" << totalBill <<endl;
  cout << "\nThank you for placing your order." << endl;

  paymentCredit = getValidBool("\nCash or Credit? ( 0 for cash, 1 for credit)\n");
  if (!paymentCredit) // for cash payment
  {
    while (change < 0)
    {
      payment = getValidDouble("\nPlease enter cash tended amount: ");
      change = payment - (totalBill);
      if (change < 0)
      {
        cout << "Insuficient Amount, Please add more cash.";
      }
    }
  }
  //handle reciept generation here
  printReceipt(m, subtotal, tip, payment, change);
}
void printReceipt(vector<MenuItem> &m, double subtotal, double tip, double payment, double change) 
{
  double tax = subtotal*0.0825;
  int something = 0;
  cout << "\n\x1b[95;4mRECEIPT\x1b[0m\n" << endl;
  
  for (size_t i = 0; i < m.size(); i++)
  { 
    if (m[i].Count > 0)
    {
      cout << setw(10) << m[i].Name 
           << setw(5) << "$" << m[i].ItemCost 
           << setw(7) << m[i].Count << endl;
    }
  }
  cout << "\nSubtotal: $" << subtotal << endl;
  cout << "Tax: $" << tax << endl;
  cout << "Tip: $" << tip << endl;
  cout << "Total: $" << subtotal +tip +tax << endl;
  cout << "\nTender: " << (change<0? "Credit" : "Cash") << endl;
  if (change > 0)
  {
    cout << "Amount: $" << payment << endl;
    cout << "Change: $" << change << endl;
  }
  cout << "Press any key to continue: " << endl;
  cin >> something;
}


  
int main() 
{
  char ordering = 'y'| 'Y';
  while (ordering == 'y' || 'Y') 
  {
    ordering = 'n' |'N';
    vector<MenuItem> wholeMenu;
    populateMenu(wholeMenu); //put default values in
    showMenu(wholeMenu); //print menu on screen
    acceptOrder(wholeMenu); 
    cout << "\033[2J\033[1;1H"; //clear screen
    ordering = getValidChar("What you like to place an order? \n Enter y for yes or n for no. :(y/n)");
  }
  return 0;
  

}