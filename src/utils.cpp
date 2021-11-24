#include "defines.hpp"
#include "pattern.hpp"
#include <iostream>

void 		shift_pattern(Pattern &pat, int row, int col)
{
	pat.b_bits = pat.b_bits << (row * BOARD_WIDTH + col);
	pat.w_bits = pat.w_bits << (row * BOARD_WIDTH + col);
}


void 		shift_pattern_other_end(Pattern &pat, int row, int col)
{
	shift_pattern(pat, row - pat.height + 1, col - pat.width + 1);
}


bool 		shift_pattern_to(Pattern &pat, int row, int col)
{
	/*
	Shifts the Pattern to the desired coordinates and updates pat.r_shift and pat.c_shift
	*/
	if (row + pat.end_r - pat.start_r < BOARD_HEIGHT and col + pat.end_c - pat.start_c < BOARD_WIDTH and col + pat.end_c - pat.start_c >= 0)
	{
		int shift = ((row - pat.r_shift - pat.start_r) * BOARD_WIDTH + (col - pat.c_shift - pat.start_c));
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


void 		print_pattern(Pattern &pat)
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
	std::cout << "r_shift: " << pat.r_shift << " c_shift: " <<  pat.c_shift << " start_r: " << pat.start_r <<  " start_c: " << pat.start_c << " end_r: " << pat.end_r << " end_c: " << pat.end_c << std::endl;
	std::cout << std::endl;
}


bool 		shift_pattern_to_other_end(Pattern &pat, int row, int col)
{
	/*
	Shifts the Pattern so the BOTTOM RIGHT OF THE Pattern IS AT the desired coordinates and updates pat.r_shift and pat.c_shift
	*/
	// std::cout << "/* shift other end*/" << std::endl;
	// std::cout << "shift " <<  ((row - pat.r_shift - pat.height + 1) * BOARD_WIDTH + (col - pat.c_shift - pat.width + 1)) << std::endl;
	// print_pattern(pat);
	if (row - pat.end_r + pat.start_r < BOARD_HEIGHT and row - pat.end_r + pat.start_r >= 0 and col - pat.end_c + pat.start_c < BOARD_WIDTH and col - pat.end_c + pat.start_c >= 0)
	{
		int shift = ((row - pat.r_shift - pat.end_r) * BOARD_WIDTH + (col - pat.c_shift - pat.end_c));
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
		pat.r_shift = row - pat.end_r;
		pat.c_shift = col - pat.end_c;
		return (true);
	}
	return (false);
}


inline int	flat_coord(int row, int col)
{
	return (BOARD_WIDTH * row + col);
}


void 		swap_colors(Pattern &pat)
{
	bitboard tmp = pat.b_bits;
	pat.b_bits = pat.w_bits;
	pat.w_bits = tmp;
}





Pattern 	create_capture_pattern(int direction, int player)
{
	Pattern p;
	if (direction == DOWN)
	{
		p.height = 4;
		p.width = 1;
		p.w_bits[flat_coord(0, 0)] = true;
		p.w_bits[flat_coord(3, 0)] = true; 
		p.b_bits[flat_coord(1, 0)] = true; 
		p.b_bits[flat_coord(2, 0)] = true;
		p.start_r = 0;
		p.start_c = 0;
		p.end_r = 3;
		p.end_c = 0;
	}
	if (direction == RIGHT)
	{
		p.height = 1;
		p.width = 4;
		p.w_bits[flat_coord(0, 0)] = true;
		p.w_bits[flat_coord(0, 3)] = true; 
		p.b_bits[flat_coord(0, 1)] = true; 
		p.b_bits[flat_coord(0, 2)] = true;
		p.start_r = 0;
		p.start_c = 0;
		p.end_r = 0;
		p.end_c = 3;
	}
	if (direction == DOWN_RIGHT)
	{
		p.height = 4;
		p.width = 4;
		p.w_bits[flat_coord(0, 0)] = true;
		p.w_bits[flat_coord(3, 3)] = true; 
		p.b_bits[flat_coord(1, 1)] = true; 
		p.b_bits[flat_coord(2, 2)] = true;
		p.start_r = 0;
		p.start_c = 0;
		p.end_r = 3;
		p.end_c = 3;
	}
	if (direction == DOWN_LEFT)
	{
		p.height = 4;
		p.width = 4;
		p.w_bits[flat_coord(3, 0)] = true;
		p.w_bits[flat_coord(0, 3)] = true; 
		p.b_bits[flat_coord(2, 1)] = true; 
		p.b_bits[flat_coord(1, 2)] = true;
		p.start_r = 0;
		p.start_c = 3;
		p.end_r = 3;
		p.end_c = 0;
	}
	if (player == BLACK)
	{
		swap_colors(p);
	}
	p.r_shift = 0;
	p.c_shift = 0;

	return (p);
}


int			get_move_keyboard(void)
{
	int r;
	int c;
	std::cout << "Enter r: "; // no flush needed
	std::cin >> r;
	std::cout << "Enter c: "; // no flush needed
	std::cin >> c;

	return (r * BOARD_WIDTH + c);
}


Pattern 	create_pair_pattern(int direction, int player)
{
	Pattern p;
	if (direction == DOWN)
	{
		p.height = 2;
		p.width = 1;
		p.w_bits[flat_coord(0, 0)] = true;
		p.w_bits[flat_coord(1, 0)] = true; 
		p.start_r = 0;
		p.start_c = 0;
		p.end_r = 1;
		p.end_c = 0;
	}
	if (direction == RIGHT)
	{
		p.height = 2;
		p.width = 1;
		p.w_bits[flat_coord(0, 0)] = true;
		p.w_bits[flat_coord(0, 1)] = true; 
		p.start_r = 0;
		p.start_c = 0;
		p.end_r = 0;
		p.end_c = 1;
	}
	if (direction == DOWN_RIGHT)
	{
		p.height = 2;
		p.width = 2;
		p.w_bits[flat_coord(0, 0)] = true;
		p.w_bits[flat_coord(1, 1)] = true;
		p.start_r = 0;
		p.start_c = 0;
		p.end_r = 1;
		p.end_c = 1; 
	}
	if (direction == DOWN_LEFT)
	{
		p.height = 2;
		p.width = 2;
		p.w_bits[flat_coord(0, 1)] = true;
		p.w_bits[flat_coord(1, 0)] = true; 
		p.start_r = 0;
		p.start_c = 1;
		p.end_r = 1;
		p.end_c = 0; 
	}
	if (player == BLACK)
	{
		swap_colors(p);
	}
	p.r_shift = 0;
	p.c_shift = 0;

	return (p);	
}

Pattern 	create_victory_pattern(int direction, int player)
{
	Pattern p;
	if (direction == DOWN)
	{
		p.height = 5;
		p.width = 1;
		p.w_bits[flat_coord(0, 0)] = true;
		p.w_bits[flat_coord(1, 0)] = true; 
		p.w_bits[flat_coord(2, 0)] = true; 
		p.w_bits[flat_coord(3, 0)] = true; 
		p.w_bits[flat_coord(4, 0)] = true; 

		p.start_r = 0;
		p.start_c = 0;
		p.end_r = 4;
		p.end_c = 0;
	}
	if (direction == RIGHT)
	{
		p.height = 1;
		p.width = 5;
		p.w_bits[flat_coord(0, 0)] = true;
		p.w_bits[flat_coord(0, 1)] = true; 
		p.w_bits[flat_coord(0, 2)] = true; 
		p.w_bits[flat_coord(0, 3)] = true; 
		p.w_bits[flat_coord(0, 4)] = true; 

		p.start_r = 0;
		p.start_c = 0;
		p.end_r = 0;
		p.end_c = 4;
	}
	if (direction == DOWN_RIGHT)
	{
		p.height = 5;
		p.width = 5;
		p.w_bits[flat_coord(0, 0)] = true;
		p.w_bits[flat_coord(1, 1)] = true; 
		p.w_bits[flat_coord(2, 2)] = true; 
		p.w_bits[flat_coord(3, 3)] = true; 
		p.w_bits[flat_coord(4, 4)] = true; 

		p.start_r = 0;
		p.start_c = 0;
		p.end_r = 4;
		p.end_c = 4;
	}
	if (direction == DOWN_LEFT)
	{
		p.height = 5;
		p.width = 5;
		p.w_bits[flat_coord(0, 4)] = true;
		p.w_bits[flat_coord(1, 3)] = true; 
		p.w_bits[flat_coord(2, 2)] = true; 
		p.w_bits[flat_coord(3, 1)] = true; 
		p.w_bits[flat_coord(4, 0)] = true; 

		p.start_r = 0;
		p.start_c = 4;
		p.end_r = 4;
		p.end_c = 0;
	}
	if (player == BLACK)
	{
		swap_colors(p);
	}
	p.r_shift = 0;
	p.c_shift = 0;

	return (p);	
}
