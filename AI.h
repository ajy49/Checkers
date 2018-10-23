#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include <iostream>
#include <vector>


using std::cout;
using std::cin;
using std::vector;

/*This function examines the position of each piece on the board and adds it's point value to the variable "score",  
The total score is then returned.*/

int evaluateBoard(int board[][8], bool turn)
{
	int score = 0;

	if (turn = true)
	{
		score = score + 5;

		for (int row = 0; row < 8; row++)
		{
			for (int col = 0; col < 8; col++)
			{
				//Black count
				if (board[row][col] == 1)
				{
					score = score + 2;
				}
				//Red count
				else if (board[row][col] == -1)
				{
					score = score - 2;
				}
				//Black king count
				else if (board[row][col] == 2)
				{
					score = score + 4;
				}
				//Red king count
				else if (board[row][col] == -2)
				{
					score = score - 4;
				}
				//Defended black 
				else if ((board[row][col] == 1) 
					&& ((board[row - 1][col - 1] == 1) || (board[row - 1][col + 1]) == 1))
				{
					score = score + 3;
				}
				//Undefended red
				else if ((board[row][col] == -1)
					&& ((board[row + 1][col - 1] == 0) || (board[row + 1][col + 1]) == 0))
				{
					score = score + 1;
				}
			}
		}
	}
	return score;
}

/*This function takes a copy of the current board and generates each possible move availible to the AI player using minimax*/

int generateMove(int currentboard[][8],bool turn, int depth, vector<node>&treescore)
{
	int board[8][8];

	char moveType = NULL;

	int score = 0;

	//Copy over the current board state to a disposible board
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			board[row][col] = currentboard[row][col];
		}
	}

	depth++;

	while (depth <= 2)
	{
		//max move
		if (turn == true)
		{
			maxRules(board, depth, turn, currentboard, treescore);
		}
		//min move
		else if (turn == false)
		{
			score = minRules(board, depth, turn, currentboard);
		}
		break;
	}
	return score;
}

/*This function creates a node, that is stored in a vector, containing all possible moves and their final point values calculated using minimax*/

void createNode (int board[][8], int boardEvaluation, int row, int col, char moveType, int depth, bool turn, vector<node>&treescore)
{
	struct node node;

	//Generate node point value
	if (depth == 2)
	{
		node.nodeScore = boardEvaluation;
	}
	else
	{
		turn = false;
		node.nodeScore = generateMove(board, turn, depth, treescore);
	}
	
	//Store move coordinates
	node.XCoord = col;
	node.yCoord = row;

	if (moveType == 'r')
	{
		node.XCoordFin = col + 1;
		node.yCoordFin = row + 1;
	}
	else if (moveType == 'l')
	{
		node.XCoordFin = col - 1;
		node.yCoordFin = row + 1;
	}
	else if (moveType == '+')
	{
		node.XCoordFin = col + 1;
		node.yCoordFin = row - 1;
	}
	else if (moveType == '-')
	{
		node.XCoordFin = col - 1;
		node.yCoordFin = row - 1;
	}

	cout << node.nodeScore;

	treescore.push_back(node);

	return;
}

/*This function contains the game rules needed to generate a legal move for Max*/

void maxRules(int board[][8], int depth, bool turn, int originalBoard[][8], vector<node>&treescore)
{
	char moveType = NULL;

	int boardEvaluation = 0;
	int score = 0;

	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			//black pawn rule set
			if (board[row][col] == 1)
			{
				//jump diagonal right
				if ((((board[row + 1][col + 1]) == -1) || ((board[row + 1][col + 1]) == -2))
					&& ((board[row + 2][col + 2]) == 0))
				{
					board[row][col] = 0;
					board[row + 1][col + 1] = 0;
					board[row + 2][col + 2] = 1;
					boardEvaluation = evaluateBoard(board, turn);

					if (depth == 1)
					{
						moveType = 'r';
						createNode(board, boardEvaluation, row, col, moveType, depth, turn, treescore);
					}
				}
				//jump diagonal left
				else if ((((board[row + 1][col - 1]) == -1) || ((board[row + 1][col - 1]) == -2))
					&& ((board[row + 2][col - 2]) == 0))
				{
					board[row][col] = 0;
					board[row + 1][col - 1] = 0;
					board[row + 2][col - 2] = 1;
					boardEvaluation = evaluateBoard(board, turn);

					if (depth == 1)
					{
						moveType = 'l';
						createNode(board, boardEvaluation, row, col, moveType, depth, turn, treescore);
					}
				}
				else
				{
					//piece moves diagonal right
					if (board[row + 1][col + 1] == 0)
					{
						board[row][col] = 0;
						board[row + 1][col + 1] = 1;
						boardEvaluation = evaluateBoard(board, turn);

						if (depth == 1)
						{
							moveType = 'r';
							createNode(board, boardEvaluation, row, col, moveType, depth, turn, treescore);
						}
					}
					//cant move
					else
					{}
					//piece moves diagonal left
					if (board[row + 1][col - 1] == 0)
					{
						board[row][col] = 0;
						board[row + 1][col - 1] = 1;
						boardEvaluation = evaluateBoard(board, turn);

						if (depth == 1)
						{
							moveType = 'l';
							createNode(board, boardEvaluation, row, col, moveType, depth, turn ,treescore);
						}
					}
					//cant move
					else
					{}
				}

				//reset board back to original state
				for (int row = 0; row < 8; row++)
				{
					for (int col = 0; col < 8; col++)
					{
						board[row][col] = originalBoard[row][col];
					}
				}
			}
			//black king rule set
			else if (board[row][col] == 2)
			{
				//jump forward right
				if ((((board[row + 1][col + 1]) == -1) || ((board[row + 1][col + 1]) == -2))
					&& ((board[row + 2][col + 2]) == 0))
				{
					board[row][col] = 0;
					board[row + 1][col + 1] = 0;
					board[row + 2][col + 2] = 2;
					turn = false;

					if (depth == 1)
					{
						moveType = 'r';
						createNode(board, boardEvaluation, row, col, moveType, depth, turn, treescore);
					}
				}
				//jump forward left
				else if ((((board[row + 1][col - 1]) == -1) || ((board[row + 1][col - 1]) == -2))
					&& ((board[row + 2][col - 2]) == 0))
				{
					board[row][col] = 0;
					board[row + 1][col - 1] = 0;
					board[row + 2][col - 2] = 2;
					turn = false;

					if (depth == 1)
					{
						moveType = 'l';
						createNode(board, boardEvaluation, row, col, moveType, depth, turn, treescore);
					}
				}
				//jump back right
				if ((((board[row - 1][col + 1]) == -1) || ((board[row - 1][col + 1]) == -2))
					&& ((board[row - 2][col + 2]) == 0))
				{
					board[row][col] = 0;
					board[row - 1][col + 1] = 0;
					board[row - 2][col + 2] = 2;
					turn = false;

					if (depth == 1)
					{
						moveType = '+';
						createNode(board, boardEvaluation, row, col, moveType, depth, turn, treescore);
					}
				}
				//jump back left
				else if ((((board[row - 1][col - 1]) == -1) || ((board[row - 1][col - 1]) == -2))
					&& ((board[row - 2][col - 2]) == 0))
				{
					board[row][col] = 0;
					board[row - 1][col - 1] = 0;
					board[row - 2][col - 2] = 2;
					turn = false;

					if (depth == 1)
					{
						moveType = '-';
						createNode(board, boardEvaluation, row, col, moveType, depth, turn, treescore);
					}
				}
				//no jumps availible
				else
				{
					//piece moves diagonal right
					if (board[row + 1][col + 1] == 0)
					{
						board[row][col] = 0;
						board[row + 1][col + 1] = 2;
						turn = false;

						if (depth == 1)
						{
							moveType = '+';
							createNode(board, boardEvaluation, row, col, moveType, depth, turn, treescore);
						}
					}
					//cant move
					else
					{}
					//piece moves diagonal left
					if (board[row + 1][col - 1] == 0)
					{
						board[row][col] = 0;
						board[row + 1][col - 1] = 2;
						turn = false;

						if (depth == 1)
						{
							moveType = 'l';
							createNode(board, boardEvaluation, row, col, moveType, depth, turn, treescore);
						}
					}
					//cant move
					else
					{}
					//piece moves up diagonal right
					if (board[row - 1][col + 1] == 0)
					{
						board[row][col] = 0;
						board[row - 1][col + 1] = 2;
						turn = false;

						if (depth == 1)
						{
							moveType = '+';
							createNode(board, boardEvaluation, row, col, moveType, depth, turn, treescore);
						}
					}
					//cant move
					else
					{}
					//piece moves up diagonal left
					if (board[row - 1][col - 1] == 0)
					{
						board[row][col] = 0;
						board[row + 1][col - 1] = 2;
						turn = false;

						if (depth == 1)
						{
							moveType = '-';
							createNode(board, boardEvaluation, row, col, moveType, depth, turn, treescore);
						}
					}
					//cant move
					else
					{}

					//reset board back to original state
					for (int row = 0; row < 8; row++)
					{
						for (int col = 0; col < 8; col++)
						{
							board[row][col] = originalBoard[row][col];
						}
					}
				}
			}
			//skip space
			else
			{}
		}
	}
}

/*This function contains the game rules needed to generate a legal move for Min*/

int minRules(int board[][8], int depth, bool turn, int originalBoard[][8])
{
	char moveType = NULL;

	int boardEvaluation = 0;

	vector<int>score;

	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (board[row][col] == -1)
			{
				//jumping
				if ((((board[row - 1][col + 1]) == 1) || ((board[row - 1][col + 1]) == 2))
					&& ((board[row - 2][col + 2]) == 0))
				{
					//jump right
					board[row][col] = 0;
					board[row - 1][col + 1] = 0;
					board[row - 2][col + 2] = -1;
					boardEvaluation = evaluateBoard(board, turn);
				}
				else if ((((board[row - 1][col - 1]) == 1) || ((board[row - 1][col - 1]) == 2))
					&& ((board[row - 2][col - 2]) == 0))
				{
					//jump left
					board[row][col] = 0;
					board[row - 1][col - 1] = 0;
					board[row - 2][col - 2] = -1;
					boardEvaluation = evaluateBoard(board, turn);
				}
				else
				{
					if (board[row - 1][col + 1] == 0)
					{
						//piece moves diagonal right
						board[row][col] = 0;
						board[row - 1][col + 1] = -1;
						evaluateBoard(board, turn);
						boardEvaluation = evaluateBoard(board, turn);
						score.push_back(boardEvaluation);
					}
					else
					{}

					if (board[row - 1][col - 1] == 0)
					{
						//piece moves diagonal right
						board[row][col] = 0;
						board[row - 1][col - 1] = -1;
						evaluateBoard(board, turn);
						boardEvaluation = evaluateBoard(board, turn);
						score.push_back(boardEvaluation);
					}
					else
					{}
				}

				//reset board back to it's original state
				for (int row = 0; row < 8; row++)
				{
					for (int col = 0; col < 8; col++)
					{
						board[row][col] = originalBoard[row][col];
					}
				}
			}

			//king move
			else if (board[row][col] == -2)
			{
				//jump forward right
				if ((((board[row + 1][col + 1]) == 1) || ((board[row + 1][col + 1]) == 2))
					&& ((board[row + 2][col + 2]) == 0))
				{
					board[row][col] = 0;
					board[row + 1][col + 1] = 0;
					board[row + 2][col + 2] = -2;
					boardEvaluation = evaluateBoard(board, turn);
				}
				//jump forward left
				else if ((((board[row + 1][col - 1]) == 1) || ((board[row + 1][col - 1]) == 2))
					&& ((board[row + 2][col - 2]) == 0))
				{
					board[row][col] = 0;
					board[row + 1][col - 1] = 0;
					board[row + 2][col - 2] = -2;
					boardEvaluation = evaluateBoard(board, turn);
				}
				//jump back right
				if ((((board[row - 1][col + 1]) == 1) || ((board[row - 1][col + 1]) == 2))
					&& ((board[row - 2][col + 2]) == 0))
				{
					board[row][col] = 0;
					board[row - 1][col + 1] = 0;
					board[row - 2][col + 2] = 2;
					boardEvaluation = evaluateBoard(board, turn);
				}
				//jump back left
				else if ((((board[row - 1][col - 1]) == 1) || ((board[row - 1][col - 1]) == 2))
					&& ((board[row - 2][col - 2]) == 0))
				{
					board[row][col] = 0;
					board[row - 1][col - 1] = 0;
					board[row - 2][col - 2] = 2;
					boardEvaluation = evaluateBoard(board, turn);
				}
				//no jumps availible, normal move
				else
				{
					//piece moves diagonal right
					if (board[row + 1][col + 1] == 0)
					{
						board[row][col] = 0;
						board[row + 1][col + 1] = -1;
						boardEvaluation = evaluateBoard(board, turn);
					}
					//cant move
					else
					{}
					//piece moves diagonal left
					if (board[row + 1][col - 1] == 0)
					{
						board[row][col] = 0;
						board[row + 1][col - 1] = -2;
						boardEvaluation = evaluateBoard(board, turn);
					}
					//cant move
					else
					{}
					//piece moves up diagonal right
					if (board[row - 1][col + 1] == 0)
					{
						board[row][col] = 0;
						board[row - 1][col + 1] = -2;
						boardEvaluation = evaluateBoard(board, turn);
					}
					//cant move
					else
					{}
					//piece moves up diagonal left
					if (board[row - 1][col - 1] == 0)
					{
						board[row][col] = 0;
						board[row + 1][col - 1] = -2;
						boardEvaluation = evaluateBoard(board, turn);
					}
					//cant move
					else
					{}

					//reset board
					for (int row = 0; row < 8; row++)
					{
						for (int col = 0; col < 8; col++)
						{
							board[row][col] = originalBoard[row][col];
						}
					}
				}
			}
			else
			{}
		}
	}

	//change turn
	turn = true;

	//determine best score for min
	boardEvaluation = min(score);

	return boardEvaluation;
}

/*The min() and max() functions return a final score for min and max by comparing all the scores in the ply*/

int min(vector<int>score)
{
	int finalscore = score[0];

	for (int in = 1; in < score.size() ; in++)
	{
		if (score[in] < finalscore)
		{
			finalscore = score[in];
		}
	}
	return finalscore;
}

int max(vector<int>score)
{
	int finalscore = score[0];

	for (int in = 1; in < score.size(); in++)
	{
		if (score[in] > finalscore)
		{
			finalscore = score[in];
		}
	}
	return finalscore;
}

#endif
