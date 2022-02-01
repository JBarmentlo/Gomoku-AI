#include <bitset>
#include <iostream>
#include <iomanip>

#include "defines.hpp"
#include "utils.hpp"
#include "state.hpp"
#include "eval.hpp"
#include "pattern.hpp"

#include "minimax.hpp"
#include "server.hpp"

#include <chrono>
#include <deque>

// typedef std::chrono::steady_clock::time_point timepoint;


State play_game(int depth, bool cpu1, bool cpu2, int limit = 10, State s = State())
{
	s.coord_evaluation_function = eval_surround_square;
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
				return s;
			}
			std::cout << "White to play" << std::endl;
			if (cpu1)
			{
				std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
				move = minimax_fred_start(s, depth);
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
				return s;
			}
			std::cout << "Black to play" << std::endl;
			if (cpu2)
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
		std::cout << "Move: " << move /  BOARD_WIDTH << ", " << move % BOARD_WIDTH  << std::endl;
		if (move == -12)
		{
			std::cout << "NO MORE MOVES" << std::endl;
			return s;
		}
		s = s.make_baby_from_coord(move);
		std::cout << std::endl;

		s.print();

		folds += 1;
		if (folds >= limit and cpu1 and cpu2)
		{
			s.print();
			// s.print_score_board();
			break;
		}
	}
	return s;
}


State play_game_beam(int depth, bool cpu1, bool cpu2, int limit = 10, State s = State())
{
	s.coord_evaluation_function = eval_surround_square;
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
				return s;
			}
			std::cout << "White to play" << std::endl;
			if (cpu1)
			{
				std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
				move = minimax_beam(s, depth);
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
				return s;
			}
			std::cout << "Black to play" << std::endl;
			if (cpu2)
			{
				std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
				// move = minimax(s, depth);
				move = minimax_beam(s, depth);

				std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
				std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000 << "." << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() % 1000000) / 100000 << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() % 100000) / 10000 <<  "s" << std::endl;
				
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
			return s;
		}
		s = s.make_baby_from_coord(move);
		std::cout << std::endl;

		s.print();

		folds += 1;
		if (folds >= limit and cpu1 and cpu2)
		{
			s.print();
			// s.print_score_board();
			break;
		}
	}
	return s;
}


State play_game_beam_vs_classic(int depth, bool cpu1, bool cpu2, int limit = 10, State s = State())
{
	s.coord_evaluation_function = eval_surround_square;
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
				return s;
			}
			std::cout << "White to play" << std::endl;
			if (cpu1)
			{
				std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
				move = minimax_beam(s, depth);
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
				return s;
			}
			std::cout << "Black to play" << std::endl;
			if (cpu2)
			{
				std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
				move = minimax(s, depth);
				// move = minimax_beam(s, depth);

				std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
				std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000 << "." << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() % 1000000) / 100000 << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() % 100000) / 10000 <<  "s" << std::endl;
				
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
			return s;
		}
		s = s.make_baby_from_coord(move);
		std::cout << std::endl;

		s.print();

		folds += 1;
		if (folds >= limit and cpu1 and cpu2)
		{
			s.print();
			// s.print_score_board();
			break;
		}
	}
	return s;
}

bool compare_scores(const State& s1, const State& s2)
{
	return (s1.score > s2.score);
}

// #include "thread_pool.hpp"


int main()
{
	// thread_pool pool(std::thread::hardware_concurrency() - 1);
	// std::cout << pool.get_thread_count() << std::endl;
	// std::future<int> fut2 = pool.submit(lolilol, 2);

	// fut2.wait_for(std::chrono::seconds(1));


	play_game(7, true, true, 15);
	// play_game_beam(7, true, true, 15);

	State s;
	s.coord_evaluation_function = eval_surround_square;
	// s = s.make_baby_from_coord(flat_coord(9, 9));
	// s = s.make_baby_from_coord(flat_coord(8, 9));
	// s = s.make_baby_from_coord(flat_coord(8, 8));
	// s = s.make_baby_from_coord(flat_coord(7, 7));
	// s = s.make_baby_from_coord(flat_coord(10, 10));
	// s = s.make_baby_from_coord(flat_coord(6, 7));
	// s = s.make_baby_from_coord(flat_coord(5, 7));
	// s = s.make_baby_from_coord(flat_coord(7, 8));
	// s = s.make_baby_from_coord(flat_coord(11, 11));
	// s = s.make_baby_from_coord(flat_coord(12, 12));
	// s = s.make_baby_from_coord(flat_coord(7, 6));
	// s = s.make_baby_from_coord(flat_coord(9, 10));
	// s.print();
	// s = s.make_baby_from_coord(flat_coord(5, 6));
	// s.print();
	// std::cout << "win: " << s.game_win << " last chance: " << s.last_chance << " last chance move: " << s.last_chance_move << std::endl;
	// s = s.make_baby_from_coord(flat_coord(10, 11));
	// s.print();
	// std::cout << "win: " << s.game_win << " last chance: " << s.last_chance << " last chance move: " << s.last_chance_move << std::endl;
	// s = s.make_baby_from_coord(flat_coord(11, 12));
	// s.print();
	// // s = s.make_baby_from_coord(flat_coord(15, 15));
	// // s.print();

	// std::cout << "win: " << s.game_win << " last chance: " << s.last_chance << " last chance move: " << s.last_chance_move <<std::endl;
	// run_websocket_server("0.0.0.0", 16784);
}