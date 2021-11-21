#include <bitset>
#include <iostream>

#include "defines.hpp"
#include "board.hpp"

int main()
{


	t_state state;
	t_fullboard board;
	state.board = board;
	set_piece(2, 3, WHITE, state);
	set_piece(2, 7, WHITE, state);
	set_piece(3, 6, BLACK, state);

	print_state(state);
}