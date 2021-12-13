#include <bitset>
#include <iostream>
#include <iomanip>

#include "defines.hpp"
#include "utils.hpp"
#include "state.hpp"
#include "eval.hpp"
#include "pattern.hpp"

#include "minimax.hpp"

#include <chrono>
#include <deque>

// typedef std::chrono::steady_clock::time_point timepoint;


void play_game(int depth, bool cpu1, bool cpu2, int limit = 10, State s = State())
{
	s.coord_evaluation_function = eval_surround_square;
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
				std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000 << "." << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() % 1000000) / 100000 << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() % 100000) / 10000 <<  "s" << std::endl;
				std::setfill(' ');
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
				std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000 << "." << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() % 1000000) / 100000 << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() % 100000) / 10000 <<  "s" << std::endl;
				
				// std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000 << "." << std::setw(2) << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() % 1000000) / 10000 <<  "s" << std::endl;
				std::setfill(' ');
			}
			else
			{
				move = get_move_keyboard();				
			}
		}
		std::cout << "Move: " << move /  BOARD_WIDTH << ", " << move % BOARD_WIDTH  << std::endl;
		if (move == -12)
		{
			std::cout << "NO MORE MOVES" << std::endl;
			return;
		}
		s = s.make_baby_from_coord(move);
		std::cout << std::endl;

		// // s.print_score_board();
		std::cout << "free threes: " << s.free_threes << std::endl;
		s.print();

		folds += 1;
		if (folds >= limit and cpu1 and cpu2)
		{
			s.print_score_board();
			break;
		}
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
	s.set_piece(flat_coord(0, 0));
	s.set_piece(flat_coord(0, 1));
	s.set_piece(flat_coord(0, 2));
	eval_surround_square(s, s.last_move);
	s.print();
	std::cout << "frees: " << s.free_threes << std::endl;
	// play_game(10, false , false, 20);
}