#ifndef PATTERN_H
#define PATTERN_H

#include "defines.hpp"
#include "utils.hpp"

typedef struct	s_pattern{
	bitboard 	b_bits;
	bitboard 	w_bits;
	bitboard	e_bits;
	int			color;
	int			r_shift = 0;
	int			c_shift = 0;
	int			start_r;
	int			start_c;
	int			end_r;
	int			end_c;
	int			direction;
	int			size;
}				pattern;

typedef		pattern (*pattern_generator)(int, int);

// void 		shift_pattern(pattern &pat, int row, int col);
bool 		shift_pattern_to(pattern &pat, int row, int col);

// void 		shift_pattern_other_end(pattern &pat, int row, int col);
bool 		shift_pattern_to_other_end(pattern &pat, int row, int col);


void 		print_pattern(pattern &pat);
pattern 	create_capture_pattern(int direction, int player);
pattern 	create_pair_pattern(int direction, int player);
pattern 	create_victory_pattern(int direction, int player);


void 		swap_colors(pattern &pat);

#endif // DEBUG