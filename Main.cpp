#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <time.h>

using namespace std;

#include "Character.h"
#include "Archer.h"
#include "Barbarian.h"
#include "Cavalier.h"
#include "Cleric.h"
#include "DarkMage.h"
#include "Fighter.h"
#include "Knight.h"
#include "Lord.h"
#include "Mage.h"
#include "Mercenary.h"
#include "Myrmidon.h"
#include "PegasusKnight.h"
#include "Tactician.h"
#include "Thief.h"
#include "Troubadour.h"
#include "WyvernRider.h"

void gameSetup();
void playerTurn();
void checkParty();
void enemyTurn();
void characterInitialization();
void enemyInitialization();

Character characters[32];
Character enemies[6];
Character party[6];
bool playerLoss = false;
bool enemyLoss = false;

int main()
{
	characterInitialization(); //Creates all of the game's characters
	gameSetup(); //Prompts user to create party
    enemyInitialization(); //Creates all of the enemies

	cout << endl << "GAME START" << endl;
	bool end = false;
    while(!end) //Plays the game
    {
		playerTurn();
		checkParty();
		if(playerLoss)
		{
			cout << "GAME OVER" << endl;
			end = true;
			break;
		}
		enemyTurn();
		checkParty();
		if(enemyLoss)
		{
			cout << "BATTLE WON" << endl;
			end = true;
			break;
		}
    }
}

void gameSetup()
{
	string choice1;
	int choice2;
	int count=0;
	int i, j;
	bool back, part1=true;
	cout << "WELCOME TO THE FIRE EMBLEM BATTLE SIMULATOR" << endl << endl;
	cout << "Choose your team" << endl;
	while(part1)
	{
		back = false;
		for(i=0; i<32; i++)
		{
			for(j=0; j<6; j++)
			{
				if(characters[i].getName().compare(party[j].getName())!=0)
				{
					cout << characters[i].getName() << endl;
					break;
				}
			}
		}
		cout << "Select a character to view more info or add to party" << endl;
		cout << "Select 1 to view your current party" << endl;
		cin >> choice1;
		if(choice1.compare("1")==0)
		{
			for(j=0; j<6; j++)
			{
				if(party[j].getName().compare("Name")!=0)
					cout << party[j].getName() << endl;
			}
			back = true;
		}
		while(!back)
		{
			cout << "1 View character information" << endl;
			cout << "2 Add character to party" << endl;
			cout << "3 Retrun to character selection" << endl;
			cin >> choice2;
			if(choice2==1)
			{
				for(i=0; i<32; i++)
				{
					if(choice1.compare(characters[i].getName())==0)
						characters[i].displayInfo();
				}
			}
			else if(choice2==2)
			{
				for(i=0; i<32; i++)
				{
					if(choice1.compare(characters[i].getName())==0)	
						party[count] = characters[i];
				}
				count++;
				back = true;
				break;
			}
			else if(choice2==3)
			{
				back = true;
				break;
			}
		}
		if(count==6)
			part1 = false;
	}
}

void playerTurn()
{
	int upgrades = 2, heals = 5;
	bool turnOver = false;
	bool canGo[6] = true;
	while(!turnOver)
	{
		//Print board
		string choice1;
		int choice2, choice3, choice4, choice5, choice6;
		for(int p=0; p<6; p++)
		{
			if(canGo[p])
				cout << party[p].getName() << " ";
		}
		cout << endl;
		cout << "Select a character by inputting their name." << endl;
		cout << "Select q to end your turn." << endl;
		cin >> choice1;
		if(choice1.compare(party[0].getName()) && canGo[0])
		{
			choice2 = 0;
		}
		else if(choice1.compare(party[1].getName()) && canGo[1])
		{
			choice2 = 1;
		}
		else if(choice1.compare(party[2].getName()) && canGo[2])
		{
			choice2 = 2;
		}
		else if(choice1.compare(party[3].getName()) && canGo[3])
		{
			choice2 = 3;
		}
		else if(choice1.compare(party[4].getName()) && canGo[4])
		{
			choice2 = 4;
		}
		else if(choice1.compare(party[5].getName()) && canGo[5])
		{
			choice2 = 5;
		}
		else if(choice1.compare("q") || (!canGo[0] && !canGo[1] && !canGo[2] && !canGo[3] && !canGo[4] && !canGo[5]))
		{
			turnOver = true;
			break;
		}
		if(turnOver)
			break;
		bool pTurnOver = false;
		bool turnUsed = false;
		while(!pTurnOver)
		{
			cout << party[choice2].getName() << endl;
			cout << "1 Move" << endl;
			cout << "2 Item" << endl;
			cout << "3 View Info" << endl;
			cout << "4 Go Back" << endl;
			cin >> choice3;
			if(choice3==1)
			{
				//Move around board, if move into enemy, attack, if attacked, pTurnOver = true
				cout << "1 Item" << endl;
				cout << "2 End Character Turn" << endl;
				cin >> choice4;
				if(choice4==1)
				{
					cout << "1 Upgrade Character" << endl;
					cout << "2 Heal Character" << endl;
					cout << "3 Go Back" << endl;
					cin >> choice5;
					if(choice5==1)
					{
						if(upgrades>0)
						{
							party[choice2].upgradeClass();
							upgrades--;
							pTurnOver = true;
							turnUsed = true;
						}
						else
						{
							cout << "Out of upgrades" << endl;
							break;
						}
					}
					else if(choice5==2)
					{
						if(heals>0)
						{
							party[choice2].healDamage(10);
							heals--;
							pTurnOver = true;
							turnUsed = true;
						}
						else
						{
							cout << "Out of heals" << endl;
							break;
						}
					}
					else if(choice5==3)
					{
						break;
					}
					if(choice5==3)
						break;
				}
				else if(choice4==2)
				{
					pTurnOver = true;
					turnUsed = true;
					break;
				}
				if(choice5==3)
						break;
				if(pTurnOver)
					break;
			}
			else if(choice3==2)
			{
				cout << "1 Upgrade Character" << endl;
				cout << "2 Heal Character" << endl;
				cout << "3 Go Back" << endl;
				cin >> choice6;
				if(choice6==1)
				{
					if(upgrades>0)
					{
						party[choice2].upgradeClass();
						upgrades--;
						pTurnOver = true;
						turnUsed = true;
					}
					else
					{
						cout << "Out of upgrades" << endl;
						break;
					}
				}
				else if(choice6==2)
				{
					if(heals>0)
					{
						party[choice2].healDamage(10);
						heals--;
						pTurnOver = true;
						turnUsed = true;
					}
					else
					{
						cout << "Out of heals" << endl;
						break;
					}
				}
				else if(choice6==3)
				{
					break;
				}
			}
			else if(choice3==3)
			{
				party[choice2].displayInfo();
				break;
			}
			else if(choice3==4)
			{
				pTurnOver = true;
				break;
			}
		}
		if(turnUsed)
		{
			canGo[choice2] = false;
		}
	}
}

void checkParty()
{
	cout << "CHECKS PARTY" << endl;
}

void enemyTurn()
{
	cout << "ENEMY TURN" << endl;
}

void characterInitialization() //Initializes all of the characters with their given class constructors
{
	characters[0] = Archer("Virion", "Archer", false, 19, 19, 60, 70, 40, 5, 15, 0);
    characters[1] = Archer("Noire", "Acher", false, 13, 13, 70, 65, 40, 8, 20, 0);
    characters[2] = Barbarian("Bjorn", "Barbarian", false, 22, 22, 40, 60, 20, 8, 18, 0);
    characters[3] = Barbarian("Garrick", "Barbarian", false, 20, 20, 50, 70, 30, 9, 20, 0);
    characters[4] = Cavalier("Stahl", "Cavalier", false, 22, 22, 87, 65, 55, 8, 18, 0);
    characters[5] = Cavalier("Sully", "Cavalier", false, 20, 20, 87, 50, 65, 7, 18, 0);
    characters[6] = Cleric("Lissa", "Cleric", false, 20, 20, 70, 100, 0, 0, 0, 10);
    characters[7] = Cleric("Brady", "Cleric", false, 18, 18, 75, 100, 0, 0, 0, 9);
    characters[8] = DarkMage("Henry", "Dark Mage", false, 17, 17, 55, 80, 50, 10, 18, 0);
    characters[9] = DarkMage("Tharja", "Dark Mage", false, 11, 11, 60, 70, 40, 11, 19, 0);
    characters[10] = Fighter("Vaike", "Fighter", false, 24, 24, 50, 65, 45, 9, 18, 0);
    characters[11] = Fighter("Malice", "Fighter", false, 22, 22, 75, 60, 50, 10, 20, 0);
    characters[12] = Knight("Kellam", "Knight", false, 35, 25, 35, 65, 45, 9, 20, 0);
    characters[13] = Knight("Kjelle", "Knight", false, 30, 21, 50, 90, 70, 7, 15, 0);
    characters[14] = Lord("Chrom", "Lord", false, 21, 21, 60, 90, 60, 7, 12, 0);
    characters[15] = Lord("Lucina", "Lord", false, 22, 22, 63, 90, 70, 9, 17, 0);
    characters[16] = Mage("Ricken", "Mage", false, 20, 20, 50, 70, 65, 8, 18, 0);
    characters[17] = Mage("Miriel", "Mage", false,21, 21, 65, 75, 50, 6, 12, 0);
    characters[18] = Mercenary("Gregor", "Mercenary", false, 22, 22, 65, 50, 12, 20, 0);
    characters[19] = Mercenary("Severa", "Mercenary", false, 28, 28, 55, 85, 10, 18, 0);
    characters[20] = Myrmidon("Lon'qu", "Myrmidon", false, 20, 20, 75, 65, 55, 6, 13,0);
    characters[21] = Myrmidon("Owain", "Myrmidon", false, 15, 15, 45, 85, 50, 8, 17, 0);
    characters[22] = PegasusKnight("Sumia","Pegasus Knight", false, 18, 18, 70, 70, 60, 6, 17, 0);
    characters[23] = PegasusKnight("Cordelia", "Pegasus Knight", false, 25, 25, 60, 60, 45, 9, 18, 0);
    characters[24] = Tactician("Robin", "Tactician", false, 19, 19, 50, 85, 55, 9, 18, 0);
    characters[25] = Tactician("Morgan", "Tactician", false, 19, 19, 70, 85, 55, 9, 18, 0);
    characters[26] = Thief("Gaius", "Thief", false, 24, 24, 70, 80, 40, 7, 13, 0);
    characters[27] = Thief("Anna", "Thief", false, 20, 20, 60, 73, 30, 8, 19, 0);
    characters[28] = Troubadour("Maribelle", "Troubadour", false, 18, 18, 70, 100, 0, 0, 0, 10);
    characters[29] = Troubadour("Libra", "Troubadour", false, 22, 22, 65, 100, 0, 0, 0, 15);
    characters[30] = WyvernRider("Cherche", "Wyvern Rider", false, 25, 25, 60, 80, 50, 14, 23, 0);
    characters[31] = WyvernRider("Gerome", "Wyvern Rider", false, 22, 22, 55, 70, 40, 10, 19, 0);
}

void enemyInitialization() //Initializes all of the enemies with random info
{						   //For each class, have a different range of numbers between which all of the stats are randomized
    srand( time( NULL ) );
    for(int i=0; i<6; i++) //Do the same process for 6 different enemies to be put into the enemy array
    {
        switch(rand()%16+1) //In order to randomize class, must switch between the 16 different cases
        {
            case 1:
            {
                int dam = rand()%2+6;
				int hp = rand()%6+13;
                enemies[i] = Character("Enemy " + to_string(i+1), "Archer", false, hp, hp, rand()%10+60, rand()%5+65, rand()%40+30, dam, dam*3, 0);
                break;
            }
            case 2:
            {
                int dam = rand()%1+9;
				int hp = rand()%3+17;
                enemies[i] = Character("Enemy " + to_string(i+1), "Barbarian", false, hp, hp, rand()%15+60, rand()%25+30, rand()%20+30, dam, dam*3, 0);
                break;
            }
            case 3:
            {
                int dam = rand()%1+7;
				int hp = rand()%5+25;
                enemies[i] = Character("Enemy " + to_string(i+1), "Cavalier", false, hp, hp, rand()%15+50, rand()%15+65, rand()%10+50, dam, dam*3, 0);
                break;
            }
            case 4:
            {
                int heal = rand()%2+7;
				int hp = rand()%2+18;
                enemies[i] = Character("Enemy " + to_string(i+1), "Cleric", false, hp, hp, rand()%10+60, 100, 0, 0, 0, heal);
                break;
            }
            case 5:
            {
                int dam = rand()%2+10;
				int hp = rand()%6+11;
                enemies[i] = Character("Enemy " + to_string(i+1), "Dark Mage", false, hp, hp, rand()%5+55, rand()%10+70, rand()%10+30, dam, dam*3, 0);
                break;
            }
            case 6:
            {
                int dam = rand()%2+9;
				int hp = rand()%2+22;
                enemies[i] = Character("Enemy " + to_string(i+1), "Fighter", false, hp, hp, rand()%10+50, rand()%15+55, rand()%10+45, dam, dam*3, 0);
                break;
            }
            case 7:
            {
                int dam = rand()%1+9;
				int hp = rand()%5+30;
                enemies[i] = Character("Enemy " + to_string(i+1), "Knight", false, hp, hp, rand()%15+15, rand()%15+65, rand()%20+45, dam, dam*3, 0);
                break;
            }
            case 8:
            {
                int dam = rand()%4+8;
				int hp = rand()%1+20;
                enemies[i] = Character("Enemy " + to_string(i+1), "Lord", false, hp, hp, rand()%10+60, rand()%5+85, rand()%10+40, dam, dam*3, 0);
                break;
            }
            case 9:
            {
                int dam = rand()%1+7;
				int hp = rand()%2+20;
                enemies[i] = Character("Enemy " + to_string(i+1), "Mage", false, hp, hp, rand()%10+50, rand()%5+70, rand()%15+50, dam, dam*3, 0);
                break;
            }
            case 10:
            {
                int dam = rand()%2+10;
				int hp = rand()%10+20;
                enemies[i] = Character("Enemy " + to_string(i+1), "Mercenary", false, hp, hp, rand()%15+35, rand()%30+65, rand()%20+25, dam, dam*3, 0);
                break;
            }
            case 11:
            {
                int dam = rand()%2+6;
				int hp = rand()%5+15;
                enemies[i] = Character("Enemy " + to_string(i+1), "Myrmidon", false, hp, hp, rand()%40+35, rand()%30+65, rand()%5+50, dam, dam*3, 0);
                break;
            }
            case 12:
            {
                int dam = rand()%1+6;
				int hp = rand()%3+15;
                enemies[i] = Character("Enemy " + to_string(i+1), "Pegasus Knight", false, hp, hp, rand()%10+60, rand()%10+60, rand()%15+45, dam, dam*3, 0);
                break;
            }
            case 13:
            {
                int dam = rand()%2+7;
				int hp = rand()%4+19;
                enemies[i] = Character("Enemy " + to_string(i+1), "Tactician", false, hp, hp, rand()%20+50, rand()%10+80, rand()%5+45, dam, dam*3, 0);
                break;
            }
            case 14:
            {
                int dam = rand()%2+7;
				int hp = rand()%4+18;
                enemies[i] = Character("Enemy " + to_string(i+1), "Thief", false, hp, hp, rand()%10+60, rand()%10+65, rand()%10+35, dam, dam*3, 0);
                break;
            }
            case 15:
            {
                int heal = rand()%3+5;
				int hp = rand()%3+15;
                enemies[i] = Character("Enemy " + to_string(i+1), "Troubadour", false, hp, hp, rand()%20+50, 100, 0, 0, 0, heal);
                break;
            }
            case 16:
            {
                int dam = rand()%3+11;
				int hp = rand()%3+22;
                enemies[i] = Character("Enemy " + to_string(i+1), "Wyvern Rider", false, hp, hp, rand()%5+50, rand()%15+60, rand()%10+40, dam, dam*3, 0);
                break;
            }
        }
    }
}
