#pragma once

namespace GameManager 
{
	enum class Difficulty { easy, medium, hard }; // Difficulty, mine-wise or size-wise

	void NewGame(Difficulty mines, Difficulty size);
}