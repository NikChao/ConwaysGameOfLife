// ConwaysGameOfLife.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <thread>
#include <vector>
#include <sstream>

class Game {
public:
	Game();
	~Game();
	bool Cell(int x, int y);
	bool UpdateCell(int x, int y);
	void Update();
	void DrawGrid(bool *grid);
	void GameLoop();

private:
	bool *grid;
	int width;
	int height;
};
#pragma region Game Methods
// Move Logic to initialisation method
Game::Game() {
	width = 20;
	height = 20;
	grid = (bool *)malloc(height * width * sizeof(bool));
	for (int i = 0; i < height * width; i++) grid[i] = false;
}

Game::~Game() {
	grid = nullptr;
	free(grid);
}

bool Game::Cell(int x, int y) {
	return x >= 0 && x < width && y >= 0 && y < height && grid[y * width + x];
}

bool Game::UpdateCell(int x, int y) {
	int surroundingAlive =
		Cell(x - 1, y - 1) + Cell(x, y - 1) + Cell(x + 1, y - 1) + Cell(x - 1, y)
		+ Cell(x + 1, y) + Cell(x - 1, y + 1)+ Cell(x, y + 1) + Cell(x + 1, y + 1);
	
	return surroundingAlive == 3 || (Cell(x, y) && surroundingAlive == 2);
}

void Game::Update() {
	bool *newBoard = (bool *)malloc(height * width * sizeof(bool));
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++)
		{
			newBoard[y * width + x] = UpdateCell(x, y);
		}
	}
	grid = newBoard;
	
	newBoard = nullptr;
	free(newBoard);
}


void Game::DrawGrid(bool *grid) {
	system("cls");
	for (int i = 0; i < height; i++) {
		for (int j = i * height; j < i * height + width; j++) {
			if (grid[j])
				std::cout << "1 ";
			else
				std::cout << "0 ";
		}
		std::cout <<  "\n";
	}
}

void Game::GameLoop() {

	std::cout << "Input your initial living cells in the format `x1,y1 x2,y2 x3,ye ...`\n";
	std::string input = "";
	std::getline(std::cin, input);

	std::string buffer;
	std::stringstream ss(input);
	std::vector<std::string> tokens;

	while (ss >> buffer) {
		tokens.push_back(buffer);
	}
	for (int i = 0; i < tokens.size(); i++) {
		std::string str = tokens[i];
		for (int j = 0; j < str.length(); j++) {
			if (str[j] == ',')
			{
				str[j] = ' ';
			}
		}
		std::vector<int> array;
		std::stringstream s(str);
		int temp;
		while (s >> temp)
			array.push_back(temp);
		grid[array[1] * width + array[0]] = true;
	}

	DrawGrid(grid);
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	while (true) {
		Update();
		DrawGrid(grid);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
}
#pragma endregion

int main() {
	Game g;
	g.GameLoop(); // Runs Game

    return 0;
}
