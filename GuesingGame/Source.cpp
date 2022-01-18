#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>

using namespace std;

struct playerInfo
{
	string playerName;
	unsigned short int playerAge{};
}p_playerInfo;


int randomNumber();
int maxTries;
int origMaxTries;
vector<int> playerGuess;
void printASCIIArt(int winlose);
void setMaxTriesLimit();
void playAgain();


auto main() -> int
{
	int generatedNumber = randomNumber();
	int playerInput;


	cout << R"(
				=============================================================
				                    WELCOME TO GUESING GAME                  
				=============================================================
	)" << "\n\n";

	if (p_playerInfo.playerName == "")
	{
		setMaxTriesLimit();

		cout << "Enter your name: ";
		cin >> p_playerInfo.playerName;

		do
		{
			cout << "Enter your age: ";
			cin >> p_playerInfo.playerAge;
			if (p_playerInfo.playerAge > 0)
			{
				break;
			}
			else
			{
				cout << "Invalid input. Please try again.\n";
				cin.clear();
				cin.ignore(numeric_limits<int>::max(), '\n');
			}

		} while (true);
	}

	cout << "\n\n#########################################################################################\n";

	cout << "You have " << maxTries << " tries give your best shot.\n\n";

	while(true)
	{
		cout << "Guess a number between 1 to 100: " << generatedNumber << ": ";
		cin >> playerInput;
		

		if (playerInput < 0)
		{
			break;
		}
		else
		{
			if (playerInput > 100)
			{
				cout << "\nInvalid input. Only choose numbers between 1 to 100.\n\n";
				cout << "===============================================\n\n";
			}
			else
			{
				//this need to be validated again for not breaking the loop
				if (playerInput <= 0)
				{
					cout << "\nInvalid input. Please try again.\n";

					//stopping the cin to interfere
					cin.clear();
					cin.ignore(numeric_limits<int>::max(), '\n'); //filter \n 
				}
				else {
					//add guessed number to vector array
					playerGuess.push_back(playerInput);
					
					if (generatedNumber > playerInput)
					{
						maxTries--;
						cout << "\nThe number is LOWER try again.\n";
						cout << "You have " << maxTries << " try left.\n\n";
						cout << "===============================================\n\n";
							
					}
					else if (generatedNumber < playerInput)
					{
						maxTries--;
						cout << "\nThe number is HIGHER try again.\n";
						cout << "You have " << maxTries << " try left.\n\n";
						cout << "===============================================\n\n";
					}
					else if (generatedNumber == playerInput)
					{
						printASCIIArt(1);

						playAgain();
					}
					else
					{
						cout << "\nInvalid input try gain.\n";
					}

					if (maxTries < 1)
					{
						printASCIIArt(2);

						playAgain();
					}
				}
			}
		}
	}
	
	return EXIT_SUCCESS;
}

void setMaxTriesLimit()
{
	do
	{
		cout << "Enter maximum guess: ";
		cin >> maxTries;

		origMaxTries = maxTries;
		if (maxTries > 0)
		{
			break;
		}
		else
		{
			cout << "Invalid input. Please try again.\n";
			cin.clear();
			cin.ignore(numeric_limits<int>::max(), '\n');
		}

	} while (true);
}

void playAgain()
{
	int choiceInput;

	cout << "You wanna play again?! Press 1 then hit Enter. ";
	cin >> choiceInput;
	if (choiceInput == 1)
	{
		playerGuess.clear(); //clear vector
		maxTries = origMaxTries; //re-init maxTries
		system("CLS"); //clear screen
		main(); //restarting the game
	}
	else
	{
		exit(0);
	}
}

void printASCIIArt(int winlose)
{
	cout << "#########################################################################################\n";
	cout << "Name: " << p_playerInfo.playerName << "\n";
	cout << "Age: " << p_playerInfo.playerAge << "\n";
	cout << "Tries left: " << maxTries << "\n";
	cout << "Tried numbers: [";
	for (int i = 0; i < playerGuess.size(); i++)
	{
		cout << playerGuess[i];
		if (i >= 0 && ((i+1) <= playerGuess.size() - 1))
		{
			cout << ", ";
		}
	}
	cout << "]\n";
	cout << "#########################################################################################\n";

	switch (winlose)
	{
		case 1:
			
			cout << R"(
						 _______________
						|@@@@|     |####|
						|@@@@|     |####|
						|@@@@|     |####|
						\@@@@|     |####/
						 \@@@|     |###/
						  `@@|_____|##'
						       (O)
						    .-'''''-.
						  .'  * * *  `.
						 :  *       *  :
						: ~  Y  O  U  ~ :
						: ~  W  I  N  ~ :
						 :  *       *  :
						  `.  * * *  .'
						    `-.....-'
		)" << "\n\n";
			break;
		case 2:
			cout << R"( 
						   .------\ /------.
						   |       -       |
						   |     Y O U     |
						   |    L O S E    |
						   |               |
						_______________________
						===========.===========
						  / ~~~~~     ~~~~~ \
						 /|     |     |\    |\
						 W   ---  / \  ---   W
						 \.      |o o|      ./
						  |                 |
						  \    #########    /
						   \  ## ----- ##  /
						    \##         ##/
						     \_____v_____/
		)" << "\n\n";
			break;
	}
}

int randomNumber()
{
	/* initialize random seed: */
	srand(time(NULL));

	/* generate secret number between 1 and 100: */
	return rand() % 100 + 1;
}