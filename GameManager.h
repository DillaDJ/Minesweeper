#pragma once
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>
#include <map>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG



namespace GameManager 
{
	enum class Difficulty { easy, medium, hard }; // Difficulty, mine-wise or size-wise
	enum class TileState { mine, flagged_mine, flagged_tile, unexplored, no_adjacent_mines, one_adjacent_mine, two_adjacent_mines, three_adjacent_mines, four_adjacent_mines, five_adjacent_mines, six_adjacent_mines, seven_adjacent_mines, eight_adjacent_mines };

	// Forward declares
	void PrintMinefield(std::vector<TileState> mines);
	
	void NewGame(Difficulty mine_amount, Difficulty size);
	
	int GetDimensions();
	
	bool IsGenerated();
	bool IsGameOver();
	bool IsVictory();

	TileState GetTileState(int id);

	std::vector<int> GetNeighbouringTiles(int id);
	
	int GetNeighbouringMines(int id);
	int GetNeighbouringMines(std::vector<int> neighbours);

	void FlagTile(int id);

	void ProcessTile(int id);

	void ProcessNeighbouringTiles(int id);

	void FloodFill(int id);
}