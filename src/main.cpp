#include <bitset>
#include <iostream>

#include "defines.hpp"
#include "utils.hpp"
#include "state.hpp"
#include "eval.hpp"
#include "minimax.hpp"


int main()
{
	State s;
	s.value_coord_fun = pairs_at_coord_color;
	
	// s.set_piece(9,9);
	// s.player = BLACK;
	int move;
	while(true)
	{
		if (s.player == WHITE)
		{
			if (s.find_pattern_around_last_move(create_victory_pattern, BLACK) != 0)
			{
				std::cout << "BLACK WON" << std::endl;
				return(0);
			}
			std::cout << "White to play" << std::endl;
			move = get_move_keyboard();
		}
		else
		{
			if (s.find_pattern_around_last_move(create_victory_pattern, WHITE) != 0)
			{
				std::cout << "WHITE WON" << std::endl;
				return(0);
			}
			std::cout << "Black to play" << std::endl;
			move = minimax(s, false, 4);
		}
		std::cout << "Move: " << move << std::endl;
		s = s.make_baby_from_coord(move);
		std::cout << "Board made" << std::endl;
		s.print();
	}

}