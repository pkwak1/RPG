/* Data Structures Final Project DarkMage.cpp
   This is the iplementation (.cpp) for the DarkMage character subclass.
*/

#include "Character.h"
#include "DarkMage.h"
#include <iostream>
#include <string>
using namespace std;

DarkMage::DarkMage (string Name, string Class, bool dead) : Character (Name, Class, dead) {
  Name = "Henry", "Tharja";
}

void DarkMage::upgradeClass() {
  Class = "Sorcerer";
  stats["HP"]= stats["Max HP"];              // The amount of hp a character currently has                                                        
  stats["Max HP"]= 32;        // The total amount of hp a character has in total                                                                  
  stats["Avoid"]= stats["Avoid"] + 5;         // The percentage chance that an unit has in dodging a character's attack                                           
  stats["Accuracy"]= stats["Accuracy"] + 3;      // The percentage chance that an unit's attacks hits                                                                
  stats["Crit"]= stats["Crit"] + 10;          // The percentage chance that an unit's attack does crit damage                                                     
  stats["Damage"]= stats["Damage"] + 3;        // The amount of damage an attack does                                                                              
  stats["Crit Damage"]= stats["Crit Damage"] + 6;
}

void DarkMage::print()
{
	cout << Name << endl;
	cout << ========================================= << endl;
	cout << "Class: " << Class << endl;
        stats["HP"]= stats["Max HP"];              // The amount of hp a character currently has
        stats["Max HP"]= 17;        // The total amount of hp a character has in total 
        stats["Avoid"]= 55;         // The percentage chance that an unit has in dodging a character's attack
        stats["Accuracy"]= 80;      // The percentage chance that an unit's attacks hits 
        stats["Crit"]= 40;          // The percentage chance that an unit's attack does crit damage                                                
        stats["Damage"]= 10;        // The amount of damage an attack does
        stats["Crit Damage"]= 18;
}
