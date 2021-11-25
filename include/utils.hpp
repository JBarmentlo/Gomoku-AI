#ifndef UTILS_H
#define UTILS_H

#include "defines.hpp"

inline int	flat_coord(int row, int col)
{
	return (BOARD_WIDTH * row + col);
}

int			get_move_keyboard(void);

inline bool	is_in_bounds(int row, int col)
{
	return (col < BOARD_WIDTH and row < BOARD_HEIGHT and col >= 0 and row >= 0);
}

#endif // !UTILS_H