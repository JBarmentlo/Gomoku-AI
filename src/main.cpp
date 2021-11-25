#include <bitset>
#include <iostream>

#include "defines.hpp"
#include "utils.hpp"
#include "state.hpp"
#include "eval.hpp"
#include "pattern.hpp"

#include "minimax.hpp"

void play_game(int depth, bool cpu1, bool cpu2)
{
	State s;
	// s.value_coord_fun = s.find_pattern_around_last_move();
	
	// s.set_piece(9,9);
	// s.player = BLACK;
	int move;
	if (cpu1)
		s.live_board.set(9 * BOARD_WIDTH + 9, true);
	while(true)
	{
		if (s.player == WHITE)
		{
			// if (s.find_pattern_around_last_move(create_victory_pattern, BLACK) != 0)
			// {
			// 	std::cout << "BLACK WON" << std::endl;
			// 	return;
			// }
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
			// if (s.find_pattern_around_last_move(create_victory_pattern, WHITE) != 0)
			// {
			// 	std::cout << "WHITE WON" << std::endl;
			// 	return;
			// }
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
	// play_game(0, false, false);
	// s = s.make_baby_from_coord(flat_coord(1, 1));
	// s = s.make_baby_from_coord(flat_coord(0, 0));
	// s = s.make_baby_from_coord(flat_coord(2, 2));
	// s = s.make_baby_from_coord(flat_coord(3, 3));
	// s.print();
	// s.player = NEXT_PLAYER(s.player);
	// s.compute_captures();

	pattern p = create_capture_pattern(DOWN, WHITE);
	print_pattern(p);
	swap_colors(p);
	print_pattern(p);

	// s = s.make_baby_from_coord(flat_coord(9, 9));
	// std::cout << "/* message */" << std::endl;
	// s = s.make_baby_from_coord(flat_coord(10, 10));
	// std::cout << "/* message */" << std::endl;
	// s = s.make_baby_from_coord(flat_coord(11, 11));
	// std::cout << "/* message */" << std::endl;
	// s = s.make_baby_from_coord(flat_coord(12, 12));
	// s = s.make_baby_from_coord(flat_coord(13, 13));
	// std::cout << "/* message */" << std::endl;
	// s = s.make_baby_from_coord(flat_coord(14, 14));
	// std::cout << "/* message */" << std::endl;
	// s = s.make_baby_from_coord(flat_coord(15, 15));
	// std::cout << "/* message */" << std::endl;
	// s = s.make_baby_from_coord(flat_coord(16, 16));
	// std::cout << "/* message */" << std::endl;
	// s = s.make_baby_from_coord(flat_coord(17, 17));
	// std::cout << "/* message */" << std::endl;
	// s = s.make_baby_from_coord(flat_coord(18, 18));
	// std::cout << "/* message */" << std::endl;
	// s = s.make_baby_from_coord(flat_coord(18, 17));
	// std::cout << "/* message */" << std::endl;
	// s = s.make_baby_from_coord(flat_coord(18, 16));
	// std::cout << "/* message */" << std::endl;
	// s = s.make_baby_from_coord(flat_coord(18, 1));
	// std::cout << "/* message */" << std::endl;
	// s = s.make_baby_from_coord(flat_coord(18, 15));
	// std::cout << "/* message */" << std::endl;
	// s = s.make_baby_from_coord(flat_coord(18, 14));
	// s = s.make_baby_from_coord(flat_coord(18, 18));

	// s.print();


	// play_game(5, true, true);

//  TODO TEST THE COLOR SWAP YOU MOROOONE
	// TODO checck negative offset pattern

	// pattern p = create_pair_pattern(DOWN, WHITE, 1);
	// // swap_colors(c);
	// // print_pattern(c);
	// // std::cout << c.color << std::endl;

	// for (int r = 0; r < BOARD_HEIGHT; r++)
	// {
	// 	for (int c = 0; c < 19; c++)
	// 	{
	// 		std::cout << "r: " << r << ",c: " << c << std::endl;
	// 		if (shift_pattern_to(p, r, c))
	// 			print_pattern(p);
	// 		/* code */
	// 	}
	// }

	// for (int i = 0; i < 15000000; i++)
	// {
	// 	pattern c = create_pair_pattern(DOWN, i % 2);
	// 	shift_pattern_to(c, i / 19, i % 19);
	// 	// std::bitset<10> b1("1111010000");

	// 	// s.make_baby_from_coord(i % BOARD_SIZE);
	// 	// if (i % BOARD_SIZE == 0)
	// 		// s = State();
	// }
}