#include "defines.hpp"
#include "utils.hpp"
#include "pattern.hpp"

#include <iostream>

// void 		shift_pattern(pattern &pat, int row, int col)
// {
// 	pat.b_bits = pat.b_bits << (row * BOARD_WIDTH + col);
// 	pat.w_bits = pat.w_bits << (row * BOARD_WIDTH + col);
// }


// void 		shift_pattern_other_end(pattern &pat, int row, int col)
// {
// 	shift_pattern(pat, row - pat.height + 1, col - pat.width + 1);
// }


bool		is_shiftable_to(pattern &pat, int row, int col)
{
	return is_in_bounds(pat.start_r +  row, pat.start_c + col) and is_in_bounds(pat.end_r +  row, pat.end_c + col);
}


bool 		shift_pattern_to(pattern &pat, int row, int col)
{
	/*
	Shifts the pattern to the desired coordinates and updates pat.r_shift and pat.c_shift
	*/
	if (not is_in_bounds(pat.end_r - pat.start_r + row, pat.end_c - pat.start_c  + col))
		return (false);
	
	int shift = (row - pat.r_shift - pat.start_r) * BOARD_WIDTH + (col - pat.c_shift - pat.start_c);
	// std::cout << "shift: " << shift << std::endl;
	if (shift > 0)
	{
		// if (pat.color & WHITE)
		pat.w_bits = pat.w_bits << shift;
		// if (pat.color & BLACK)
		pat.b_bits = pat.b_bits << shift;
		// if (pat.color & EMPTY)
		pat.e_bits = pat.e_bits << shift;
	}
	else
	{
		pat.w_bits = pat.w_bits >> -shift;
		// if (pat.color & BLACK)
		pat.b_bits = pat.b_bits >> -shift;
		// if (pat.color & EMPTY)
		pat.e_bits = pat.e_bits >> -shift;
	}
	// std::cout << "r_shift: " << pat.r_shift << "row:" std::endl;
	pat.r_shift = row - pat.start_r;
	pat.c_shift = col - pat.start_c;

	return (true);
}


void 		print_pattern(pattern &pat)
{
	std::string symbols[3] = {"O", "X", " "};
	std::cout << "r_shift: " << pat.r_shift << ", c_shift: " <<  pat.c_shift << ", start_r: " << pat.start_r <<  ", start_c: " << pat.start_c << ", end_r: " << pat.end_r << ", end_c: " << pat.end_c << std::endl;

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
				std::cout << "  " << symbols[1] << " ";
			else if (pat.w_bits[r * BOARD_WIDTH + c])
				std::cout << "  " << symbols[0] << " ";
			else
				std::cout << "  " << symbols[2] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


bool 		shift_pattern_to_other_end(pattern &pat, int row, int col)
{
	if (not is_in_bounds(pat.start_r - pat.end_r +  row, pat.start_c - pat.end_c + col))
		return (false);
	
	int shift = flat_coord(row - pat.r_shift -  pat.end_r,col - pat.c_shift - pat.end_c);
	if (shift > 0)
	{
		// if (pat.color & WHITE)
		pat.w_bits = pat.w_bits << shift;
		// if (pat.color & BLACK)
		pat.b_bits = pat.b_bits << shift;
		// if (pat.color & EMPTY)
		pat.e_bits = pat.e_bits << shift;
	}
	else
	{
		pat.w_bits = pat.w_bits >> -shift;
		// if (pat.color & BLACK)
		pat.b_bits = pat.b_bits >> -shift;
		// if (pat.color & EMPTY)
		pat.e_bits = pat.e_bits >> -shift;
	}
	return (true);
}


// bool 		shift_pattern_to_other_end(pattern &pat, int row, int col)
// {
// 	/*
// 	Shifts the pattern so the BOTTOM RIGHT OF THE PATTERN IS AT the desired coordinates and updates pat.r_shift and pat.c_shift
// 	*/
// 	// std::cout << "/* shift other end*/" << std::endl;
// 	// std::cout << "shift " <<  ((row - pat.r_shift - pat.height + 1) * BOARD_WIDTH + (col - pat.c_shift - pat.width + 1)) << std::endl;
// 	// print_pattern(pat);
// 	if (row - pat.end_r + pat.start_r < BOARD_HEIGHT and row - pat.end_r + pat.start_r >= 0 and col - pat.end_c + pat.start_c < BOARD_WIDTH and col - pat.end_c + pat.start_c >= 0)
// 	{
// 		int shift = ((row - pat.r_shift - pat.end_r) * BOARD_WIDTH + (col - pat.c_shift - pat.end_c));
// 		if (shift >= 0)
// 		{
// 			pat.b_bits = pat.b_bits << shift;
// 			pat.w_bits = pat.w_bits << shift;
// 		}
// 		else
// 		{
// 			pat.b_bits = pat.b_bits >> -shift;
// 			pat.w_bits = pat.w_bits >> -shift;
// 		}
// 		pat.r_shift = row - pat.end_r;
// 		pat.c_shift = col - pat.end_c;
// 		return (true);
// 	}
// 	return (false);
// }


void 		swap_colors(pattern &pat)
{
	bitboard tmp = pat.b_bits;
	pat.b_bits = pat.w_bits;
	pat.w_bits = tmp;
}





pattern 	create_capture_pattern(int direction, int player)
{
	pattern p;
	if (direction == DOWN)
	{
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


// pattern 	create_pair_pattern(int direction, int player)
// {
// 	pattern p;
// 	if (direction == DOWN)
// 	{
// 		p.height = 2;
// 		p.width = 1;
// 		p.w_bits[flat_coord(0, 0)] = true;
// 		p.w_bits[flat_coord(1, 0)] = true; 
// 		p.start_r = 0;
// 		p.start_c = 0;
// 		p.end_r = 1;
// 		p.end_c = 0;
// 	}
// 	if (direction == RIGHT)
// 	{
// 		p.height = 2;
// 		p.width = 1;
// 		p.w_bits[flat_coord(0, 0)] = true;
// 		p.w_bits[flat_coord(0, 1)] = true; 
// 		p.start_r = 0;
// 		p.start_c = 0;
// 		p.end_r = 0;
// 		p.end_c = 1;
// 	}
// 	if (direction == DOWN_RIGHT)
// 	{
// 		p.height = 2;
// 		p.width = 2;
// 		p.w_bits[flat_coord(0, 0)] = true;
// 		p.w_bits[flat_coord(1, 1)] = true;
// 		p.start_r = 0;
// 		p.start_c = 0;
// 		p.end_r = 1;
// 		p.end_c = 1; 
// 	}
// 	if (direction == DOWN_LEFT)
// 	{
// 		p.height = 2;
// 		p.width = 2;
// 		p.w_bits[flat_coord(0, 1)] = true;
// 		p.w_bits[flat_coord(1, 0)] = true; 
// 		p.start_r = 0;
// 		p.start_c = 1;
// 		p.end_r = 1;
// 		p.end_c = 0; 
// 	}
// 	if (player == BLACK)
// 	{
// 		swap_colors(p);
// 	}
// 	p.r_shift = 0;
// 	p.c_shift = 0;

// 	return (p);	
// }

// pattern 	create_victory_pattern(int direction, int player)
// {
// 	pattern p;
// 	if (direction == DOWN)
// 	{
// 		p.height = 5;
// 		p.width = 1;
// 		p.w_bits[flat_coord(0, 0)] = true;
// 		p.w_bits[flat_coord(1, 0)] = true; 
// 		p.w_bits[flat_coord(2, 0)] = true; 
// 		p.w_bits[flat_coord(3, 0)] = true; 
// 		p.w_bits[flat_coord(4, 0)] = true; 

// 		p.start_r = 0;
// 		p.start_c = 0;
// 		p.end_r = 4;
// 		p.end_c = 0;
// 	}
// 	if (direction == RIGHT)
// 	{
// 		p.height = 1;
// 		p.width = 5;
// 		p.w_bits[flat_coord(0, 0)] = true;
// 		p.w_bits[flat_coord(0, 1)] = true; 
// 		p.w_bits[flat_coord(0, 2)] = true; 
// 		p.w_bits[flat_coord(0, 3)] = true; 
// 		p.w_bits[flat_coord(0, 4)] = true; 

// 		p.start_r = 0;
// 		p.start_c = 0;
// 		p.end_r = 0;
// 		p.end_c = 4;
// 	}
// 	if (direction == DOWN_RIGHT)
// 	{
// 		p.height = 5;
// 		p.width = 5;
// 		p.w_bits[flat_coord(0, 0)] = true;
// 		p.w_bits[flat_coord(1, 1)] = true; 
// 		p.w_bits[flat_coord(2, 2)] = true; 
// 		p.w_bits[flat_coord(3, 3)] = true; 
// 		p.w_bits[flat_coord(4, 4)] = true; 

// 		p.start_r = 0;
// 		p.start_c = 0;
// 		p.end_r = 4;
// 		p.end_c = 4;
// 	}
// 	if (direction == DOWN_LEFT)
// 	{
// 		p.height = 5;
// 		p.width = 5;
// 		p.w_bits[flat_coord(0, 4)] = true;
// 		p.w_bits[flat_coord(1, 3)] = true; 
// 		p.w_bits[flat_coord(2, 2)] = true; 
// 		p.w_bits[flat_coord(3, 1)] = true; 
// 		p.w_bits[flat_coord(4, 0)] = true; 

// 		p.start_r = 0;
// 		p.start_c = 4;
// 		p.end_r = 4;
// 		p.end_c = 0;
// 	}
// 	if (player == BLACK)
// 	{
// 		swap_colors(p);
// 	}
// 	p.r_shift = 0;
// 	p.c_shift = 0;

// 	return (p);	
// }