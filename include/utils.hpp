#ifndef UTILS_H
#define UTILS_H

#include "defines.hpp"
#include "pattern.hpp"

void 		shift_pattern(pattern &pat, int row, int col);
bool 		shift_pattern_to(pattern &pat, int row, int col);

void 		shift_pattern_other_end(pattern &pat, int row, int col);
bool 		shift_pattern_to_other_end(pattern &pat, int row, int col);


void 		print_pattern(pattern &pat);
pattern 	create_capture_pattern(int direction, int player);
pattern 	create_pair_pattern(int direction, int player);
pattern 	create_victory_pattern(int direction, int player);


void 		swap_colors(pattern &pat);
inline int 	flat_coord(int row, int col);
int			get_move_keyboard(void);

#endif // !UTILS_H