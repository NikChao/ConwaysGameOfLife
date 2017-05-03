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
	bool UpdateCell(int i);
	void Update();
	bool* GetGrid();
	void DrawGrid(bool* grid);
	void GameLoop();

private:
	bool* grid;
	int width;
	int height;
};

#pragma region Game Methods
Game::Game()
{
	width = 20;
	height = 20;
	grid = (bool *)malloc(height * width * sizeof(bool));

	for (int i = 0; i < height * width; i++)
		grid[i] = false;

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
		grid[array[1] * width + array[0]] = true;
	}
}

Game::~Game()
{
	grid = nullptr;
	free(grid);
}

bool Game::UpdateCell(int i)
{
	int surroundingAlive = 0;

	// Top left
	if (i % width > 0 && i > width && grid[i - width - 1]) surroundingAlive++;
	// Top mid
	if (i > width && grid[i - width]) surroundingAlive++;
	// Top right
	if (i > width && i % width < width - 1 && grid[i - width + 1]) surroundingAlive++;
	// left
	if (i % width > 0 && grid[i - 1]) surroundingAlive++;
	// right
	if (i % width < width - 1 && grid[i + 1]) surroundingAlive++;
	// bot left
	if (i % width > 0 && i <= width * (height - 1) && grid[i + width - 1]) surroundingAlive++;
	// bot mid
	if (i <= width * (height - 1) && grid[i + width]) surroundingAlive++;
	// bot right
	if (i % width < width - 1 && i <= width * (height - 1) && grid[i + width + 1]) surroundingAlive++;

	if (surroundingAlive == 3) return true;
	if (grid[i] && surroundingAlive == 2) return true;
	if (surroundingAlive > 3 || surroundingAlive < 2) return false;
}

void Game::Update()
{
	bool* newBoard = (bool *)malloc(height * width * sizeof(bool));
	for (int i = 0; i < height * width; i++)
	{
		newBoard[i] = UpdateCell(i);
	}
	grid = newBoard;
	
	newBoard = nullptr;
	free(newBoard);
}

void Game::DrawGrid(bool* grid)
{
	system("cls");
	for (int i = 0; i < height; i++)
	{
		string row = "";
		for (int j = i * height; j < i * height + width; j++)
		{
			if (grid[j])
				row += "1 ";
			else
				row += "0 ";
		}
		row += "\n";
		cout << row;
	}
}

bool* Game::GetGrid()
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
