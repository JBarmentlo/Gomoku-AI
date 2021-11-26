#include <bitset>
#include <iostream>

#include "defines.hpp"
#include "utils.hpp"
#include "state.hpp"
#include "eval.hpp"
#include "pattern.hpp"

#include "minimax.hpp"

#include <chrono>

// typedef std::chrono::steady_clock::time_point timepoint;


void play_game(int depth, bool cpu1, bool cpu2, int limit = 10)
{
	State s;
	// s.value_coord_fun = s.find_pattern_around_last_move();
	
	// s.set_piece(9,9);
	// s.player = BLACK;
	int folds = 0;
	int move;
	if (cpu1)
		s.live_board.set(9 * BOARD_WIDTH + 9, true);
	while(true)
	{
		if (s.player == WHITE)
		{
			if (s.game_win)
			{
				std::cout << "BLACK WON" << std::endl;
				return;
			}
			std::cout << "White to play" << std::endl;
			if (cpu1)
			{
				std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
				move = minimax(s, depth);
				std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
				std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000 << "." << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() % 1000000) / 10000 <<  "s" << std::endl;

			}
			else
			{
				move = get_move_keyboard();				
			}
		}
		else
		{
			if (s.game_win)
			{
				std::cout << "WHITE WON" << std::endl;
				return;
			}
			std::cout << "Black to play" << std::endl;
			if (cpu2)
			{
				std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
				move = minimax(s, depth);
				std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
				std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000 << "." << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() % 1000000) / 10000 <<  "s" << std::endl;
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
		folds += 1;
		if (folds >= limit and cpu1 and cpu2)
			break;
	}
}

#include <array>
#include <algorithm>

bool compare_scores(const State& s1, const State& s2)
{
	return (s1.score > s2.score);
}


// TODO add empyt to patterns
int main()
{
	State s;
	// std::cout << (1 << 2) << std::endl;
	play_game(5, true, true, 20);
	// s.coord_evaluation_function = tuples_eval_at_coord;
	// s = s.make_baby_from_coord(flat_coord(9, 9));
	// s = s.make_baby_from_coord(flat_coord(8, 8));
	// s = s.make_baby_from_coord(flat_coord(9, 8));
	// s = s.make_baby_from_coord(flat_coord(8, 7));
	// s = s.make_baby_from_coord(flat_coord(9, 7));

	// s = s.make_baby_from_coord(flat_coord(9, 6));
	// s = s.make_baby_from_coord(flat_coord(7, 8));

	// s = s.make_baby_from_coord(flat_coord(8, 9));
	// s = s.make_baby_from_coord(flat_coord(10, 5));


	// s.print();
	// pattern p = create_capture_pattern(DOWN_LEFT, WHITE, 1);

	// print_pattern(p);
	// if (p.color & BLACK != 0)
		// std::cout << "color: " <<  (p.color & BLACK) << std::endl;
	// std::cout << "shift: " << shift_pattern_to(p, 1, 2) << std::endl;
	// p.w_bits = p.w_bits << 19;
	// p.b_bits = p.b_bits << 19;
	// print_pattern(p);
	// s.player = NEXT_PLAYER(s.player);
	// std::cout << s.is_win() << std::endl;
	// s.player = NEXT_PLAYER(s.player);
	// s.compute_captures();
	// std::cout << s.find_pattern_around_last_move(create_triplet_pattern, NEXT_PLAYER(s.player)) << std::endl;


	// pattern p = create_capture_pattern(DOWN, WHITE);
	// print_pattern(p);
	// swap_colors(p);
	// print_pattern(p);

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
	// pattern p = create_capture_pattern(DOWN_LEFT, WHITE, 0);

	// // swap_colors(c);
	// // print_pattern(c);
	// // std::cout << c.color << std::endl;

	// for (int r = 0; r < BOARD_HEIGHT; r++)
	// {
	// 	for (int c = 0; c < 19; c++)
	// 	{
	// 		pattern p = create_capture_pattern(DOWN_LEFT, WHITE, 3);
	// 		std::cout << "r: " << r << ",c: " << c << std::endl;
	// 		if (shift_pattern_to(p, r, c))
	// 			print_pattern(p);
	// 		/* code */
	// 	}
	// }

	// // * 1500000 iteration should take about 0.4 s 
	// for (int i = 0; i < 1500000; i++)
	// {
	// 	// pattern c = create_pair_pattern(DOWN, i % 2);
	// 	// shift_pattern_to(c, i / 19, i % 19);
	// 	// std::bitset<10> b1("1111010000");

	// 	s.make_baby_from_coord(i % BOARD_SIZE);
	// 	if (i % BOARD_SIZE == 0)
	// 		s = State();
	// }
}