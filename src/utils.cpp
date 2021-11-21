#include "defines.hpp"
#include <iostream>

void shift_pattern(pattern &pat, int row, int col)
{
	pat.b_bits = pat.b_bits << (row * BOARD_WIDTH + col);
	pat.w_bits = pat.w_bits << (row * BOARD_WIDTH + col);
}

void print_pattern(pattern &pat)
{
	std::string symbols[3] = {"O", "X", " "};
	for (int r = 0; r <= BOARD_HEIGHT; r++)
	{
		for (int c = 0; c <= BOARD_WIDTH; c++)
		{
			std::cout << "+   ";
		}
		std::cout << std::endl;
		for (int c = 0; c < BOARD_WIDTH; c++)
		{
			if (pat.b_bits[r * BOARD_WIDTH + c])
				std::cout << "  " << symbols[BLACK] << " ";
			else if (pat.w_bits[r * BOARD_WIDTH + c])
				std::cout << "  " << symbols[WHITE] << " ";
			else
				std::cout << "  " << symbols[EMPTY] << " ";
		}
		std::cout << std::endl;
	}
}
