#include "minimax.hpp"
#include "utils.hpp"
#include "eval.hpp"

#include <iostream>

#include <vector>
#include <array>

#include <algorithm>
#include <deque>

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

int	minimax(State state, int limit, std::deque<int> past_scores, int depth, int alpha, int beta)
{
	static int node_count = 0;
	static int tactics_pruned = 0;
	static int a_b_pruned = 0;

	if (depth == 0)
	{
		tactics_pruned = 0;
		node_count = 0;
		a_b_pruned = 0;
	}
	node_count += 1;
	

	bool	maximizer = (state.player == WHITE);

	past_scores.push_front(state.score);

	int	start_score;
	if (maximizer)
		start_score = INT32_MIN;
	else
		start_score = INT32_MAX;

	if (past_scores.size() > TACTICS_LEN)
	{
	 	start_score = past_scores.back();
		past_scores.pop_back();
	}


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
	std::pair<int, int>	babies[200]; // <Score, state_index>
	State				babie_states[200];

	int counter = 0;

	if (maximizer)
	{
		if (past_scores.size() == TACTICS_LEN and start_score > state.score)
		{
			tactics_pruned += 1;
			return state.score;
		}
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
			eval = minimax(state.make_baby_from_coord(babies[i].second), limit, past_scores, depth + 1, alpha, beta);
			if (eval > maxEval)
			{
				// std::cout << "FOUND BETTER MOVE: " << babies[i].second << " eval: " << eval << std::endl;
				best_move = babies[i].second;
				maxEval = eval;
			}
			alpha = std::max(alpha, eval);
			if (beta <= alpha)
			{
				a_b_pruned += 1;
				break;
			}
		}
		if (depth == 0)
		{
			std::cout << "NODES EXPLORED:   " << node_count << std::endl;
			std::cout << "TACTICS PRUNED:   " << tactics_pruned << std::endl;
			std::cout << "A_B PRUNED:       " << a_b_pruned << std::endl;
			return best_move;
		}
		else
			return (maxEval);
	}
	else
	{
		if (past_scores.size() == TACTICS_LEN and start_score < state.score)
		{
			tactics_pruned += 1;
			return state.score;
		}
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
			eval = minimax(state.make_baby_from_coord(babies[i].second), limit, past_scores, depth + 1, alpha, beta);
			if (eval < minEval)
			{
				// std::cout << "FOUND BETTER MOVE: " << babies[i].second << " eval: " << eval << std::endl;
				best_move = babies[i].second;
				minEval = eval;
			}
			beta = std::min(beta, eval);
			if (beta <= alpha)
			{
				a_b_pruned += 1;
				break;
			}
		}
		if (depth == 0)
		{
			std::cout << "NODES EXPLORED:   " << node_count << std::endl;
			std::cout << "TACTICS PRUNED:   " << tactics_pruned << std::endl;
			std::cout << "A_B PRUNED:       " << a_b_pruned << std::endl;

			return best_move;
		}
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