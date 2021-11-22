#include "defines.hpp"
#include <iostream>

void 	shift_pattern(pattern &pat, int row, int col)
{
	pat.b_bits = pat.b_bits << (row * BOARD_WIDTH + col);
	pat.w_bits = pat.w_bits << (row * BOARD_WIDTH + col);
}


void 	shift_pattern_other_end(pattern &pat, int row, int col)
{
	shift_pattern(pat, row - pat.height + 1, col - pat.width + 1);
}


bool 	shift_pattern_to(pattern &pat, int row, int col)
{
	/*
	Shifts the pattern to the desired coordinates and updates pat.r_shift and pat.c_shift
	*/
	if (row + pat.height <= BOARD_HEIGHT and col + pat.width <= BOARD_WIDTH)
	{
		int shift = ((row - pat.r_shift) * BOARD_WIDTH + (col - pat.c_shift));
		if (shift >= 0)
		{
			pat.b_bits = pat.b_bits << shift;
			pat.w_bits = pat.w_bits << shift;
		}
		else
		{
			pat.b_bits = pat.b_bits >> -shift;
			pat.w_bits = pat.w_bits >> -shift;
		}
		pat.r_shift = row;
		pat.c_shift = col;
		return (true);
	}
	return (false);
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
	std::cout << std::endl;
}

bool 	shift_pattern_to_other_end(pattern &pat, int row, int col)
{
	/*
	Shifts the pattern so the BOTTOM RIGHT OF THE PATTERN IS AT the desired coordinates and updates pat.r_shift and pat.c_shift
	*/
	// std::cout << "/* shift other end*/" << std::endl;
	// std::cout << "shift " <<  ((row - pat.r_shift - pat.height + 1) * BOARD_WIDTH + (col - pat.c_shift - pat.width + 1)) << std::endl;
	// print_pattern(pat);
	if (row - pat.height + 1 >= 0 and col - pat.width  + 1 >= 0)
	{
		int shift = ((row - pat.r_shift - pat.height + 1) * BOARD_WIDTH + (col - pat.c_shift - pat.width + 1));
		if (shift >= 0)
		{
			pat.b_bits = pat.b_bits << shift;
			pat.w_bits = pat.w_bits << shift;
		}
		else
		{
			pat.b_bits = pat.b_bits >> -shift;
			pat.w_bits = pat.w_bits >> -shift;
		}
		pat.r_shift = row - pat.height + 1;
		pat.c_shift = col - pat.width + 1;
		return (true);
	}
	return (false);
}

inline int flat_coord(int row, int col)
{
	return (BOARD_WIDTH * row + col);
}


void swap_colors(pattern &pat)
{
	bitboard tmp = pat.b_bits;
	pat.b_bits = pat.w_bits;
	pat.w_bits = tmp;
}


pattern create_capture_pattern(int direction, int player)
{
	pattern p;
	if (direction == DOWN)
	{
		p.height = 4;
		p.width = 1;
		p.w_bits[flat_coord(0, 0)] = true;
		p.w_bits[flat_coord(3, 0)] = true; 
		p.b_bits[flat_coord(1, 0)] = true; 
		p.b_bits[flat_coord(2, 0)] = true; 
	}
	if (direction == RIGHT)
	{
		p.height = 1;
		p.width = 4;
		p.w_bits[flat_coord(0, 0)] = true;
		p.w_bits[flat_coord(0, 3)] = true; 
		p.b_bits[flat_coord(0, 1)] = true; 
		p.b_bits[flat_coord(0, 2)] = true; 
	}
	if (direction == DOWN_RIGHT)
	{
		p.height = 4;
		p.width = 4;
		p.w_bits[flat_coord(0, 0)] = true;
		p.w_bits[flat_coord(3, 3)] = true; 
		p.b_bits[flat_coord(1, 1)] = true; 
		p.b_bits[flat_coord(2, 2)] = true; 
	}
	if (player == BLACK)
	{
		swap_colors(p);
	}
	p.r_shift = 0;
	p.c_shift = 0;

	return (p);
}


int	get_move_keyboard(void)
{
	int r;
	int c;
	std::cout << "Enter r: "; // no flush needed
	std::cin >> r;
	std::cout << "Enter c: "; // no flush needed
	std::cin >> c;

	return (r * BOARD_WIDTH + c);
}