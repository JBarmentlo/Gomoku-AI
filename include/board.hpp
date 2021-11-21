#ifndef BOARD_H
#define BOARD_H

#include "defines.hpp"

typedef struct 	s_fullboard {
	bitboard black;
	bitboard white;

}				t_fullboard;


typedef struct	s_state {
	t_fullboard	board;
	int			white_captures;
	int			black_captures;
}				t_state;

bool	set_piece(int row, int col, int player, t_state &state);
void	print_state(t_state &state);
int		get_square(int row, int col, t_fullboard &board);
#endif