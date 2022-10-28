#pragma once
#include <vector>

namespace GameManager 
{
	enum class Difficulty { easy, medium, hard }; // Difficulty, mine-wise or size-wise

	std::vector<std::vector<bool>> NewGame(Difficulty mines, Difficulty size);
}