#include "defines.hpp"
#include "state.hpp"
#include "utils.hpp"


#include <string>
#include <iostream>


State::State(/* args */)
{
	this->player = WHITE;
	this->w_captures = 0;
	this->b_captures = 0;
}

State::~State()
{
}


void		State::set_piece(int row, int col)
{
	/*
	Sets a piece at the given position.
	*/
	if (this->player == WHITE)
	{
		if (not this->w_board[row * BOARD_WIDTH + col])
		{
			this->w_board.set(row * BOARD_WIDTH + col, true);
			this->player = BLACK;
		}
	}
	else
	{
		if (not this->b_board[row * BOARD_WIDTH + col])
		{
			this->b_board.set(row * BOARD_WIDTH + col, true);
			this->player = WHITE;
		}		
	}
}


int			State::get_square(int row, int col)
{
	if (this->b_board[row * BOARD_WIDTH + col])
	{
		return  (BLACK);
	}
	if (this->w_board[row * BOARD_WIDTH + col])
	{
		return  (WHITE);
	}
	return  (EMPTY);
}

void		State::print(void)
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
			std::cout << "  " << symbols[this->get_square(r, c)] << " ";
		}
		std::cout << std::endl;
	}
}

int			State::find_pattern(pattern pat)
{
	int last_r = 0;
	int last_c = 0;
	for (int r = 0; r <= BOARD_HEIGHT - pat.height; r++)
	{
		for (int c = 0; c <= BOARD_WIDTH - pat.width; c++)
		{
			shift_pattern(pat, r -  last_r, c - last_c);
			last_r = r;
			last_c = c;
			if (((pat.b_bits & this->b_board) == pat.b_bits) and ((pat.w_bits & this->w_board) == pat.w_bits))
			{
				return (r * BOARD_WIDTH + c);
			}
		}
	}
	return (PATTERN_MISSING);
}

int			State::count_pattern(pattern pat)
{
	int last_r = 0;
	int last_c = 0;
	int out    = 0;

	for (int r = 0; r <= BOARD_HEIGHT - pat.height; r++)
	{
		for (int c = 0; c <= BOARD_WIDTH - pat.width; c++)
		{
			shift_pattern(pat, r -  last_r, c - last_c);
			last_r = r;
			last_c = c;
			if (((pat.b_bits & this->b_board) == pat.b_bits) and ((pat.w_bits & this->w_board) == pat.w_bits))
			{
				out = out + 1;
			}
		}
	}
	return (out);
}
