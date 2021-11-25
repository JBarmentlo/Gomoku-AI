#include "minimax.hpp"
#include "utils.hpp"
#include <iostream>
int	minimax(State state, bool maximizer, int limit, int depth, int alpha, int beta)
{
	static int i = 0;
	i += 1;
	if (i % 1000000 == 0)
		std::cout << i << std::endl;

	// if (state.find_pattern_around_last_move(create_victory_pattern, (state.player + 1)% 2) != 0)
	// {
	// 	if (maximizer)
	// 	{
	// 		return (INT32_MIN + 2);
	// 	}
	// 	else
	// 	{
	// 		return (INT32_MAX - 2);
	// 	}
	// }

	if (depth == limit)
	{
		return (state.score);
	}

	int eval;
	int best_move = -12;
	if (maximizer)
	{
		int maxEval = -INT32_MAX;
		for (int c = 0; c < BOARD_SIZE; c++)
		{
			if (state.live_board.test(c))
			{
				eval = minimax(state.make_baby_from_coord(c), !maximizer, limit, depth + 1, alpha, beta);
				if (eval > maxEval)
				{
					best_move = c;
					maxEval = eval;
				}
				alpha = std::max(alpha, eval);
				if (beta <= alpha)
				{
					break;
				}
			}
		}
		if (depth == 0)
		{
			return best_move;
		}
		else
		{
			return (maxEval);
		}
	}
	else
	{
		int minEval = INT32_MAX;

		for (int c = 0; c < BOARD_SIZE; c++)
		{
			if (state.live_board[c])
			{
				eval = minimax(state.make_baby_from_coord(c), !maximizer, limit, depth + 1, alpha, beta);
				if (eval < minEval)
				{
					minEval = eval;
					best_move = c;
				}
				beta = std::min(beta, eval);
				if (beta <= alpha)
				{
					break;
				}
			}
		}
		if (depth == 0)
		{
			return best_move;
		}
		else
		{
			return (minEval);
		}
	}
}

// int	minimax(State state, bool maximizer, int depth, int alpha, int beta)
// {
// 	if (depth == 0)
// 	{
// 		return (state.score);
// 	}
// 	std::multiset<State> bebes = state.make_ordered_babies();

// 	int eval;
// 	if (maximizer)
// 	{
// 		int maxEval = -INT32_MAX;

// 		for (std::multiset<State>::iterator it=bebes.begin(); it!=bebes.end(); ++it)
// 		{
// 			eval = minimax(*it, !maximizer, alpha, beta, depth - 1);
// 			maxEval = std::max(maxEval, eval);
// 			alpha = std::max(alpha, eval);
// 			if (beta <= alpha)
// 				break;
// 			return (maxEval);
// 		}
// 	}
// 	else
// 	{
// 		int minEval = INT32_MAX;

// 		for (std::multiset<State>::iterator it=bebes.begin(); it!=bebes.end(); ++it)
// 		{
// 			eval = minimax(*it, !maximizer, alpha, beta, depth - 1);
// 			minEval = std::min(minEval, eval);
// 			beta = std::min(beta, eval);
// 			if (beta <= alpha)
// 				break;
// 			return (minEval);
// 		}
// 	}
// }