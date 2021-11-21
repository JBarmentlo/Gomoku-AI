#include "defines.hpp"
#include "board.hpp"

#include <iostream>
#include <string>


bool	set_piece(int row, int col, int player, t_state &state)
{
	/*
	Sets a piece at the given position.
	Returns true if legal, False if illegal (square already occupied)
	*/
	if (player == WHITE)
	{
		if (state.board.white[row * BOARD_WIDTH + col])
			return false;
		else
		{
			state.board.white.set(row * BOARD_WIDTH + col, true);
			return true;
		}
	}
	else
	{
		if (state.board.black[row * BOARD_WIDTH + col])
			return false;
		else
		{
			state.board.black.set(row * BOARD_WIDTH + col, true);
			return true;
		}		
	}
}

int		get_square(int row, int col, t_fullboard &board)
{
	if (board.black[row * BOARD_WIDTH + col])
	{
		return  (BLACK);
	}
	if (board.white[row * BOARD_WIDTH + col])
	{
		return  (WHITE);
	}
	return  (EMPTY);
}

void	print_state(t_state &state)
{
	std::string symbols[3] = {"O", "X", " "};
	for (int r = 0; r < BOARD_HEIGHT; r++)
	{
		for (int c = 0; c < BOARD_WIDTH; c++)
		{
			std::cout << "+   ";
		}
		std::cout << std::endl;
		for (int c = 0; c < BOARD_WIDTH; c++)
		{
			std::cout << "  " << symbols[get_square(r, c, state.board)] << " ";
		}
		std::cout << std::endl;
	}
}