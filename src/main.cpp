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
		std::cout << "Move: " << move /  BOARD_WIDTH << ", " << move % BOARD_WIDTH  << std::endl;
		s = s.make_baby_from_coord(move);
		std::cout << "Board made" << std::endl;
		s.print();
	}
}


int main()
{
	State s;
	std::bitset<10> b1("1111010000");
	std::cout << NEXT_PLAYER(WHITE) << std::endl;
	std::cout << NEXT_PLAYER(BLACK) << std::endl;
	// std::cout << FLAT_COORD(1, 2) << std::endl;
	s = s.make_baby_from_coord(FLAT_COORD(9, 9));
	s = s.make_baby_from_coord(FLAT_COORD(10, 10));
	s = s.make_baby_from_coord(FLAT_COORD(11, 11));
	// s = s.make_baby_from_coord(FLAT_COORD(12, 12));
	// s = s.make_baby_from_coord(FLAT_COORD(13, 13));
	// s = s.make_baby_from_coord(FLAT_COORD(14, 14));
	// s = s.make_baby_from_coord(FLAT_COORD(15, 15));
	// s = s.make_baby_from_coord(FLAT_COORD(16, 16));
	// s = s.make_baby_from_coord(FLAT_COORD(17, 17));
	// s = s.make_baby_from_coord(FLAT_COORD(18, 18));
	// s = s.make_baby_from_coord(FLAT_COORD(18, 17));
	// s = s.make_baby_from_coord(FLAT_COORD(18, 16));
	// s = s.make_baby_from_coord(FLAT_COORD(18, 1));
	// s = s.make_baby_from_coord(FLAT_COORD(18, 15));
	// s = s.make_baby_from_coord(FLAT_COORD(18, 14));
	// s = s.make_baby_from_coord(FLAT_COORD(18, 18));

	// s.print(true);


	play_game(5, true, true);

	// for (int i = 0; i < 15000000; i++)
	// {
	// 	Pattern c = create_capture_pattern(DOWN, i % 2);
	// 	std::bitset<10> b1("1111010000");

	// 	// s.make_baby_from_coord(i % BOARD_SIZE);
	// 	// if (i % BOARD_SIZE == 0)
	// 	// 	s = State();
	// }
}