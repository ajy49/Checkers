#ifndef TOKENIZE_H_INCLUDED
#define TOKENIZE_H_INCLUDED

#include <iostream>
#include "Board.h"
#include "ClearScreen.h"
#include "AI.h"

using std::cout;
using std::cin;

/*This function is used to print the current board positions as well as the game score*/

void displayUpdate(int board[][8], bool turn)
{
	int row = 0, col = 0, coord = 8, blackCount = 0, redCount = 0;

	//Begin by clearing the old board setup
	ClearScreen();

	if (turn = false)
	{
		//CPU's turn
		cout << "\n\n         COMPUTER'S TURN";
	}
	else
	{
		//Player's turn
		cout << "\n\n         PLAYER'S TURN";
	}

	/*Print the current board setup
	Starting with the piece count*/
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if ((board[row][col] == 1) || (board[row][col] == 2))
			{
				blackCount++;
			}
			else if ((board[row][col] == -1) || (board[row][col] == -2))
			{
				redCount++;
			}
		}
	}
	cout << "  Black: " << blackCount << "  Red: " << redCount;

	cout << "\n\n			       #========================================#\n";

	for (row = 0; row < 8; row++)
	{
		if (col == 8)
		{
			cout << "\n			       #----------------------------------------#\n";
		}
		
		cout << "			    ";
		cout << coord;
		coord--;
		cout << "  #";
		
		for (col = 0; col < 8; col++)
		{
			switch (board[row][col])
			{
				//Black Pawn
				case 1:
				{
					cout << "  B  ";
					break;
				}
				//Red Pawn
				case -1:
				{
					cout << "  R  ";
					break;
				}
				//Empty Space
				case 0:
				{
					cout << "     ";
					break;
				}
				//Blank Space
				case 4:
				{
					cout << "|||||";
					break;
				}
				//Black King
				case 2:
				{
					cout << " *B* ";
					break;
				}
				//Red King
				case -2:
				{
					cout << " *R* ";
					break;
				}
			}
		}
	cout << "#";
	}

	cout << "\n			       #========================================#\n";
	cout << "				  A    B    C    D    E    F    G    H    \n";
}

/*This function handles the moves made by the player*/

void movePiece(int board[][8],bool turn , int cpuX, int cpuY, int cpuXFin, int cpuYFin)
{
	int xCoord = 0;
	int yCoord = 0;
	char xCoordLet = 0;

	int xCoordFin = 0;
	int yCoordFin = 0;
	char xCoordLetFin = 0;

	int move = 0;

	if (turn == false)
	{
		xCoord = playerMoveX();
		yCoord = playerMoveY();

		cout << " Move to:\n";

		xCoordFin = playerMoveXFin();
		yCoordFin = playerMoveYFin();

		
	}
	else
	{
		xCoord = cpuX;
		yCoord = cpuY;
		xCoordFin = cpuXFin;
		yCoordFin = cpuYFin;
	}

	//Check the legality and type of move
	move = checkMove(board, yCoord, xCoord, yCoordFin, xCoordFin, turn);

	//Handles moves to empty spaces and returns
	if (move == 1)
	{
		
		//move = 1 moves to blank spaces
		if (board[yCoord][xCoord] == 1)
		{
			//Black to empty space
			board[yCoord][xCoord] = 0;
			if (yCoordFin == 7)
			{
				board[yCoordFin][xCoordFin] = 2;
			}
			else
			{
				board[yCoordFin][xCoordFin] = 1;
			}
			return;
		}
		else if (board[yCoord][xCoord] == -1)
		{
			//Red to empty space
			board[yCoord][xCoord] = 0;
			if (yCoordFin == 0)
			{
				board[yCoordFin][xCoordFin] = -2;
			}
			else
			{
				board[yCoordFin][xCoordFin] = -1;
			}
			return;
		}
		
		
	}

	//Handles king moves and returns
	else if (move == 2)
	{
		if (board[yCoord][xCoord] == 2)
		{
			//Black King to empty space
			board[yCoord][xCoord] = 0;
			board[yCoordFin][xCoordFin] = 2;
			return;

		}
		else if (board[yCoord][xCoord] == -2)
		{
			//Red King to empty space
			board[yCoord][xCoord] = 0;
			board[yCoordFin][xCoordFin] = -2;
			return;
		}
	}

	//Handles jump moves and returns
	else if (move == 3)
	{
		jumpMove(board, yCoord, xCoord, yCoordFin, xCoordFin, turn);
		return;
	}
	//Returns by default
	else
	{
		return;
	}

}

/*This function checks the player's move using if statments containing the rules for checkers*/

int checkMove(int board[][8], int yCoord, int xCoord, int yCoordFin, int xCoordFin, bool turn)
{
	if (turn == true)
	{
		//Check legality of the CPU's move
		if (board[yCoord][xCoord] == 1)
		{
			if ((((board[yCoordFin][xCoordFin]) == -1) || ((board[yCoordFin][xCoordFin]) == -2)) 
				&& (((board[yCoordFin + 1][xCoordFin + 1]) == 0) || ((board[yCoordFin + 1][xCoordFin - 1]) == 0)))
			{
				return(3);
			}
			else
			{
				if (((yCoordFin == yCoord + 1) && (board[yCoordFin][xCoordFin] == 0))
					&& ((xCoordFin == xCoord + 1) || (xCoordFin == xCoord - 1)))
				{
					return (1);
				}
				else
				{
					return (0);
				}
			}
		}
		else if (board[yCoord][xCoord] == 2)
		{
			if ((((board[yCoordFin][xCoordFin]) == -1) || ((board[yCoordFin][xCoordFin]) == -2)) 
				&& (((board[yCoordFin + 1][xCoordFin + 1]) == 0) || ((board[yCoordFin + 1][xCoordFin - 1]) == 0)
					|| (board[yCoordFin + 1][xCoordFin + 1]) == 0) || ((board[yCoordFin - 1][xCoordFin - 1]) == 0))
			{
				return (3);
			}
			else
			{
				if ((board[yCoordFin][xCoordFin] == 0) 
					&& ((yCoordFin == yCoord + 1) || (yCoordFin == yCoord - 1))
					&& ((xCoordFin == xCoord + 1) || (xCoordFin == xCoord - 1)))
				{
					return (2);
				}
				else
				{
					return(0);
				}
			}
		}
		else
		{
			return(0);
		}
	}
	else
	{
		//Check legality of the Player's move
		if (board[yCoord][xCoord] == -1)
		{
			if ((((board[yCoordFin][xCoordFin]) == 1) || ((board[yCoordFin][xCoordFin]) == 2))
				&& (((board[yCoordFin - 1][xCoordFin + 1]) == 0) || ((board[yCoordFin - 1][xCoordFin - 1]) == 0)))
			{
				return(3);
			}
			else
			{
				if (((yCoordFin == yCoord - 1) && (board[yCoordFin][xCoordFin] == 0))
					&& ((xCoordFin == xCoord + 1) || (xCoordFin == xCoord - 1)))
				{
					return (1);
				}
				else
				{
					cout << "\nMove cannot be completed, please try again\n";
					return (0);
				}
			}
		}
		else if (board[yCoord][xCoord] == -2)
		{
			if (((board[yCoordFin][xCoordFin] == 1) || (board[yCoordFin][xCoordFin] == 2))
				&& (((board[yCoordFin + 1][xCoordFin + 1] == 0) || (board[yCoordFin + 1][xCoordFin - 1] == 0))
					|| ((board[yCoordFin + 1][xCoordFin + 1] == 0) || (board[yCoordFin - 1][xCoordFin - 1] == 0))))
			{
				return (3);
			}
			else
			{
				if ((board[yCoordFin][xCoordFin] == 0)
					&& ((yCoordFin == yCoord + 1) || (yCoordFin == yCoord - 1))
					&& ((xCoordFin == xCoord + 1) || (xCoordFin == xCoord - 1)))
				{
					return (2);
				}
				else
				{
					cout << "\nMove cannot be completed, please try again\n";
					return(0);
				}
			}
		}
		else
		{
			cout << "\nMove Error\n";
			return(0);
		}
	}
}

/*This function handles jump moves performed by the player*/

void jumpMove(int board[][8], int yCoord, int xCoord, int yCoordFin, int xCoordFin, bool turn)
{
	if (turn == true)
	{
		//Black's pawn jump moves
		if (board[yCoord][xCoord] == 1)
		{
			if ((yCoordFin == yCoord + 1) && (xCoordFin == xCoord - 1))
			{
				//Black jumps left
				board[yCoord][xCoord] = 0;
				board[yCoordFin][xCoordFin] = 0;
				if ((yCoordFin + 1) == 7)
				{
					board[yCoordFin + 1][xCoordFin - 1] = 2;
				}
				else
				{
					board[yCoordFin + 1][xCoordFin - 1] = 1;
				}
				return;

			}
			else if ((yCoordFin == yCoord + 1) && (xCoordFin == xCoord + 1))
			{
				//Black jumps right
				board[yCoord][xCoord] = 0;
				board[yCoordFin][xCoordFin] = 0;
				if ((yCoordFin + 1) == 7)
				{
					board[yCoordFin + 1][xCoordFin + 1] = 2;
				}
				else
				{
					board[yCoordFin + 1][xCoordFin + 1] = 1;
				}
				return;
			}
		}

		//Black's king jump moves
		else if (board[yCoord][xCoord] == 2)
		{
			if ((yCoord == yCoordFin + 1) && (xCoordFin == xCoordFin - 1))
			{
				//Black jumps forward left
				board[yCoord][xCoord] = 0;
				board[yCoordFin][xCoordFin] = 0;
				board[yCoordFin + 1][xCoordFin - 1] = 2;
				return;

			}
			else if ((yCoordFin == yCoord + 1) && (xCoordFin == xCoord + 1))
			{
				//Black jumps forward right
				board[yCoord][xCoord] = 0;
				board[yCoordFin][xCoordFin] = 0;
				board[yCoordFin + 1][xCoordFin + 1] = 2;
				return;
			}
			else if ((yCoordFin == yCoord - 1) && (xCoordFin == xCoord - 1))
			{
				//Black jumps back left
				board[yCoord][xCoord] = 0;
				board[yCoordFin][xCoordFin] = 0;
				board[yCoordFin - 1][xCoordFin - 1] = 2;
				return;

			}
			else if ((yCoordFin == yCoord - 1) && (xCoordFin == xCoord + 1))
			{
				//Black jumps back right
				board[yCoord][xCoord] = 0;
				board[yCoordFin][xCoordFin] = 0;
				board[yCoordFin - 1][xCoordFin + 1] = 2;
				return;
			}
			else
			{
				return;
			}
		}
	}
	else
	{
		//Red's pawn jump moves
		if (board[yCoord][xCoord] == -1)
		{
			if ((yCoordFin == yCoord - 1) && (xCoordFin == xCoord - 1))
			{
				//Red jumps left
				board[yCoord][xCoord] = 0;
				board[yCoordFin][xCoordFin] = 0;
				if ((yCoordFin - 1) == 0)
				{
					board[yCoordFin - 1][xCoordFin - 1] = -2;
				}
				else
				{
					board[yCoordFin - 1][xCoordFin - 1] = -1;
				}
				return;

			}
			else if ((yCoordFin == yCoord - 1) && (xCoordFin == xCoord + 1))
			{
				//Red jumps right
				board[yCoord][xCoord] = 0;
				board[yCoordFin][xCoordFin] = 0;
				if ((yCoordFin - 1) == 0)
				{
					board[yCoordFin - 1][xCoordFin + 1] = -2;
				}
				else
				{
					board[yCoordFin - 1][xCoordFin + 1] = -1;
				}
				return;
			}
		}
			//Red's king jump moves
		else if (board[yCoord][xCoord] == -2)
		{
			if ((yCoordFin == yCoord + 1) && (xCoordFin == xCoord - 1))
			{
				//Red jumps forward left
				board[yCoord][xCoord] = 0;
				board[yCoordFin][xCoordFin] = 0;
				board[yCoordFin + 1][xCoordFin - 1] = -2;
				return;

			}
			else if ((yCoordFin == yCoord + 1) && (xCoordFin == xCoord + 1))
			{
				//Red jumps forward right
				board[yCoord][xCoord] = 0;
				board[yCoordFin][xCoordFin] = 0;
				board[yCoordFin + 1][xCoordFin + 1] = -2;
				return;
			}
			else if ((yCoordFin == yCoord - 1) && (xCoordFin == xCoord - 1))
			{
				//Red jumps back left
				board[yCoord][xCoord] = 0;
				board[yCoordFin][xCoordFin] = 0;
				board[yCoordFin - 1][xCoordFin - 1] = -2;
				return;

			}
			else if ((yCoordFin == yCoord - 1) && (xCoordFin == xCoord + 1))
			{
				//Red jumps back right
				board[yCoord][xCoord] = 0;
				board[yCoordFin][xCoordFin] = 0;
				board[yCoordFin - 1][xCoordFin + 1] = -2;
				return;
			}
		}
		else
		{
				cout << "Jump Error";
				return;
		}
	}
}

/*These next four functions translate the coordinates entered by the player into array locations
that can then be used in the checkMove() function*/

int playerMoveX ()
{
	int xCoord = 0;
	char xCoordLet = NULL;

	bool askInput = true;

	int move = 0;

	
	cout << "X: ";
	cin >> xCoordLet;

	//Translates xCoordLet to array column number
	switch (xCoordLet)
	{
		case 'a':
		{
			xCoord = 0;
			break;
		}
		case 'b':
		{
			xCoord = 1;
			break;
		}
		case 'c':
		{
			xCoord = 2;
			break;
		}
		case 'd':
		{
			xCoord = 3;
			break;
		}
		case 'e':
		{
			xCoord = 4;
			break;
		}
		case 'f':
		{
			xCoord = 5;
			break;
		}
		case 'g':
		{
			xCoord = 6;
			break;
		}
		case 'h':
		{
			xCoord = 7;
			break;
		}
		//Wrong character error message
		default:
		{
			cout << "Error, only letters A-H are accepted";
			break;
		}
	}

	return xCoord;
}

int playerMoveY ()
{
	int yCoord = 0;

	cout << "Y: ";
	cin >> yCoord;

	//Translates yCoord to array row number
	switch (yCoord)
	{
		case 8:
		{
			yCoord = 0;
			break;
		}
		case 7:
		{
			yCoord = 1;
			break;
		}
		case 6:
		{
			yCoord = 2;
			break;
		}
		case 5:
		{
			yCoord = 3;
			break;
		}
		case 4:
		{
			yCoord = 4;
			break;
		}
		case 3:
		{
			yCoord = 5;
			break;
		}
		case 2:
		{
			yCoord = 6;
			break;
		}
		case 1:
		{
			yCoord = 7;
			break;
		}
	}
	return yCoord;
}

int playerMoveXFin()
{
	int xCoordFin = 0;
	char xCoordLetFin = NULL;

	cout << "X: ";
	cin >> xCoordLetFin;

	//Translates xCoordLetFin to array column number
	switch (xCoordLetFin)
	{
		case 'a':
		{
			xCoordFin = 0;
			break;
		}
		case 'b':
		{
			xCoordFin = 1;
			break;
		}
		case 'c':
		{
			xCoordFin = 2;
			break;
		}
		case 'd':
		{
			xCoordFin = 3;
			break;
		}
		case 'e':
		{
			xCoordFin = 4;
			break;
		}
		case 'f':
		{
			xCoordFin = 5;
			break;
		}
		case 'g':
		{
			xCoordFin = 6;
			break;
		}
		case 'h':
		{
			xCoordFin = 7;
			break;
		}	

		//Wrong character error message
		default:
		{
			cout << "Error, only letters A-H are accepted";
			break;
		}
	}
	return xCoordFin;
}

int playerMoveYFin()
{
	int yCoordFin = 0;

	cout << "Y: ";
	cin >> yCoordFin;

	//Translates yCoordFin to array column number
	switch (yCoordFin)
	{
		case 8:
		{
			yCoordFin = 0;
			break;
		}
		case 7:
		{
			yCoordFin = 1;
			break;
		}
		case 6:
		{
			yCoordFin = 2;
			break;
		}
		case 5:
		{
			yCoordFin = 3;
			break;
		}
		case 4:
		{
			yCoordFin = 4;
			break;
		}
		case 3:
		{
			yCoordFin = 5;
			break;
		}
		case 2:
		{
			yCoordFin = 6;
			break;
		}
		case 1:
		{
			yCoordFin = 7;
			break;
		}
	}
	return yCoordFin;
}

/*This function counts the number of pieces on the board and declares a winner if there is one*/

bool checkGameState(int board[][8])
{
	int redCount = 0;
	int blackCount = 0;

	for (int row = 0; row < 8; row ++)
	{
		for (int col = 0; col < 8; col++)
		{
			if ((board[row][col] == 1) || (board[row][col] == 2))
			{
				blackCount++;
			}
			else if ((board[row][col] == -1) || (board[row][col] == -2))
			{
				redCount++;
			}
		}
	}

	if ((redCount != 0) && (blackCount != 0))
	{
		return false;
	}
	else if (redCount == 0)
	{
		cout << "\n\nBlack Wins";
		cin.ignore();
		return true;
	}
	else if (blackCount == 0)
	{
		cout << "\n\nRed Wins";
		cin.ignore();
		return true;
	}
}

/*This function translates the cpu's move into the board's coordinate system*/

void cpuTranslation(int cpuX, int cpuY, int cpuXFin, int cpuYFin)
{
	cout << "Computer's Move:\n";
	switch (cpuX)
	{
		case 0:
		{
			cout << "A";
			break;
		}
		case 1:
		{
			cout << "B";
			break;
		}
		case 2:
		{
			cout << "C";
			break;
		}
		case 3:
		{
			cout << "D";
			break;
		}
		case 4:
		{
			cout << "E";
			break;
		}
		case 5:
		{
			cout << "F";
			break;
		}
		case 6:
		{
			cout << "G";
			break;
		}
		case 7:
		{
			cout << "H";
			break;
		}
	}

	cout << ",";

	switch (cpuY)
	{
		case 0:
		{
			cout << "8";
			break;
		}
		case 1:
		{
			cout << "7";
			break;
		}
		case 2:
		{
			cout << "6";
			break;
		}
		case 3:
		{
			cout << "5";
			break;
		}
		case 4:
		{
			cout << "4";
			break;
		}
		case 5:
		{
			cout << "3";
			break;
		}
		case 6:
		{
			cout << "2";
			break;
		}
		case 7:
		{
			cout << "1";
			break;
		}
	}

	cout << " to ";

	switch (cpuXFin)
	{
		case 0:
		{
			cout << "A";
			break;
		}
		case 1:
		{
			cout << "B";
			break;
		}
		case 2:
		{
			cout << "C";
			break;
		}
		case 3:
		{
			cout << "D";
			break;
		}
		case 4:
		{
			cout << "E";
			break;
		}
		case 5:
		{
			cout << "F";
			break;
		}
		case 6:
		{
			cout << "G";
			break;
		}
		case 7:
		{
			cout << "H";
			break;
		}
	}

	cout << ",";

	switch (cpuYFin)
	{
		case 0:
		{
			cout << "8\n\n";
			break;
		}
		case 1:
		{
			cout << "7\n\n";
			break;
		}
		case 2:
		{
			cout << "6\n\n";
			break;
		}
		case 3:
		{
			cout << "5\n\n";
			break;
		}
		case 4:
		{
			cout << "4\n\n";
			break;
		}
		case 5:
		{
			cout << "3\n\n";
			break;
		}
		case 6:
		{
			cout << "2\n\n";
			break;
		}
		case 7:
		{
			cout << "1\n\n";
			break;
		}
	}

	return;
}

#endif
