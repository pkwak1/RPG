#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <time.h>
#include <math.h>

using namespace std;

// character classes included
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

#define ROWS 8
#define COLS 8

// function prototypes
void boardInitialization();
void gameSetup();
void playerTurn();
void checkParty();
void enemyTurn();
void characterInitialization();
void enemyInitialization();
char int_to_terrain(int i);
void printMap(int d[][COLS]);
void erase(int d[][COLS], string playerSelect);
bool move(int d[][COLS], string playerSelect, char move);
void fight(int, int, int);
double dForm(int enemy, int character);
void emove(int enemy, int character, bool fight);
void efight(int enemy, int character);

Character characters[32];
Character enemies[6];
Character party[6];
bool playerLoss = false;
bool enemyLoss = false;
int upgrades = 2;
int heals = 5;
bool triedToGoThroughCharacter = false;

int d[ROWS][COLS]={ // board array
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
  	{0,0,0,0,0,0,0,0}};

int main()
{
	boardInitialization();
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
		else if(enemyLoss)
		{
			cout << "BATTLE WON" << endl;
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
		else if(playerLoss)
		{
			cout << "GAME OVER" << endl;
			end = true;
			break;
		}
    }
}

void boardInitialization() // determining where player and enemy appear at the start of battle
{
	int i, j;
	srand(time(NULL));
	int enemyRandomRow[6];
	int enemyRandomCol[6];
	int playerRandomRow[6];
	int playerRandomCol[6];
	for(i=0; i<6; i++) // randomizing enemy appearance
	{
		enemyRandomRow[i] = rand()%3+0;
		enemyRandomCol[i] = rand()%7+0;
		playerRandomRow[i] = rand()%3+4;
		playerRandomCol[i] = rand()%7+0;
	}
	for(i=0; i<6; i++)
	{
		for(j=i+1; j<6; j++)
		{
			if(enemyRandomRow[i]==enemyRandomRow[j] && enemyRandomCol[i]==enemyRandomCol[j])
			{
				enemyRandomRow[j] = rand()%3+0;
				enemyRandomCol[j] = rand()%7+0;
			}
			if(playerRandomRow[i]==playerRandomRow[j] && playerRandomCol[i]==playerRandomCol[j])
			{
				playerRandomRow[j] = rand()%3+4;
				playerRandomCol[j] = rand()%7+0;
			}
		}
	}
	for(i=0; i<6; i++)
	{
		for(int j=i+1; j<6; j++)
		{
			if(enemyRandomRow[i]==enemyRandomRow[j] && enemyRandomCol[i]==enemyRandomCol[j])
			{
				enemyRandomRow[j] = rand()%3+0;
				enemyRandomCol[j] = rand()%7+0;
			}
			if(playerRandomRow[i]==playerRandomRow[j] && playerRandomCol[i]==playerRandomCol[j])
			{
				playerRandomRow[j] = rand()%3+4;
				playerRandomCol[j] = rand()%7+0;
			}
		}
	}
	for(i=0; i<6; i++)
	{
		d[enemyRandomRow[i]][enemyRandomCol[i]] = i+2;
		d[playerRandomRow[i]][playerRandomCol[i]] = i+8;
	}
}

void gameSetup() // creating your party team of six players at the start of the game
{
	string choice1;
	int choice2;
        string choice2s;
	int count=0;
	int i, j;
	bool back, part1=true;
	cout << "WELCOME TO THE FIRE EMBLEM BATTLE SIMULATOR" << endl << endl;
	cout << "Choose your team (6 characters)" << endl;
	while(part1) // first part of the game. Initializing the party and possible options that the player can do.
	{
		back = false;
		for(i=0; i<8; i++)
		{
			for(j=0; j<6; j++)
			{
				if(characters[i].getName().compare(party[j].getName())!=0)
				{
					cout << characters[i].getName() << "\t";
					break;
				}
			}
		}
		cout << endl;
		for(i=8; i<16; i++)
		{
			for(j=0; j<6; j++)
			{
				if(characters[i].getName().compare(party[j].getName())!=0)
				{
					cout << characters[i].getName() << "\t";
					break;
				}
			}
		}
		cout << endl;
		for(i=16; i<24; i++)
		{
			for(j=0; j<6; j++)
			{
				if(characters[i].getName().compare(party[j].getName())!=0)
				{
					cout << characters[i].getName() << "\t";
					break;
				}
			}
		}
		cout << endl;
		for(i=24; i<32; i++)
		{
			for(j=0; j<6; j++)
			{
				if(characters[i].getName().compare(party[j].getName())!=0)
				{
					cout << characters[i].getName() << "\t";
					break;
				}
			}
		}
		cout << endl;
		cout << "Select a character to view more info or add to party" << endl;
		cout << "Select 1 to view your current party" << endl;

                bool reUse = false;
                bool exists = false;

		cin >> choice1;

                for( int jINeedThis = 0; jINeedThis < 6; jINeedThis++)
                {
                     if(( choice1.compare(party[jINeedThis].getName()) == 0 ))
                     {
                          reUse = true;
                     }
                }
                for( int kNeedThis = 0; kNeedThis < 32; kNeedThis++ )
                {
                     if(( choice1.compare(characters[kNeedThis].getName()) == 0 ))
                     {
                          exists = true;
                     }
                }

		if(choice1.compare("1")==0)
		{
			for(j=0; j<6; j++)
			{
				if(party[j].getName().compare("Name")!=0)
					cout << party[j].getName() << " ";
			}
			cout << endl << endl;
			back = true;
		}
                else if(( reUse ))
                {
                    cout << "Party member already chosen." << endl << endl;
                    continue;
                }
                else if(( !exists ))
                {
                     cout << "Please enter a valid name." << endl << endl;
                     continue;
                }

		while(!back)
		{
			cout << "1 View character information" << endl;
			cout << "2 Add character to party" << endl;
			cout << "3 Return to character selection" << endl;
			cin >> choice2s;

                        for( int strIt = 0; strIt < choice2s.size(); strIt++ )
                        {
                            if(( !(isdigit( choice2s[ strIt ] ) ) ))
                            {
                                cout << "Don't input strings. Just don't." << endl;
                                continue;
                            }
                        }
                        choice2 = stoi( choice2s );

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

void playerTurn() // the function that helps determine the possible actions the player can do for the player turn
{
	bool turnOver = false;
	bool canGo[6] = {true, true, true, true, true, true};
	char move_select;
	cout << "PLAYER TURN" << endl;
	while(!turnOver) // as long as the player has units that can do something and are not dead. All choices for each of the six party units are implemented in similar manner.
	{
		// Print board
		printMap(d);
		// Movement over
		if(!canGo[0] && !canGo[1] && !canGo[2] && !canGo[3] && !canGo[4] && !canGo[5])
		{
			cout << "TURN OVER" << endl;
			turnOver = true;
			break;
		}
		string choice1;
		int choice2, choice3, choice4, choice5, choice6;
                string choice3s, choice4s, choice5s, choice6s;
		int numMoves = 3;
		bool pTurnOver = false;
		bool turnUsed = false;
		bool moving = true;
		int r, c;

		cout << endl;
		for(r=0; r<8; r++)
		{
			for(c=0; c<8; c++)
			{
				if(8<=d[r][c] && d[r][c]<=13 && canGo[d[r][c]-8])
				{
					cout << party[d[r][c]-8].getName() << " (" << r << ", " << char(c+65) << ") ";
				}
			}
		}
		cout << endl;
		for(r=0; r<8; r++)
		{
			for(c=0; c<8; c++)
			{
				if(2<=d[r][c] && d[r][c]<=7)
				{
					cout << enemies[d[r][c]-2].getName() << " (" << r << ", " << char(c+65) << ") ";
				}
			}
		}
		cout << endl;
		cout << "Select a character by inputting their name." << endl;
		cout << "Select an enemy number to view their information." << endl;
		cout << "Select q to end your turn." << endl;
		cin >> choice1;

                bool exists2 = false;

                for( int blarg = 0; blarg < 6; blarg++ )
                {
                    if(( choice1.compare(party[blarg].getName()) == 0 ))
                    {
                        exists2 = true;
                    }
                    else if(( choice1.compare( "1" ) == 0 ))
                    {
                        exists2 = true;
                    }
                    else if(( choice1.compare( "2" ) == 0 ))
                    {
                        exists2 = true;
                    }
                    else if(( choice1.compare( "3" ) == 0 ))
                    {
                        exists2 = true;
                    }
                    else if(( choice1.compare( "4" ) == 0 ))
                    {
                        exists2 = true;
                    }
                    else if(( choice1.compare( "5" ) == 0 ))
                    {
                        exists2 = true;
                    }
                    else if(( choice1.compare( "6" ) == 0 ))
                    {
                        exists2 = true;
                    }
                    else if(( choice1.compare( "q" ) == 0 ))
                    {
                        exists2 = true;
                    }
                }

                if(( !exists2 ))
                {
                    cout << "Please enter a valid command." << endl << endl;
                    continue;
                }
		else if(choice1.compare(party[0].getName())==0 && canGo[0])
		{
			choice2 = 0;
		}
		else if(choice1.compare(party[1].getName())==0 && canGo[1])
		{
			choice2 = 1;
		}
		else if(choice1.compare(party[2].getName())==0 && canGo[2])
		{
			choice2 = 2;
		}
		else if(choice1.compare(party[3].getName())==0 && canGo[3])
		{
			choice2 = 3;
		}
		else if(choice1.compare(party[4].getName())==0 && canGo[4])
		{
			choice2 = 4;
		}
		else if(choice1.compare(party[5].getName())==0 && canGo[5])
		{
			choice2 = 5;
		}
		else if(choice1.compare("1")==0)
		{
			enemies[0].displayInfo();
			pTurnOver = true;
		}
		else if(choice1.compare("2")==0)
		{
			enemies[1].displayInfo();
			pTurnOver = true;
		}
		else if(choice1.compare("3")==0)
		{
			enemies[2].displayInfo();
			pTurnOver = true;
		}
		else if(choice1.compare("4")==0)
		{
			enemies[3].displayInfo();
			pTurnOver = true;
		}
		else if(choice1.compare("5")==0)
		{
			enemies[4].displayInfo();
			pTurnOver = true;
		}
		else if(choice1.compare("6")==0)
		{
			enemies[5].displayInfo();
			pTurnOver = true;
		}
		else if(choice1.compare("q")==0)
		{
			cout << "TURN OVER" << endl;
			turnOver = true;
			break;
		}
		else
		{
			cout << "Please enter valid option." << endl;
			pTurnOver = true;
			turnOver = false;
			break;
		}
		if(turnOver)
			break;
		while(!pTurnOver)
		{
			cout << "1 Move" << endl;
			cout << "2 Item" << endl;
			cout << "3 View Info" << endl;
			cout << "4 Go Back" << endl;
			cin >> choice3s;

                        for( int boodles = 0; boodles < choice3s.size(); boodles++ )
                        {
                            if(( !(isdigit( choice3s[boodles] ) ) ))
                            {
                                cout << "I warned you about the strings bro." << endl;
                                continue;
                            }
                        }

                        choice3 = stoi( choice3s );

			if(choice3==1)
			{
				//Move around board, if move into enemy, attack, if attacked, pTurnOver = true
				while(numMoves>0 && moving)
				{
					cout << "Move character. " << numMoves << " moves left."<< endl;
			        cout << "w (up)  a (left)  s (down)  d (right)  e (stop moving)" << endl;
			        cin >> move_select;
					if(move_select=='e')
					{
						moving = false;
						break;
					}
					else
					{
						moving = move(d, party[choice2].getName(), move_select);
						if(!triedToGoThroughCharacter)
							numMoves--;
						if(moving)
							printMap(d);
					}
				}
				if(!moving)
				{
					pTurnOver = true;
					turnUsed = true;
					break;
				}
				cout << "1 Item" << endl;
				cout << "2 End Character Turn" << endl;
				cin >> choice4s;

                                for( int spinnies = 0; spinnies < choice4s.size(); spinnies++ )
                                {
                                     if(( !(isdigit(choice4s[spinnies]) ) ))
                                     {
                                          cout << "PICK A GOD AND PRAY!" << endl;
                                          continue;
                                      }
                                }

                                choice4 = stoi( choice4s );

				if(choice4==1)
				{
					cout << "1 Upgrade Character" << endl;
					cout << "2 Heal Character" << endl;
					cout << "3 Go Back" << endl;
					cin >> choice5s;

                                        for( int levin = 0; levin < choice5s.size(); levin++ )
                                        {
                                             if(( !(isdigit(choice5s[levin]) ) ))
                                             {
                                                 cout << "Now Im angry!" << endl;
                                                 continue;
                                             }
                                        }

                                        choice5 = stoi( choice5s );

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
							pTurnOver = true;
							turnUsed = true;
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
							pTurnOver = true;
							turnUsed = true;
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
				cin >> choice6s;

                                for( int validar = 0; validar < choice6s.size(); validar++ )
                                {
                                     if(( !(isdigit(choice6s[validar]) ) ))
                                     {
                                         cout << "Now youve angered me." << endl;
                                         continue;
                                     }
                                }

                                choice6 = stoi(choice6s);

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

void checkParty() // determining how many party members have been killed and how many enemies have been killed
{
	int playerDeadCount = 0;
	int enemyDeadCount = 0;
	for(int p=0; p<6; p++)
	{
		if(party[p].isDead())
			playerDeadCount++;
	}
	if(playerDeadCount>=6)
	{
		playerLoss = true;
	}
	for(int e=0; e<6; e++)
	{
		if(enemies[e].isDead())
			enemyDeadCount++;
	}
	if(enemyDeadCount>=6)
	{
		enemyLoss = true;
	}
}

void enemyTurn() // the AI for the enemy attacking the player and what the enemy prioritizes in attacking
{
  int lowestHP = 50;
  int charWithLowest = -1;
  int smallestDistance = 8;
  int charWithSmallest = 0;
  int distance, enemyX, enemyY, characterX, characterY, diffX, diffY, i;
  bool pathClear = true; //CHANGE THIS LATER
  cout << "ENEMY TURN" << endl;

  for(int e=0; e<6; e++)
  {
  	cout << enemies[e].getName() << "'s turn" << endl;
    for(int p=0; p<6; p++)
    {
      if(dForm(e+2, p+8) == 3.0 || dForm(e+2, p+8) <= 2.0)
      {
      	for(int r=0; r<8; r++)
		{
		    for(int c=0; c<8; c++)
		    {
	  			if(d[r][c]==e+2)
		      	{
		        	enemyX = r;
		    	    enemyY = c;
		      	}
		      	else if(d[r][c]==p+8)
		      	{
		        	characterX = r;
		        	characterY = c;
		      	}
		   	}
		}
		diffX = enemyX - characterX;
		diffY = enemyY - characterY;
		if(diffX==0)
		{
			if(diffY>0)
			{
				if(diffY!=1)
				{
					for(i=characterY+1; i<enemyY; i++)
					{
						if(d[enemyX][i]!=0)
							pathClear = false;
					}
				}
			}
			else if(diffY<0)
			{
				if(diffY!=-1)
				{
					for(i=enemyY+1; i<characterY; i++)
					{
						if(d[enemyX][i]!=0)
							pathClear = false;
					}
				}
			}
		}
		else if(diffY==0)
		{
			if(diffX>0)
			{
				if(diffX!=1)
				{
					for(i=characterX+1; i<enemyX; i++)
					{
						if(d[i][enemyY]!=0)
							pathClear = false;
					}
				}
			}
			else if(diffX<0)
			{
				if(diffX!=-1)
				{
					for(i=enemyX+1; i<characterX; i++)
					{
						if(d[i][enemyY]!=0)
							pathClear = false;
					}
				}
			}
		}
      	if(pathClear)
      	{
	        if(party[p].getClass().compare("Cleric") || party[p].getClass().compare("Troubadour"))
	        {
	          emove(e+2, p+8, true);
	          efight(e, p);
	          p = 6;
	        }
	        else if(party[p].getHP() < lowestHP)
	        {
	          lowestHP = party[p].getHP();
	          charWithLowest = p;
	        }
	    }
      }
    }
    if(charWithLowest!=-1)
    {
      emove(e+2, charWithLowest+8, true);
      efight(e, charWithLowest);
    }
    else
    {
      for(int r=0; r<8; r++)
      {
        for(int c=0; c<8; c++)
        {
          distance = dForm(e+2, d[r][c]-8);
          if(8<=d[r][c]<=13 && distance<smallestDistance)
          {
            smallestDistance = distance;
            charWithSmallest = d[r][c] - 8;
          }
        }
      }
      emove(e+2, charWithSmallest+8, false);
    }
    printMap(d);
  }
  cout << "ENEMY TURN OVER" << endl;
}

double dForm(int enemy, int character) // determining the distance that an enemy will go with respect to other characters. Enemies will attack a player character within the distance. 
{
  int enemyX, enemyY, characterX, characterY;
  for(int r=0; r<8; r++)
  {
    for(int c=0; c<8; c++)
    {
      if(d[r][c]==enemy)
      {
        enemyX = r;
        enemyY = c;
      }
      else if(d[r][c]==character)
      {
        characterX = r;
        characterY = c;
      }
    }
  }
  return sqrt(pow((enemyX-characterX),2) + pow((enemyY-characterY),2));
}

void emove(int enemy, int character, bool fight) // determining movement of the enemy with respect to other characters
{
  Character enemyChar;
  int enemyX, enemyY, characterX, characterY, moveX, moveY;
  for(int r=0; r<8; r++)
  {
    for(int c=0; c<8; c++)
    {
      if(d[r][c]==enemy)
      {
        enemyX = r;
        enemyY = c;
      }
      else if(d[r][c]==character)
      {
        characterX = r;
        characterY = c;
      }
    }
  }
  moveX = enemyX - characterX;
  moveY = enemyY - characterY;
  if(moveX>3)
    moveX = 3;
  if(moveX<-3)
    moveX = -3;
  if(moveY>3)
    moveY = 3;
  if(moveY<-3)
    moveY = -3;
  if(d[enemyX-moveX][enemyY-moveY]==0)
  {
    d[enemyX-moveX][enemyY-moveY]=enemy;
  	erase(d, enemies[enemy-2].getName());
  }
  if(fight)
  {
  	if(moveX>0)
  		characterX++;
  	else if(moveY>0)
  		characterY--;
  	if(moveX<0)
  		characterX--;
  	else if(moveY<0)
  		characterY++;
  	erase(d, enemies[enemy-2].getName());
  	d[characterX][characterY]=enemy;
  }
}

void efight(int enemy, int character) // displaying the results of the fight and if a player dies
{
  srand(time(NULL));
  int critRoll = rand()%100+1;
  int attackRoll, avoidRoll;
  if(critRoll <= enemies[enemy].getCrit())
  {
    party[character].takeDamage(enemies[enemy].getCritDamage());
    cout << enemies[enemy].getName() << " crits " << party[character].getName() << " and deals " << enemies[enemy].getCritDamage() << " damage!" << endl;
    if(party[character].getHP()<=0)
    {
    	erase(d, party[character].getName());
      	party[character].dies();
    }
  }
  else
  {
    attackRoll = rand()%100+1;
    if(attackRoll <= enemies[enemy].getAccuracy())
    {
      avoidRoll = rand()%100+1;
      if(avoidRoll <= party[character].getAvoid())
      {
        cout << party[character].getName() << " avoided the attack." << endl;
      }
      else
      {
        party[character].takeDamage(enemies[enemy].getDamage());
        cout << enemies[enemy].getName() << " hits " << party[character].getName() << " and deals " << enemies[enemy].getDamage() << " damage!" << endl;
        if(party[character].getHP()<=0)
        {
        	erase(d, party[character].getName());
          	party[character].dies();
          	checkParty();
        }
      }
    }
    else
    {
      cout << enemies[enemy].getName() << " misses " << party[character].getName() << "." << endl;
    }

    if(party[character].getClass().compare("Cleric") && party[character].getClass().compare("Troubadour"))
    {
      attackRoll = rand()%100+1;
      if(attackRoll <= party[character].getAccuracy())
      {
        avoidRoll = rand()%100+1;
        if(avoidRoll <= enemies[enemy].getAvoid())
        {
          cout << enemies[enemy].getName() << " avoided the attack." << endl;
        }
        else
        {
          enemies[enemy].takeDamage(party[character].getDamage());
          cout << party[character].getName() << " hits " << enemies[enemy].getName() << " and deals " << party[character].getDamage() << " damage!" << endl;
          if(enemies[enemy].getHP()<=0)
          {
          	erase(d, enemies[enemy].getName());
           	enemies[enemy].dies();
           	checkParty();
          }
        }
      }
      else
      {
        cout << party[character].getName() << " misses " << enemies[enemy].getName() << "." << endl;
      }
    }

    attackRoll = rand()%100+1;
    if(attackRoll <= enemies[enemy].getAccuracy())
    {
      avoidRoll = rand()%100+1;
      if(avoidRoll <= party[character].getAvoid())
      {
        cout << party[character].getName() << " avoided the attack." << endl;
      }
      else
      {
        party[character].takeDamage(enemies[enemy].getDamage());
        cout << enemies[enemy].getName() << " hits " << party[character].getName() << " and deals " << enemies[enemy].getDamage() << " damage!" << endl;
        if(party[character].getHP()<=0)
        {
        	erase(d, party[character].getName());
          	party[character].dies();
          	checkParty();
        }
      }
    }
    else
    {
      cout << enemies[enemy].getName() << " misses " << party[character].getName() << "." << endl;
    }
  }
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
    characters[18] = Mercenary("Gregor", "Mercenary", false, 22, 22, 75, 75, 20, 12, 18, 0);
    characters[19] = Mercenary("Severa", "Mercenary", false, 28, 28, 60, 85, 25, 10, 20, 0);
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
        switch(rand()%14+1) //In order to randomize class, must switch between the 16 different cases
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
                int dam = rand()%2+10;
				int hp = rand()%6+11;
                enemies[i] = Character("Enemy " + to_string(i+1), "Dark Mage", false, hp, hp, rand()%5+55, rand()%10+70, rand()%10+30, dam, dam*3, 0);
                break;
            }
            case 5:
            {
                int dam = rand()%2+9;
				int hp = rand()%2+22;
                enemies[i] = Character("Enemy " + to_string(i+1), "Fighter", false, hp, hp, rand()%10+50, rand()%15+55, rand()%10+45, dam, dam*3, 0);
                break;
            }
            case 6:
            {
                int dam = rand()%1+9;
				int hp = rand()%5+30;
                enemies[i] = Character("Enemy " + to_string(i+1), "Knight", false, hp, hp, rand()%15+15, rand()%15+65, rand()%20+45, dam, dam*3, 0);
                break;
            }
            case 7:
            {
                int dam = rand()%4+8;
				int hp = rand()%1+20;
                enemies[i] = Character("Enemy " + to_string(i+1), "Lord", false, hp, hp, rand()%10+60, rand()%5+85, rand()%10+40, dam, dam*3, 0);
                break;
            }
            case 8:
            {
                int dam = rand()%1+7;
				int hp = rand()%2+20;
                enemies[i] = Character("Enemy " + to_string(i+1), "Mage", false, hp, hp, rand()%10+50, rand()%5+70, rand()%15+50, dam, dam*3, 0);
                break;
            }
            case 9:
            {
                int dam = rand()%2+10;
				int hp = rand()%10+20;
                enemies[i] = Character("Enemy " + to_string(i+1), "Mercenary", false, hp, hp, rand()%15+35, rand()%30+65, rand()%20+25, dam, dam*3, 0);
                break;
            }
            case 10:
            {
                int dam = rand()%2+6;
				int hp = rand()%5+15;
                enemies[i] = Character("Enemy " + to_string(i+1), "Myrmidon", false, hp, hp, rand()%40+35, rand()%30+65, rand()%5+50, dam, dam*3, 0);
                break;
            }
            case 11:
            {
                int dam = rand()%1+6;
				int hp = rand()%3+15;
                enemies[i] = Character("Enemy " + to_string(i+1), "Pegasus Knight", false, hp, hp, rand()%10+60, rand()%10+60, rand()%15+45, dam, dam*3, 0);
                break;
            }
            case 12:
            {
                int dam = rand()%2+7;
				int hp = rand()%4+19;
                enemies[i] = Character("Enemy " + to_string(i+1), "Tactician", false, hp, hp, rand()%20+50, rand()%10+80, rand()%5+45, dam, dam*3, 0);
                break;
            }
            case 13:
            {
                int dam = rand()%2+7;
				int hp = rand()%4+18;
                enemies[i] = Character("Enemy " + to_string(i+1), "Thief", false, hp, hp, rand()%10+60, rand()%10+65, rand()%10+35, dam, dam*3, 0);
                break;
            }
            case 14:
            {
                int dam = rand()%3+11;
				int hp = rand()%3+22;
                enemies[i] = Character("Enemy " + to_string(i+1), "Wyvern Rider", false, hp, hp, rand()%5+50, rand()%15+60, rand()%10+40, dam, dam*3, 0);
                break;
            }
        }
    }
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* Board and movement */
void printMap(int d[][COLS])
{
    int row, col;

    cout << "  +---+---+---+---+---+---+---+---+" << endl;

    for (row = 0; row < ROWS; ++row)
    {
        cout << row << " |";
        for (col = 0; col < COLS; ++col)
        {
            printf(" %c |", int_to_terrain(d[row][col]) );
            //cout << int_to_terrain(d[row][col]) << "  |";
            //learned some c formatting from Systems Programming
        }
        cout << endl;
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
    }

    cout << "    A   B   C   D   E   F   G   H" << endl;
}


char int_to_terrain(int i)
{
  	    if(i==0){
					return ' ';
				}
        else if(i==1){
					return '.';
				}
        else if(i >= 2 && i <=7){
					return 'E';
				}
        else
        {
			return party[i-8].getName().at(0);
		}
    return ('*');
}

void erase(int d[][COLS], string playerSelect) // erasing a chracter from the previous space when moving the character to another spot.
{
    int col, row, member;
	if(party[0].getName().compare(playerSelect)==0)
		member = 8;
	else if(party[1].getName().compare(playerSelect)==0)
		member = 9;
	else if(party[2].getName().compare(playerSelect)==0)
		member = 10;
	else if(party[3].getName().compare(playerSelect)==0)
		member = 11;
	else if(party[4].getName().compare(playerSelect)==0)
		member = 12;
	else if(party[5].getName().compare(playerSelect)==0)
		member = 13;
	else if(enemies[0].getName().compare(playerSelect)==0)
		member = 2;
	else if(enemies[1].getName().compare(playerSelect)==0)
		member = 3;
	else if(enemies[2].getName().compare(playerSelect)==0)
		member = 4;
	else if(enemies[3].getName().compare(playerSelect)==0)
		member = 5;
	else if(enemies[4].getName().compare(playerSelect)==0)
		member = 6;
	else if(enemies[5].getName().compare(playerSelect)==0)
		member = 7;
	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
			if(member==d[i][j])
			{
				col = j;
				row = i;
			}
		}
	}
    d[row][col] = 0;
    cout << endl;
}

bool move(int d[][COLS], string playerSelect, char move) // moving the characters on the board to another space
{
    int row, col, count;
	int member;
	bool fought = false;

	if(party[0].getName().compare(playerSelect)==0)
		member = 8;
	else if(party[1].getName().compare(playerSelect)==0)
		member = 9;
	else if(party[2].getName().compare(playerSelect)==0)
		member = 10;
	else if(party[3].getName().compare(playerSelect)==0)
		member = 11;
	else if(party[4].getName().compare(playerSelect)==0)
		member = 12;
	else if(party[5].getName().compare(playerSelect)==0)
		member = 13;

	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
			if(member==d[i][j])
			{
				col = j;
				row = i;
			}
		}
	}

    /* clear board for animation */
    // Look at system library
    //
    // Idea:
    /*
        Erase current position by setting col and row pos to 0
        Then have switch(move) case determine new placement of P or E
            That'll be an if condition to decide which one
        w = row + 1; and etc.
    */
		bool valid = true;

		switch(move)
	  {
	    case 'w':
	      row = row - 1;
	     	break;
	    case 'a':
	      col = col - 1;
	      break;
	    case 'd':
	      col = col + 1;
       	break;
			case 's':
	      row = row + 1;
	      break;
	  }

		if(row < 0 || row > 8 || col < 0 || col > 8)
		{
				if(row < 0)
				{
					row = row + 1;
				}
				else if(row > 8)
				{
					row = row - 1;
				}
				else if(col < 0)
				{
					col = col + 1;
				}
				else if(col > 8)
				{
					col = col - 1;
				}
				cout << "Not valid move, try again" << endl;
		}

/*
    if(row < 0 || row > 8 || col < 0 || col > 8)
    {
      continue;
    }
*/
	if(d[row][col]>=2 && d[row][col]<=7)
	{
		if(party[member-8].getClass().compare("Cleric") && party[member-8].getClass().compare("Troubadour"))
		{
			fight(member, row, col);
			if(enemies[d[row][col]-2].isDead())
				erase(d, enemies[d[row][col]-2].getName());
			fought = true;
		}
		else
		{
			triedToGoThroughCharacter = true;
		}
	}
	else if(d[row][col]>=8 && d[row][col]<=13)
	{
		if(party[member-8].getClass().compare("Cleric")==0 || party[member-8].getClass().compare("Troubadour")==0)
		{
			party[d[row][col]-8].healDamage(party[member-8].getHeal());
			cout << party[member-8].getName() << " healed " << party[d[row][col]-8].getName() << endl;
			fought = true;
		}
		else
		{
			triedToGoThroughCharacter = true;
		}
	}
	if(d[row][col]==0 && !fought)
	{
		erase(d, playerSelect);
		if(member==8)
			d[row][col] = 8;
		else if(member==9)
			d[row][col] = 9;
		else if(member==10)
			d[row][col] = 10;
		else if(member==11)
			d[row][col] = 11;
		else if(member==12)
			d[row][col] = 12;
		else if(member==13)
			d[row][col] = 13;
		triedToGoThroughCharacter = false;
	}
	return !fought;
}

void fight(int member, int row, int col)
{
	srand(time(NULL));
	int critRoll = rand()%100+1;
	int attackRoll, avoidRoll;
	if(critRoll <= party[member-8].getCrit())
	{
		enemies[d[row][col]-2].takeDamage(party[member-8].getCritDamage());
		cout << party[member-8].getName() << " crits " << enemies[d[row][col]-2].getName() << " and deals " << party[member-8].getCritDamage() << " damage!" << endl;
		if(enemies[d[row][col]-2].getHP()<=0)
			enemies[d[row][col]-2].dies();
	}
	else
	{
		attackRoll = rand()%100+1;
		if(attackRoll <= party[member-8].getAccuracy())
		{
			avoidRoll = rand()%100+1;
			if(avoidRoll <= enemies[d[row][col]-2].getAvoid())
			{
				cout << enemies[d[row][col]-2].getName() << " avoided the attack." << endl;
			}
			else
			{
				enemies[d[row][col]-2].takeDamage(party[member-8].getDamage());
				cout << party[member-8].getName() << " hits " << enemies[d[row][col]-2].getName() << " and deals " << party[member-8].getDamage() << " damage!" << endl;
				if(enemies[d[row][col]-2].getHP()<=0)
				{
					enemies[d[row][col]-2].dies();
					checkParty();
				}
			}
		}
		else
		{
			cout << party[member-8].getName() << " misses " << enemies[d[row][col]-2].getName() << "." << endl;
		}

		if(enemies[d[row][col]-2].getClass().compare("Cleric") && enemies[d[row][col]-2].getClass().compare("Troubadour"))
		{
			attackRoll = rand()%100+1;
			if(attackRoll <= enemies[d[row][col]-2].getAccuracy())
			{
				avoidRoll = rand()%100+1;
				if(avoidRoll <= party[member-8].getAvoid())
				{
					cout << party[member-8].getName() << " avoided the attack." << endl;
				}
				else
				{
					party[member-8].takeDamage(enemies[d[row][col]-2].getDamage());
					cout << enemies[d[row][col]-2].getName() << " hits " << party[member-8].getName() << " and deals " << enemies[d[row][col]-2].getDamage() << " damage!" << endl;
					if(party[member-8].getHP()<=0)
					{
						party[member-8].dies();
						checkParty();
					}
				}
			}
			else
			{
				cout << enemies[d[row][col]-2].getName() << " misses " << party[member-8].getName() << "." << endl;
			}
		}

		attackRoll = rand()%100+1;
		if(attackRoll <= party[member-8].getAccuracy())
		{
			avoidRoll = rand()%100+1;
			if(avoidRoll <= enemies[d[row][col]-2].getAvoid())
			{
				cout << enemies[d[row][col]-2].getName() << " avoided the attack." << endl;
			}
			else
			{
				enemies[d[row][col]-2].takeDamage(party[member-8].getDamage());
				cout << party[member-8].getName() << " hits " << enemies[d[row][col]-2].getName() << " and deals " << party[member-8].getDamage() << " damage!" << endl;
				if(enemies[d[row][col]-2].getHP()<=0)
				{
					enemies[d[row][col]-2].dies();
					checkParty();
				}
			}
		}
		else
		{
			cout << party[member-8].getName() << " misses " << enemies[d[row][col]-2].getName() << "." << endl;
		}
	}
}
