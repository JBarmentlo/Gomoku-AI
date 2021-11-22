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
	s.value_coord_fun = pairs_at_coord;
	
	// s.set_piece(0,0);
	// minimax(s, true, 5);
	for (int i = 0; i < 1000000; i++)
	{
		// s.set_piece(i % BOARD_SIZE);
		// s.compute_captures();
		// s.update_live_board();
		// s.score += pairs_at_coord(s);
		s.make_baby_from_coord(i % BOARD_SIZE);
	}
	// pattern p = create_capture_pattern(RIGHT, WHITE);
	// print_pattern(p);
	// shift_pattern_to(p, 0, 0);
	// print_pattern(p);


	// s.set_piece(0,1);
	// State s2 = s.make_baby_from_coord(2);
	// s2.print();

	// int v = s.value_coord_fun(s);
	// std::cout << v << std::endl; 
	// s.set_piece(18, 14);

	// s.set_piece(1,0);
	// s.set_piece(18, 12);

	// s.set_piece(1,1);
	// s.set_piece(18, 13);

	// s.set_piece(0, 1);
	// s.set_piece(18, 15);


	// s.set_piece(0, 2);
	// s.set_piece(18, 7);

	// s.set_piece(0, 3);
	// s.set_piece(18, 1);
	// s.print();

	// std::cout << count_pairs(s, BLACK) << std::endl;


	// pattern p;
	// p.w_bits.set(0);
	// p.w_bits.set(1);
	// // p.b_bits.set(0);
	// // p.b_bits.set(3);
	// p.width = 2;
	// p.height = 1;
	// print_pattern(p);

	// std::cout << s.count_pattern(p) << std::endl;



	// state.board.white = state.board.white >> 4;
	// state.board.black = state.board.black >> 4;

	// print_state(state);

	// s.find_pattern_around_last_move(create_capture_pattern);
	int move;
	// while (true)
	// {
	// 	if (s.player == WHITE)
	// 		std::cout << "White to play" << std::endl;
	// 	else
	// 		std::cout << "Black to play" << std::endl;

	// 	move = get_move_keyboard();
	// 	std::cout << "Move: " << move << std::endl;
	// 	s.set_piece(move / BOARD_WIDTH, move % BOARD_WIDTH);
	// 	std::cout << "Moved: " << std::endl;

	// 	if (s.compute_captures() != 0)
	// 		std::cout << "Captured" << std::endl;
		
	// 	s.print();
	// 	update_pair_eval(s);
	// 	std::cout << "scor: " << s.score << std::endl;
	// 	std::cout << "eval: " << pair_eval(s) << std::endl;
	// 	s.player = (s.player + 1) % 2;
	// // }
	// pattern p = create_pair_pattern(DOWN_LEFT, WHITE);
	// for (int i = 0; i < 19; i++)
	// {
	// 	for (int j = 0; j < 19; j++)
	// 	{
	// 		if (shift_pattern_to_other_end(p, i, j))
	// 		{
	// 			std::cout << "r: " << i << "c: " << j << std::endl;
	// 			print_pattern(p);
	// 		}
	// 	}
	// }
	// std::cout << "r: " << 1 << "c: " << 1 << std::endl;
	// shift_pattern_to_other_end(p, 1, 1);
	// print_pattern(p);

	// s.set_piece(1, 0);
	// s.set_piece(2, 0);
	// s.player = BLACK;
	// s.set_piece(3, 0);
	// s.set_piece(0, 0);
	// s.print();
	// int a = s.compute_captures();
	// if (a != 0)
	// 	std::cout << "Captured: " << a << std::endl;
	// s.print();


	// bitboard b;
	// b[10] = true;
	// b = b << -9;
	// std::cout << b << std::endl;

	// std::cout << (DOWN | RIGHT) << std::endl;
	// pattern p = create_capture_pattern(DOWN_RIGHT, BLACK);
	// print_pattern(p);
	// int move;
	// while (true)
	// {
	// 	move = get_move_keyboard();
	// 	s.set_piece(move / BOARD_WIDTH, move % BOARD_WIDTH);
	// 	pattern p = create_capture_pattern(DOWN_RIGHT, s.player);
	// 	if (shift_pattern_to(p, move / BOARD_WIDTH, move % BOARD_WIDTH))
	// 	{
	// 		std::cout << "posible pattern" << std::endl;
	// 		print_pattern(p);
	// 	}
	// 	else
	// 	{
	// 		std::cout << "Impossible" << std::endl;
	// 	}
	// 	// std::cout << "State" << std::endl;
	// 	// s.print();
	// 	std::cout << std::endl << std::endl;
	// }
}