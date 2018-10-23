/*Andrew Yahnke
  Checkers Program
  CS495
*/

#include <iostream>
#include <string>
#include "Board.h"
#include "AI.h"
#include "ClearScreen.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main()
{
	int currentBoard[8][8] = { 4,1,4,1,4,1,4,1,
							  1,4,1,4,1,4,1,4,
							  4,1,4,1,4,1,4,1,
							  0,4,0,4,0,4,0,4,
							  4,0,4,0,4,0,4,0,
							 -1,4,-1,4,-1,4,-1,4,
							 4,-1,4,-1,4,-1,4,-1,
							 -1,4,-1,4,-1,4,-1,4 };

	bool turn = true;

	int bestScoreNum = 0;

	int depth = 0;
	
	bool gameOver = false;

	int cpuY = 0;
	int cpuX = 0;

	int cpuYFin = 0;
	int cpuXFin = 0;

	vector<node>treescore;

	
	while (gameOver == false)
	{
		displayUpdate(currentBoard, turn);

		if (turn == true)
		{
			//cpu's turn

			generateMove(currentBoard, turn, depth, treescore);

			int bestScore = treescore[0].nodeScore;

			for (int in = 1; in < treescore.size(); in++)
			{
				if (treescore[in].nodeScore > bestScore)
				{
					bestScore = treescore[in].nodeScore;
					bestScoreNum = in;
				}
			}


			for (int in = 0; in < treescore.size(); in++)
			{
				cout << "\n" << treescore[in].nodeScore;
			}

			cpuY = treescore[bestScoreNum].yCoord;
			cpuX = treescore[bestScoreNum].XCoord;
			cpuYFin = treescore[bestScoreNum].yCoordFin;
			cpuXFin = treescore[bestScoreNum].XCoordFin;

			treescore.clear();
			movePiece(currentBoard, turn, cpuX, cpuY, cpuXFin, cpuYFin);

			turn = false;
		}
		else
		{	
			//player's turn

			cpuTranslation(cpuX, cpuY, cpuXFin, cpuYFin);

			//reset the variables used
			bestScoreNum = 0;
			depth = 0;
			cpuY = 0;
			cpuX = 0;
			cpuYFin = 0;
			cpuXFin = 0;
			
			movePiece(currentBoard, turn, cpuX, cpuY, cpuXFin, cpuYFin);
			turn = true;
		
		}

		gameOver = checkGameState(currentBoard);

	}

	cin.ignore();
	
	return (0);
}
