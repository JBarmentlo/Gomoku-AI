#ifndef UTILS_H
#define UTILS_H

#include "defines.hpp"
#include "pattern.hpp"

void 		shift_pattern(Pattern &pat, int row, int col);
bool 		shift_pattern_to(Pattern &pat, int row, int col);

void 		shift_pattern_other_end(Pattern &pat, int row, int col);
bool 		shift_pattern_to_other_end(Pattern &pat, int row, int col);


void 		print_pattern(Pattern &pat);
Pattern 	create_capture_pattern(int direction, int player);
Pattern 	create_pair_pattern(int direction, int player);
Pattern 	create_victory_pattern(int direction, int player);


void 		swap_colors(Pattern &pat);
inline int 	flat_coord(int row, int col);
int			get_move_keyboard(void);

#endif // !UTILS_H