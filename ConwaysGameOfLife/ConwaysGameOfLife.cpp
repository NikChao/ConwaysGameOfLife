// ConwaysGameOfLife.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <sstream>

using namespace std;
// TODO replace jagged array with flattened array and use logic for checks :)
class Game
{
public:
	Game();
	~Game();
	bool UpdateCell(int x, int y);
	void Update();
	bool** GetGrid();
	void DrawGrid(bool** grid);
	void GameLoop();

private:
	bool** grid;
	int width;
	int height;
};

#pragma region Game Methods
Game::Game()
{
	width = 20;
	height = 20;
	grid = (bool **)malloc(height * sizeof(bool *));
	for (int i = 0; i < height; i++)
	{
		grid[i] = (bool *)malloc(width * sizeof(bool));
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
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

Game::~Game()
{
	free(grid);
}

bool Game::UpdateCell(int x, int y)
{
	int maxx = width - 1;
	int maxy = height - 1;
	int surroundingAlive = 0;

	if (x > 0 && y > 0) {
		if (grid[y - 1][x - 1])
			surroundingAlive++;
		if (grid[y][x - 1])
			surroundingAlive++;
	}
	if (x > 0 && y < maxy) {
		if (grid[y + 1][x - 1])
			surroundingAlive++;
		if (grid[y + 1][x])
			surroundingAlive++;
	}
	if (x < maxx && y > 0) {
		if (grid[y - 1][x + 1])
			surroundingAlive++;
		if (grid[y - 1][x])
			surroundingAlive++;
		if (grid[y][x + 1])
			surroundingAlive++;
	}
	if (x < maxx && y < maxy) {
		if (grid[y + 1][x + 1])
			surroundingAlive++;
	}

	/* Returns */
	if (grid[y][x] && (surroundingAlive == 2 || surroundingAlive == 3))
	{
		return true;
	}
	if (surroundingAlive > 3 || surroundingAlive < 2)
	{
		return false;
	}
	if (!grid[y][x] && surroundingAlive == 3)
	{
		return true;
	}
	return false;
	/* End */

}

void Game::Update()
{
	bool** newBoard = (bool **)malloc(height * sizeof(bool *));
	for (int i = 0; i < height; i++)
	{
		newBoard[i] = (bool *)malloc(width * sizeof(bool));
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			newBoard[j][i] = UpdateCell(i, j);
		}
	}
	grid = newBoard;
}

void Game::DrawGrid(bool** grid)
{
	system("cls");
	for (int i = 0; i < height; i++)
	{
		bool* row = grid[i];
		string rowDisplay = "";
		for (int j = 0; j < width; j++)
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
	g.GameLoop(); // Runs Game

    return 0;
}
