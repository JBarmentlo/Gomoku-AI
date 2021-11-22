#ifndef UTILS_H
#define UTILS_H

#include "defines.hpp"

void 		shift_pattern(pattern &pat, int row, int col);
void 		shift_pattern_other_end(pattern &pat, int row, int col);


void 		print_pattern(pattern &pat);
pattern 	create_capture_pattern(int direction, int player);
void 		swap_colors(pattern &pat);
inline int 	flat_coord(int row, int col);
int			get_move_keyboard(void);

#endif // !UTILS_H