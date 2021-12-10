#include "minimax.hpp"
#include "utils.hpp"
#include "eval.hpp"

#include <iostream>

#include <vector>
#include <array>

#include <algorithm>

// bool compare_score(const State& s1, const State& s2)
// {
// 	return (s1.score > s2.score);
// }

// bool compare_score_reverse(const State& s1, const State& s2)
// {
// 	return (s1.score < s2.score);
// }

bool compare_score(const std::pair<int, int>& s1, const std::pair<int, int>& s2)
{
	return (s1.first > s2.first);
}

bool compare_score_reverse(const std::pair<int, int>& s1, const std::pair<int, int>& s2)
{
	return (s1.first < s2.first);
}

int	minimax(State state, int limit, int depth, int alpha, int beta)
{
	static int i = 0;
	i += 1;
	// if (i % int(1e5) == 0)
		// std::cout << i;

	// std::cout << "depth: " << depth << std::endl;
	// state.print();
	// std::cout << std::endl;
	bool  maximizer = (state.player == WHITE);

	if (state.game_win)
	{
		// state.print();
		if (maximizer)
			return (INT32_MIN + 1);
		else
			return (INT32_MAX - 1);
	}
	if (depth == limit)
		return (state.score);

	int eval;
	int best_move = -12;

	// std::vector<State> babies;
	// std::array<State, 150> babies;
	std::pair<int, int>  babies[200]; // <Score, move>
	int counter = 0;

	if (maximizer)
	{
		int maxEval = INT32_MIN;
		for (int c = 0; c < BOARD_SIZE; c++)
		{
			if (state.live_board.test(c))
			{
				babies[counter] = std::pair<int, int>(tuples_eval_at_coord_potential(state, c, state.player), c);
				counter += 1;
				if (counter == 200)
					break;
			}
			std::sort(babies, babies + counter, compare_score);
		}
		// std::max(10.0, (1.0 - float(depth) / float(limit)) * counter)
		for(int i = 0; i < counter; i++)
		{
			eval = minimax(state.make_baby_from_coord(babies[i].second), limit, depth + 1, alpha, beta);
			if (eval > maxEval)
			{
				// std::cout << "FOUND BETTER MOVE: " << babies[i].second << " eval: " << eval << std::endl;
				best_move = babies[i].second;
				maxEval = eval;
			}
			alpha = std::max(alpha, eval);
			if (beta <= alpha)
				break;
		}
		if (depth == 0)
			return best_move;
		else
			return (maxEval);
	}
	else
	{
		int minEval = INT32_MAX;
		for (int c = 0; c < BOARD_SIZE; c++)
		{
			if (state.live_board.test(c))
			{
				babies[counter] = std::pair<int, int>(tuples_eval_at_coord_potential(state, c, state.player), c);
				counter += 1;
				if (counter == 100)
					break;
			}
			std::sort(babies, babies + counter, compare_score_reverse); 

		}
		for(int i = 0; i < counter; i++)
		{
			eval = minimax(state.make_baby_from_coord(babies[i].second), limit, depth + 1, alpha, beta);
			if (eval < minEval)
			{
				// std::cout << "FOUND BETTER MOVE: " << babies[i].second << " eval: " << eval << std::endl;
				best_move = babies[i].second;
				minEval = eval;
			}
			beta = std::min(beta, eval);
			if (beta <= alpha)
				break;
		}
		if (depth == 0)
			return best_move;
		else
			return (minEval);
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