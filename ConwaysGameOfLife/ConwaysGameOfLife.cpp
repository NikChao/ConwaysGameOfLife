// ConwaysGameOfLife.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <sstream>

using namespace std;

class Game
{
public:
	Game();
	bool UpdateCell(int x, int y);
	void Update();
	bool** GetGrid();
	void DrawGrid(bool** grid);
	void GameLoop();

private:
	bool** grid;
	int x;
	int y;
};

#pragma region Game Methods
Game::Game()
{
	x = 20;
	y = 20;
	grid = (bool **)malloc(y * sizeof(bool *));
	for (int i = 0; i < y; i++)
	{
		grid[i] = (bool *)malloc(x * sizeof(bool));
	}
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			grid[i][j] = false;
		}
	}

	fprintf(stdout, "Input your initial living cells in the format `x1,y1 x2,y2 x3,ye ...`\n");
	string input = "";
	getline(cin, input);

	string buffer;
	stringstream ss(input);
	vector<string> tokens;

	while (ss >> buffer)
	{
		tokens.push_back(buffer);
	}
	for (int i = 0; i < tokens.size(); i++)
	{
		string str = tokens[i];
		for (int j = 0; j < str.length(); j++)
		{
			if (str[j] == ',')
			{
				str[j] = ' ';
			}
		}
		vector<int> array;
		stringstream s(str);
		int temp;
		while (s >> temp)
			array.push_back(temp);
		grid[array[1]][array[0]] = true;
	}
}

bool Game::UpdateCell(int xpos, int ypos)
{
	int maxx = x - 1;
	int maxy = y - 1;
	int surroundingAlive = 0;

	if (xpos > 0 && ypos > 0) {
		if (grid[ypos - 1][xpos - 1])
			surroundingAlive++;
		if (grid[ypos][xpos - 1])
			surroundingAlive++;
	}
	if (xpos > 0 && ypos < maxy) {
		if (grid[ypos + 1][xpos - 1])
			surroundingAlive++;
		if (grid[ypos + 1][xpos])
			surroundingAlive++;
	}
	if (xpos < maxx && ypos > 0) {
		if (grid[ypos - 1][xpos + 1])
			surroundingAlive++;
		if (grid[ypos - 1][xpos])
			surroundingAlive++;
		if (grid[ypos][xpos + 1])
			surroundingAlive++;
	}
	if (xpos < maxx && ypos < maxy) {
		if (grid[ypos + 1][xpos + 1])
			surroundingAlive++;
	}

	/* Returns */
	if (grid[ypos][xpos] && (surroundingAlive == 2 || surroundingAlive == 3))
	{
		return true;
	}
	if (surroundingAlive > 3 || surroundingAlive < 2)
	{
		return false;
	}
	if (!grid[ypos][xpos] && surroundingAlive == 3)
	{
		return true;
	}
	return false;
	/* End */

}

void Game::Update()
{
	bool** newBoard = (bool **)malloc(y * sizeof(bool *));
	for (int i = 0; i < y; i++)
	{
		newBoard[i] = (bool *)malloc(x * sizeof(bool));
	}
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < x; j++)
		{
			newBoard[j][i] = UpdateCell(i, j);
		}
	}
	grid = newBoard;
}

void Game::DrawGrid(bool** grid)
{
	system("cls");
	for (int i = 0; i < y; i++)
	{
		bool* row = grid[i];
		string rowDisplay = "";
		for (int j = 0; j < x; j++)
		{
			if (grid[i][j])
			{
				rowDisplay += "1 ";
			}
			else
			{
				rowDisplay += "0 ";
			}
		}
		cout << rowDisplay << '\n';
	}
}

bool** Game::GetGrid()
{ 
	return grid;
}

void Game::GameLoop()
{
	DrawGrid(grid);
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	while (true)
	{
		Update();
		DrawGrid(grid);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
}
#pragma endregion

int main()
{
	Game g = Game();
	getchar();
	g.GameLoop(); // Runs Game


    return 0;
}

