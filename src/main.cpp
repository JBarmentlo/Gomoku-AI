#include <bitset>
#include <iostream>

#include "defines.hpp"
#include "utils.hpp"
#include "state.hpp"
#include "eval.hpp"
#include "minimax.hpp"

void play_game(int depth, bool cpu1, bool cpu2)
{
	State s;
	s.value_coord_fun = pairs_at_coord_color;
	
	// s.set_piece(9,9);
	// s.player = BLACK;
	int move;
	if (cpu1)
		s.live_board.set(9 * BOARD_WIDTH + 9, true);
	while(true)
	{
		if (s.player == WHITE)
		{
			if (s.find_pattern_around_last_move(create_victory_pattern, BLACK) != 0)
			{
				std::cout << "BLACK WON" << std::endl;
				return;
			}
			std::cout << "White to play" << std::endl;
			if (cpu1)
			{
				move = minimax(s, true, depth);
			}
			else
			{
				move = get_move_keyboard();				
			}
		}
		else
		{
			if (s.find_pattern_around_last_move(create_victory_pattern, WHITE) != 0)
			{
				std::cout << "WHITE WON" << std::endl;
				return;
			}
			std::cout << "Black to play" << std::endl;
			if (cpu2)
			{
				move = minimax(s, false, depth);
			}
			else
			{
				move = get_move_keyboard();				
			}
		}
		std::cout << "Move: " << move << std::endl;
		s = s.make_baby_from_coord(move);
		std::cout << "Board made" << std::endl;
		s.print();
	}
}


int main()
{
	State s;

	play_game(5, true, true);

	for (int i = 0; i < 1500000; i++)
	{
		s.make_baby_from_coord(i % BOARD_SIZE);
		if (i % BOARD_SIZE == 0)
			s = State();
	}
}